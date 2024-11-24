#pragma once

#include "StreamFormat/FMT/Context/BasicContext/BasicContext.h"

#include "StreamFormat/FMT/Buffer/FMTBufferOutManip.h"
#include "StreamFormat/FMT/Buffer/BufferWriteManip.h"

#include "FormatterType.h"
#include "IndexArgs.h"
#include "NamedArgs.h"
#include "STDEnumerable.h"

#include "FormatterArgs.h"

namespace StreamFormat::FMT::Context
{
    template <typename CharType>
    class BasicFormatterExecutor : public ContextExecutor<CharType>
    {
    public:
        using TChar = CharType;
    private:
        using M_Type = BasicFormatterExecutor<TChar>;

    public:
        BasicFormatterExecutor(Detail::FMTBufferOutInfo<TChar>& bufferOut, Detail::ITextPropertiesExecutor& textPropertiesExecutor);
        ~BasicFormatterExecutor() override = default;

        [[nodiscard]] std::expected<void, FMTResult> Terminate();

    public:
        Detail::FMTBufferOutInfo<TChar>& BufferOut;

        using ContextExecutor<CharType>::Data;
        using ContextExecutor<CharType>::TextManager;
    
    protected:
        [[nodiscard]] std::expected<void, FMTResult> ExecRawString(std::basic_string_view<TChar> sv) override
        {
            return Detail::BufferWriteManip(BufferOut).FastWriteString(sv);
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecSettings() override;

    public:
        template <typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run_(Detail::BufferInfoView<TChar> format, Args&&... args);
        template <typename Format, typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run(Format&& format, Args&&... args);

    public:
        template <typename Type, typename... Rest>
        [[nodiscard]] inline std::expected<void, FMTResult> WriteType(Type&& type, Rest&&... rest)
        {
            FormatterType<typename Detail::FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Format(std::forward<Type>(type), *this);
            if constexpr (sizeof...(rest) > 0)
                WriteType(std::forward<Rest>(rest)...);
        }
    };
}

namespace StreamFormat::FMT::Context
{
    template <typename TChar>
    BasicFormatterExecutor<TChar>::BasicFormatterExecutor(Detail::FMTBufferOutInfo<TChar>& bufferOut, Detail::ITextPropertiesExecutor& textPropertiesExecutor)
        : ContextExecutor<TChar>(textPropertiesExecutor)
        , BufferOut(bufferOut)
    {
        textPropertiesExecutor.LinkToExecutor(this);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::Terminate()
    {
        Detail::BufferOutManip(BufferOut).ComputeGeneratedSize();
        
        // End char not included in buffer manager context to deduce size correctly
        if (Detail::BufferOutManip(BufferOut).Reserve(1))
            Detail::BufferOutManip(BufferOut).Pushback('\0');
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::ExecSettings()
    {
        // Indent
        auto indent = Data.Specifiers.Get("indent");
        if (indent != nullptr)
            BufferOut.Indent = indent->AsNumber;
    }

    template <typename TChar>
    template <typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::Run_(Detail::BufferInfoView<TChar> format, Args&&... args)
    {
        auto argsInterface = Detail::FormatterArgsInterface<TChar, BasicFormatterExecutor<TChar>, Args...>(*this, std::forward<Args>(args)...);

        Detail::TextProperties::Properties saveTextProperties = TextManager.Save();
        Context::BasicContext<TChar> context(*this, format, argsInterface);
        context.Run();
        TextManager.Reload(saveTextProperties);
    }

    template <typename TChar>
    template <typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::Run(Format&& formatInput, Args&&... args)
    {
        Run_(Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }
}

#include "FormatBasics-impl.h"
#include "FormatTextProperties-impl.h"
