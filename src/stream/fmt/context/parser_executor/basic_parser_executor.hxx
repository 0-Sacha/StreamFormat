#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/test_manip.hxx"

#include "stream/fmt/context/basic_context/basic_context.hxx"

#include "parser_type.hxx"

#include "parser_args.hxx"

#include "parser_text_properties_executor/parser_text_properties_executor.hxx"

namespace stream::fmt::context {
    template <typename CharType>
    class BasicParserExecutor : public ContextExecutor<CharType> {
    public:
        using TChar = CharType;

    private:
        using M_Type = BasicParserExecutor<TChar>;

    public:
        BasicParserExecutor(buf::StreamView<TChar>& istream, detail::ITextPropertiesExecutor& text_properties_executor);
        ~BasicParserExecutor() override = default;

        void terminate();

    public:
        buf::StreamView<TChar>& istream;

        using ContextExecutor<CharType>::data;
        using ContextExecutor<CharType>::text_manager;

    protected:
        void exec_raw_string(std::basic_string_view<TChar> sv) override {
            buf::TestManip(istream).is_same_forward(sv.data(), sv.size());
        }
        void exec_settings() override {};

    public:
        template <typename... Args>
        void run_(buf::StreamView<TChar> format, Args&&... args);
        template <typename Format, typename... Args>
        void run(Format&& format, Args&&... args);

    public:
        template <typename Type, typename... Rest>
        void read_type(Type& type, Rest&... rest) {
            ParserType<typename detail::FormatTypeForwardAs<detail::get_base_type<Type>>::type, M_Type>::parse(type, *this);
            if constexpr (sizeof...(rest) > 0) read_type(std::forward<Rest>(rest)...);
        }
    };
}  // namespace stream::fmt::context

namespace stream::fmt::context {
    template <typename TChar>
    BasicParserExecutor<TChar>::BasicParserExecutor(buf::StreamView<TChar>& istream_, detail::ITextPropertiesExecutor& text_properties_executor_)
        : ContextExecutor<TChar>(text_properties_executor_), istream{istream_} {
        text_properties_executor_.link_to_executor(this);
    }

    template <typename TChar>
    void BasicParserExecutor<TChar>::terminate() {}

    template <typename TChar>
    template <typename... Args>
    void BasicParserExecutor<TChar>::run_(buf::StreamView<TChar> format, Args&&... args) {
        auto args_interface = detail::ParserArgsInterface<TChar, BasicParserExecutor<TChar>, Args...>(*this, std::forward<Args>(args)...);

        detail::TextProperties::Properties saveTextProperties = text_manager.save();
        context::BasicContext<TChar>       context(*this, format, args_interface);
        context.run();
        return text_manager.reload(saveTextProperties);
    }

    template <typename TChar>
    template <typename Format, typename... Args>
    void BasicParserExecutor<TChar>::run(Format&& format_input, Args&&... args) {
        return run_(buf::StreamView{format_input}, std::forward<Args>(args)...);
    }
}  // namespace stream::fmt::context

#include "parse_basics_impl.hxx"
#include "parse_text_properties_impl.hxx"
