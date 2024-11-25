#pragma once

#include "StreamFormat/FMT/Detail/ConvertTraits.h"
#include "StreamFormat/FMT/Detail/Prelude.h"
#include "StreamFormat/FMT/Detail/Specifiers.h"

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferManip.h"
#include "StreamFormat/FMT/Buffer/BufferTestManip.h"
#include "StreamFormat/FMT/Buffer/BufferReadManip.h"

#include "BasicArgsInterface.h"

#include "ITextPropertiesExecutor.h"
#include "TextPropertiesManager.h"

namespace StreamFormat::FMT::Context
{
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class ContextExecutor
    {
    public:
        ContextExecutor(Detail::ITextPropertiesExecutor& textPropertiesExecutor)
            : Data{}
            , TextManager{textPropertiesExecutor}
        {}
        virtual ~ContextExecutor() = default;
        
    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecSettings() = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecRawString(std::basic_string_view<TChar>) = 0;

    public:
        Detail::FormatData<TChar> Data;
        Detail::TextPropertiesManager<TChar> TextManager;
    };

    template <typename CharType>
    class BasicContext
    {
    public:
        using TChar = CharType;

    public:
        BasicContext(
            ContextExecutor<TChar>& executor,
            Detail::BufferInfoView<TChar> format,
            Detail::BasicArgsInterface<TChar>& argsInterface
        );
        virtual ~BasicContext() = default;
        
    public:
        ContextExecutor<TChar>& Executor;

        Detail::BufferInfoView<TChar> Format;        
        Detail::BasicArgsInterface<TChar>& ArgsInterface;
        std::int32_t ValuesIndex;

    public:
        [[nodiscard]] std::expected<void, FMTResult> Run();

    public:
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex();
        template <typename T>
        [[nodiscard]] std::expected<T, FMTResult> FormatReadParameter(const T& defaultValue);

    protected:
        void FormatDataApplyNextOverride();

    protected:
        [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> ParseNextOverrideFormatData();

        [[nodiscard]] std::expected<void, FMTResult> ParseFormatDataBase();
        [[nodiscard]] std::expected<void, FMTResult> ParseFormatDataSpecial();
        [[nodiscard]] std::expected<void, FMTResult> ParseFormatDataSpecial_ShiftType(const Detail::ShiftInfo::ShiftType type);
        [[nodiscard]] std::expected<void, FMTResult> ParseFormatDataCustom();
        [[nodiscard]] std::expected<void, FMTResult> ParseFormatData();

        [[nodiscard]] std::expected<void, FMTResult> ParseVariable(std::int32_t formatIdx);
        [[nodiscard]] std::expected<void, FMTResult> Parse();

    public:
        template <typename Func, typename... Args>
        inline void ExecNextFormatData(Func&& func, Args&&... args)
        {
            if (Executor.Data.NextOverride.size() == 0)
                return func(std::forward<Args>(args)...);
            Detail::FormatData<TChar> formatDataCopy = Executor.Data;
            FormatDataApplyNextOverride();
            func(std::forward<Args>(args)...);
            Executor.Data = formatDataCopy;
        }
    };
}

namespace StreamFormat::FMT::Context
{
    template <typename TChar>
    BasicContext<TChar>::BasicContext(
            ContextExecutor<TChar>& executor,
            Detail::BufferInfoView<TChar> format,
            Detail::BasicArgsInterface<TChar>& argsInterface
        )
        : Executor(executor)
        , Format{format}
        , ArgsInterface{argsInterface}
        , ValuesIndex{0}
    {}

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::Run()
    {
        while (!Detail::BufferAccess(Format).IsEndOfString())
        {
            const TChar* beginContinousString = Format.CurrentPos;
            std::size_t sizeContinousString  = 0;
            while (Detail::BufferAccess(Format).IsEndOfString() == false && Detail::BufferTestAccess(Format).IsEqualTo('{') == false)
            {
                ++sizeContinousString;
                SF_TRY(Detail::BufferManip(Format).Forward());
            }
            SF_TRY(Executor.ExecRawString(std::basic_string_view<TChar>(beginContinousString, sizeContinousString)));

            if (Detail::BufferAccess(Format).IsEndOfString() == false && Detail::BufferTestAccess(Format).IsEqualTo('{'))
            {
                SF_TRY(Parse());
            }
        }

        return {};
    }

    template <typename TChar>
    void BasicContext<TChar>::FormatDataApplyNextOverride()
    {
        if (Executor.Data.NextOverride.size() == 0) return;

        Detail::BufferInfoView<TChar> overridePos(Executor.Data.NextOverride);
        Detail::BufferInfoView<TChar> formatPos = Format;
        Format = overridePos;
        ParseFormatData();
        Format = formatPos;
    }

    template <typename TChar>
    template <typename T>
    [[nodiscard]] std::expected<T, FMTResult> BasicContext<TChar>::FormatReadParameter(const T& defaultValue)
    {
        if (!Detail::BufferTestAccess(Format).IsEqualTo('{'))
        {
            T t;
            SF_TRY(Detail::BufferReadManip(Format).FastReadInteger(t));
            return t;
        }

        // SubIndex
        SF_TRY(Detail::BufferTestManip(Format).SkipOneOf('}'));
        std::int32_t formatIdx = SF_TRY(GetFormatIndex());
        if constexpr (std::is_convertible_v<T, int64_t>)
            return ArgsInterface.GetIntAt(formatIdx);
        else if constexpr (std::is_convertible_v<T, std::basic_string_view<TChar>>)
            return ArgsInterface.GetStringAt(formatIdx);

        return std::unexpected(FMTResult::Context_ArgumentIndexExpected);
    }
}

#include "BasicContextParse-impl.h"
