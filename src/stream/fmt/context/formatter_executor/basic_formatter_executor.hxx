#pragma once

#include "stream/fmt/context/basic_context/basic_context.hxx"

#include "stream/fmt/buf/fmt_manip_io.hxx"
#include "stream/fmt/buf/write_manip.hxx"

#include "formatter_type.hxx"
#include "index_args.hxx"
#include "named_args.hxx"
#include "std_enumerable.hxx"

#include "formatter_args.hxx"

namespace stream::fmt::context {
    enum class EndOfStringCharMode {
        Forced,
        Optional
    };

    template <typename CharType>
    class BasicFormatterExecutor : public context_executor<CharType> {
    public:
        using TChar = CharType;

    private:
        using M_Type = BasicFormatterExecutor<TChar>;

    public:
        BasicFormatterExecutor(buf::FMTStreamIO<TChar>& ostream, detail::ITextPropertiesExecutor& text_properties_executor);
        ~BasicFormatterExecutor() override = default;

        [[nodiscard]] std::expected<void, FMTResult> terminate();

    public:
        buf::FMTStreamIO<TChar>& ostream;
        EndOfStringCharMode      EndOfStringChar = EndOfStringCharMode::Optional;

        using context_executor<CharType>::data;
        using context_executor<CharType>::text_manager;

    protected:
        [[nodiscard]] std::expected<void, FMTResult> exec_raw_string(std::basic_string_view<TChar> sv) override {
            return buf::WriteManip(ostream).fast_write_string(sv);
        }
        [[nodiscard]] std::expected<void, FMTResult> exec_settings() override;

    public:
        template <typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> run_(buf::StreamView<TChar> format, Args&&... args);
        template <typename Format, typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> run(Format&& format, Args&&... args);

    public:
        template <typename Type, typename... Rest>
        [[nodiscard]] inline std::expected<void, FMTResult> write_type(Type&& type, Rest&&... rest) {
            auto&& formatErr = FormatterType<typename detail::FormatTypeForwardAs<detail::get_base_type<Type>>::type, M_Type>::format(std::forward<Type>(type), *this);
            SF_VERIFY(formatErr);
            if constexpr (sizeof...(rest) > 0) {
                SF_VERIFY(write_type(std::forward<Rest>(rest)...));
            }
            return {};
        }
    };
}  // namespace stream::fmt::context

namespace stream::fmt::context {
    template <typename TChar>
    BasicFormatterExecutor<TChar>::BasicFormatterExecutor(buf::FMTStreamIO<TChar>& ostream_, detail::ITextPropertiesExecutor& text_properties_executor_)
        : context_executor<TChar>(text_properties_executor_), ostream(ostream_) {
        text_properties_executor_.link_to_executor(this);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::terminate() {
        buf::ManipIO(ostream).compute_generated_size();

        // End char not included in buffer manager context to deduce size correctly
        auto res = buf::ManipIO(ostream).pushback('\0');
        if (EndOfStringChar == EndOfStringCharMode::Forced) {
            SF_VERIFY(res);
        }

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::exec_settings() {
        // indent
        auto indent = data.specifiers.get("indent");
        if (indent != nullptr) ostream.indent = indent->as_number;
        return {};
    }

    template <typename TChar>
    template <typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::run_(buf::StreamView<TChar> format, Args&&... args) {
        auto args_interface = detail::FormatterArgsInterface<TChar, BasicFormatterExecutor<TChar>, Args...>(*this, std::forward<Args>(args)...);

        detail::TextProperties::Properties saveTextProperties = text_manager.save();
        context::BasicContext<TChar>       context(*this, format, args_interface);
        SF_VERIFY(context.run());
        return text_manager.reload(saveTextProperties);
    }

    template <typename TChar>
    template <typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicFormatterExecutor<TChar>::run(Format&& format_input, Args&&... args) {
        return run_(buf::StreamView{format_input}, std::forward<Args>(args)...);
    }
}  // namespace stream::fmt::context

#include "format_basics_impl.hxx"
#include "format_text_properties_impl.hxx"
