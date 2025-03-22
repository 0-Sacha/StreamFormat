#pragma once

#include "stream/fmt/context/basic_context/basic_context.h"

#include "stream/fmt/buffer/fmt_buffer_out_manip.h"
#include "stream/fmt/buffer/buffer_write_manip.h"

#include "formatter_type.h"
#include "index_args.h"
#include "named_args.h"
#include "std_enumerable.h"

#include "formatter_args.h"

namespace stream::fmt::context
{
    enum class EndOfStringCharMode
    {
        Forced,
        Optional
    };

    template <typename CharType>
    class BasicFormatterExecutor : public ContextExecutor<CharType>
    {
    public:
        using TChar = CharType;
    private:
        using M_Type = BasicFormatterExecutor<TChar>;

    public:
        BasicFormatterExecutor(detail::FMTBufferOutInfo<TChar>& bufferOut, detail::ITextPropertiesExecutor& textPropertiesExecutor);
        ~BasicFormatterExecutor() override = default;

        [[nodiscard]] std::expected<void, FMTResult> Terminate();

    public:
        detail::FMTBufferOutInfo<TChar>& BufferOut;
        EndOfStringCharMode EndOfStringChar = EndOfStringCharMode::Optional;

        using ContextExecutor<CharType>::Data;
        using ContextExecutor<CharType>::TextManager;
    
    protected:
        [[nodiscard]] std::expected<void, FMTResult> ExecRawString(std::basic_string_view<TChar> sv) override
        {
            return detail::BufferWriteManip(BufferOut).FastWriteString(sv);
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecSettings() override;

    public:
        template <typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run_(detail::BufferInfoView<TChar> format, Args&&... args);
        template <typename Format, typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run(Format&& format, Args&&... args);

    public:
        template <typename Type, typename... Rest>
        [[nodiscard]] inline std::expected<void, FMTResult> WriteType(Type&& type, Rest&&... rest)
        {
            auto&& formatErr = FormatterType<typename detail::FormatTypeForwardAs<detail::GetBaseType<Type>>::Type, M_Type>::format(std::forward<Type>(type), *this);
            SF_TRY(formatErr);
            if constexpr (sizeof...(rest) > 0)
                { SF_TRY(WriteType(std::forward<Rest>(rest)...)); }
            return {};
        }
    };
}

namespace stream::fmt::context
{
    template <typename TChar>
    BasicFormatterExecutor<TChar>::BasicFormatterExecutor(detail::FMTBufferOutInfo<TChar>& bufferOut, detail::ITextPropertiesExecutor& textPropertiesExecutor)
        : ContextExecutor<TChar>(textPropertiesExecutor)
        , BufferOut(bufferOut)
    {
        textPropertiesExecutor.link_to_executor(this);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::Terminate()
    {
        detail::BufferOutManip(BufferOut).ComputeGeneratedSize();

        // End char not included in buffer manager context to deduce size correctly
        auto res = detail::BufferOutManip(BufferOut).Pushback('\0');
        if (EndOfStringChar == EndOfStringCharMode::Forced)
            { SF_TRY(res); }

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::ExecSettings()
    {
        // Indent
        auto indent = Data.Specifiers.Get("indent");
        if (indent != nullptr)
            BufferOut.Indent = indent->AsNumber;
        return {};
    }

    template <typename TChar>
    template <typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::Run_(detail::BufferInfoView<TChar> format, Args&&... args)
    {
        auto argsInterface = detail::FormatterArgsInterface<TChar, BasicFormatterExecutor<TChar>, Args...>(*this, std::forward<Args>(args)...);

        detail::TextProperties::Properties saveTextProperties = TextManager.Save();
        Context::BasicContext<TChar> context(*this, format, argsInterface);
        SF_TRY(context.Run());
        return TextManager.Reload(saveTextProperties);
    }

    template <typename TChar>
    template <typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::Run(Format&& formatInput, Args&&... args)
    {
        return Run_(detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }
}

#include "FormatBasics-impl.h"
#include "FormatTextProperties-impl.h"
