#pragma once

#include "StreamFormat/FMT/Detail/ConvertTraits.h"
#include "StreamFormat/FMT/Detail/Detail.h"

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
        virtual void ExecSettings() = 0;
        virtual Detail::BufferManipResult ExecRawString(std::basic_string_view<TChar>) = 0;

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
        void Run();

    public:
        Detail::BufferManipResult GetFormatIndex(std::int32_t& idx);

        template <typename T>
        Detail::BufferManipResult FormatReadParameter(T& i, const T& defaultValue);

    public:
        void FormatDataApplyNextOverride();

    protected:
        std::basic_string_view<TChar> ParseNextOverrideFormatData();

        void ParseFormatDataBase();
        void ParseFormatDataSpecial();
        void ParseFormatDataSpecial_ShiftType(const Detail::ShiftInfo::ShiftType type);
        void ParseFormatDataCustom();
        void ParseFormatData();

        void ParseVariable(std::int32_t formatIdx);
        bool Parse();

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
    void BasicContext<TChar>::Run()
    {
        while (!Detail::BufferAccess(Format).IsEndOfString())
        {
            const TChar* beginContinousString = Format.CurrentPos;
            std::size_t       sizeContinousString  = 0;
            while (Detail::BufferAccess(Format).IsEndOfString() == false && Detail::BufferTestAccess(Format).IsEqualTo('{') == false)
            {
                ++sizeContinousString;
                Detail::BufferManip(Format).Forward();
            }
            Executor.ExecRawString(std::basic_string_view<TChar>(beginContinousString, sizeContinousString));

            if (Detail::BufferAccess(Format).IsEndOfString() == false && Detail::BufferTestAccess(Format).IsEqualTo('{'))
            {
                bool parseArg = Parse();
                if (parseArg == false)
                    Executor.ExecRawString("{").ThrowIfFailed();
            }
        }
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
    Detail::BufferManipResult BasicContext<TChar>::FormatReadParameter(T& i, const T& defaultValue)
    {
        if (!Detail::BufferTestAccess(Format).IsEqualTo('{'))
        {
            if (Detail::BufferReadManip(Format).FastReadInteger(i) == false)
                i = defaultValue;
            return true;
        }

        // SubIndex
        std::int32_t formatIdx = 0;
        if (GetFormatIndex(formatIdx) == false) return false;
        Detail::BufferTestManip(Format).IsEqualToForward('}');
        if constexpr (std::is_convertible_v<T, int64_t>)
            i = static_cast<T>(ArgsInterface.GetIntAt(formatIdx));
        else if constexpr (std::is_convertible_v<T, std::basic_string_view<TChar>>)
            i = static_cast<T>(ArgsInterface.GetStringAt(formatIdx));
        
        return true;
    }
}

#include "BasicContextParse-impl.h"
