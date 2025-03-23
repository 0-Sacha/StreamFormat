#pragma once

#include "stream/fmt/buf/stream.h"
#include "stream/fmt/buf/manip.h"
#include "stream/fmt/buf/test_manip.h"

#include "stream/fmt/context/basic_context/basic_context.h"

#include "parser_type.h"

#include "parser_args.h"

#include "parser_text_properties_executor/parser_text_properties_executor.h"

namespace stream::fmt::context
{
    template <typename CharType>
    class BasicParserExecutor : public context_executor<CharType>
    {
    public:
        using TChar = CharType;
    private:
        using M_Type = BasicParserExecutor<TChar>;

    public:
        BasicParserExecutor(buf::StreamView<TChar>& istream, detail::ITextPropertiesExecutor& text_properties_executor);
        ~BasicParserExecutor() override = default;

        [[nodiscard]] std::expected<void, FMTResult> terminate();

    public:
        buf::StreamView<TChar>& istream;

        using context_executor<CharType>::data;
        using context_executor<CharType>::TextManager;

    protected:
        [[nodiscard]] std::expected<void, FMTResult> exec_raw_string(std::basic_string_view<TChar> sv) override
        {
            SF_TRY(buf::TestManip(istream).is_same_forward(sv.data(), sv.size()));
            return {};
        }
        [[nodiscard]] std::expected<void, FMTResult> exec_settings() override { return {}; };

    public:
        template <typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> run_(buf::StreamView<TChar> format, Args&&... args);
        template <typename Format, typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> run(Format&& format, Args&&... args);

    public:
        template <typename Type, typename... Rest>
        [[nodiscard]] inline std::expected<void, FMTResult> read_type(Type& type, Rest&... rest)
        {
            auto&& parseErr = ParserType<typename detail::FormatTypeForwardAs<detail::get_base_type<Type>>::type, M_Type>::parse(type, *this);
            SF_TRY(parseErr);
            if constexpr (sizeof...(rest) > 0)
                SF_TRY(read_type(std::forward<Rest>(rest)...));
            return {};
        }
    };
}

namespace stream::fmt::context
{
    template <typename TChar>
    BasicParserExecutor<TChar>::BasicParserExecutor(buf::StreamView<TChar>& istream_, detail::ITextPropertiesExecutor& text_properties_executor_)
        : context_executor<TChar>(text_properties_executor_)
        , istream{istream_}
    {
        text_properties_executor_.link_to_executor(this);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::terminate()
    {
        return {};
    }

    template <typename TChar>
    template <typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::run_(buf::StreamView<TChar> format, Args&&... args)
    {
        auto args_interface = detail::ParserArgsInterface<TChar, BasicParserExecutor<TChar>, Args...>(*this, std::forward<Args>(args)...);

        detail::TextProperties::Properties saveTextProperties = TextManager.save();
        context::BasicContext<TChar> context(*this, format, args_interface);
        SF_TRY(context.run());
        return TextManager.reload(saveTextProperties);
    }

    template <typename TChar>
    template <typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::run(Format&& format_input, Args&&... args)
    {
        return run_(buf::StreamView{format_input}, std::forward<Args>(args)...);
    }
}

#include "parse_basics_impl.h"
#include "parse_text_properties_impl.h"
