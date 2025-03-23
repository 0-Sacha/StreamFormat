#pragma once

#include "basic_parser_executor.hxx"

#include "stream/fmt/buf/streamio_manager/given_streamio_manager.hxx"
#include "stream/fmt/buf/streamio_manager/static_streamio_manager.hxx"

#include "parser_text_properties_executor/parser_text_properties_executor_ansi.hxx"

namespace stream::fmt {
    template <typename Buffer, typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> parse(Buffer&& buffer_input, Format&& format_input, Args&&... args) {
        buf::StreamView buffer{buffer_input};
        buf::StreamView format{format_input};
        using TChar = typename decltype(format)::TChar;

        detail::ParserNOTextPropertiesExecutor<std::remove_const_t<TChar>> text_properties_executor;
        context::BasicParserExecutor<std::remove_const_t<TChar>>           executor(buffer, text_properties_executor);
        SF_VERIFY(executor.run(format, std::forward<Args>(args)...));
        return executor.terminate();
    }
}  // namespace stream::fmt
