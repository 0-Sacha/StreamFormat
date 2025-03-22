#pragma once

#include "stream/fmt/detail/convert_traits.h"
#include "stream/fmt/detail/prelude.h"
#include "stream/fmt/detail/specifiers.h"

#include "stream/fmt/buffer/buffer_info.h"
#include "stream/fmt/buffer/buffer_manip.h"
#include "stream/fmt/buffer/buffer_test_manip.h"
#include "stream/fmt/buffer/buffer_read_manip.h"

#include "basic_args_interface.h"

#include "text_properties_executor.h"
#include "text_properties_manager.h"

namespace stream::fmt::context
{
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class ContextExecutor
    {
    public:
        ContextExecutor(detail::ITextPropertiesExecutor& textPropertiesExecutor)
            : Data{}
            , TextManager{textPropertiesExecutor}
        {}
        virtual ~ContextExecutor() = default;
        
    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecSettings() = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> ExecRawString(std::basic_string_view<TChar>) = 0;

    public:
        detail::FormatData<TChar> Data;
        detail::TextPropertiesManager<TChar> TextManager;
    };

    template <typename CharType>
    class BasicContext
    {
    public:
        using TChar = CharType;

    public:
        BasicContext(
            ContextExecutor<TChar>& executor,
            detail::BufferInfoView<TChar> format,
            detail::BasicArgsInterface<TChar>& argsInterface
        );
        virtual ~BasicContext() = default;
        
    public:
        ContextExecutor<TChar>& Executor;

        detail::BufferInfoView<TChar> Format;        
        detail::BasicArgsInterface<TChar>& ArgsInterface;
        std::int32_t ValuesIndex;

    public:
        [[nodiscard]] std::expected<void, FMTResult> Run();

    private:
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex_Number();
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex_Name();
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex_SubIndex();

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
        [[nodiscard]] std::expected<void, FMTResult> ParseFormatDataSpecial_ShiftType(const detail::ShiftInfo::ShiftType type);
        [[nodiscard]] std::expected<void, FMTResult> ParseFormatDataCustom();
        [[nodiscard]] std::expected<void, FMTResult> ParseFormatData();

        [[nodiscard]] std::expected<void, FMTResult> ParseVariable(std::int32_t formatIdx);
        [[nodiscard]] std::expected<void, FMTResult> parse();

    public:
        template <typename Func, typename... Args>
        inline void ExecNextFormatData(Func&& func, Args&&... args)
        {
            if (Executor.Data.NextOverride.size() == 0)
                return func(std::forward<Args>(args)...);
            detail::FormatData<TChar> formatDataCopy = Executor.Data;
            FormatDataApplyNextOverride();
            func(std::forward<Args>(args)...);
            Executor.Data = formatDataCopy;
        }
    };
}

namespace stream::fmt::context
{
    template <typename TChar>
    BasicContext<TChar>::BasicContext(
            ContextExecutor<TChar>& executor,
            detail::BufferInfoView<TChar> format,
            detail::BasicArgsInterface<TChar>& argsInterface
        )
        : Executor(executor)
        , Format{format}
        , ArgsInterface{argsInterface}
        , ValuesIndex{0}
    {}

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::Run()
    {
        while (!detail::BufferAccess(Format).IsEndOfString())
        {
            const TChar* beginContinousString = Format.CurrentPos;
            std::size_t sizeContinousString  = 0;
            while (detail::BufferAccess(Format).IsEndOfString() == false && detail::BufferTestAccess(Format).IsEqualTo('{') == false)
            {
                ++sizeContinousString;
                SF_TRY(detail::BufferManip(Format).Forward());
            }
            SF_TRY(Executor.ExecRawString(std::basic_string_view<TChar>(beginContinousString, sizeContinousString)));

            if (detail::BufferAccess(Format).IsEndOfString() == false && detail::BufferTestAccess(Format).IsEqualTo('{'))
            {
                SF_TRY(parse());
            }
        }

        return {};
    }

    template <typename TChar>
    void BasicContext<TChar>::FormatDataApplyNextOverride()
    {
        if (Executor.Data.NextOverride.size() == 0)
            { return; }

        detail::BufferInfoView<TChar> overridePos(Executor.Data.NextOverride);
        detail::BufferInfoView<TChar> formatPos = Format;
        Format = overridePos;
        ParseFormatData();
        Format = formatPos;
    }

    template <typename TChar>
    template <typename T>
    [[nodiscard]] std::expected<T, FMTResult> BasicContext<TChar>::FormatReadParameter(const T& defaultValue)
    {
        if (!detail::BufferTestAccess(Format).IsEqualTo('{'))
        {
            T t;
            SF_TRY(detail::BufferReadManip(Format).FastReadInteger(t));
            return t;
        }

        // SubIndex
        SF_TRY(detail::BufferTestManip(Format).SkipOneOf('}'));
        std::int32_t formatIdx = SF_TRY(GetFormatIndex());
        if constexpr (std::is_convertible_v<T, int64_t>)
            return ArgsInterface.GetIntAt(formatIdx);
        else if constexpr (std::is_convertible_v<T, std::basic_string_view<TChar>>)
            return ArgsInterface.GetStringAt(formatIdx);

        return std::unexpected(FMTResult::Context_ArgumentIndexExpected);
    }
}

#include "BasicContextParse-impl.h"
