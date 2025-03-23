#pragma once

#include "basic_formatter_executor.h"

#include "stream/fmt/buf/streamio_manager/dynamic_streamio_manager.h"
#include "stream/fmt/buf/streamio_manager/given_streamio_manager.h"
#include "stream/fmt/buf/streamio_manager/static_streamio_manager.h"

#include "formatter_text_properties_executor/formatter_text_properties_executor_ansi.h"

#include <memory>

namespace stream::fmt {
    /////---------- Impl with as Format ----------//////
    namespace detail {
        template <typename TChar, typename... Args>
            requires(IsCharType<TChar>::value)
        [[nodiscard]] std::expected<void, FMTResult> format_in_manager(buf::BasicStreamIOManager<TChar>& ostream_manager, bool newline, buf::StreamView<TChar> format,
                                                                       Args&&... args) {
            using TCharResolved = std::remove_const_t<TChar>;

            detail::FormatterTextPropertiesExecutorANSI<TCharResolved> text_properties_executor;
            buf::FMTStreamIO<TCharResolved>                            ostream = SF_TRY(buf::FMTStreamIO<TCharResolved>::create(ostream_manager));
            context::BasicFormatterExecutor<TCharResolved>             executor(ostream, text_properties_executor);
            SF_TRY(executor.run(format, std::forward<Args>(args)...));
            if (newline) SF_TRY(buf::ManipIO(ostream).pushback('\n'));
            return executor.terminate();
        }

        template <typename TChar, typename T>
            requires(IsCharType<TChar>::value)
        [[nodiscard]] std::expected<void, FMTResult> format_in_manager(buf::BasicStreamIOManager<TChar>& ostream_manager, bool newline, T&& t) {
            using TCharResolved = std::remove_const_t<TChar>;

            detail::FormatterTextPropertiesExecutorANSI<TCharResolved> text_properties_executor;
            buf::FMTStreamIO<TCharResolved>                            ostream = SF_TRY(buf::FMTStreamIO<TCharResolved>::create(ostream_manager));
            context::BasicFormatterExecutor<TCharResolved>             executor(ostream, text_properties_executor);
            SF_TRY(executor.write_type(std::forward<T>(t)));
            if (newline) SF_TRY(buf::ManipIO(ostream).pushback('\n'));
            return executor.terminate();
        }
    }  // namespace detail

    template <typename TChar, typename Format, std::size_t BUFFER_SIZE, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] std::expected<void, FMTResult> format_in_char(TChar (&buffer)[BUFFER_SIZE], Format&& format_input, Args&&... args) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer);
        return detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] std::expected<void, FMTResult> format_in_char(TChar* const buffer, const std::size_t buffer_size, Format&& format_input, Args&&... args) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer, buffer_size);
        return detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] std::expected<void, FMTResult> cfile_print(FILE* stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        SF_TRY(detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...));

        std::fwrite(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size(), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] std::expected<void, FMTResult> cfile_println(FILE* stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        SF_TRY(detail::format_in_manager(ostream_manager, true, buf::StreamView{format_input}, std::forward<Args>(args)...));

        std::fwrite(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size(), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] std::expected<void, FMTResult> file_print(std::basic_ostream<TChar>& stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        SF_TRY(detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...));

        stream.write(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size());
        stream.flush();
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] std::expected<void, FMTResult> file_println(std::basic_ostream<TChar>& stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        SF_TRY(detail::format_in_manager(ostream_manager, true, buf::StreamView{format_input}, std::forward<Args>(args)...));

        stream.write(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size());
        stream.flush();
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] std::expected<void, FMTResult> format_in_string(std::basic_string<TChar>& str, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        SF_TRY(detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...));
        str = ostream_manager.get_last_generated_string_view();
        return {};
    }

    template <typename TChar = char, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    [[nodiscard]] inline std::expected<std::basic_string<TChar>, FMTResult> format_string(Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        SF_TRY(detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...));
        return std::basic_string<TChar>{ostream_manager.get_last_generated_string_view()};
    }

    /////---------- NO-FORMAT Impl except for string which are formatted to avoid {} ----------//////

    template <typename TChar, size_t BUFFER_SIZE, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] std::expected<void, FMTResult> format_in_char(TChar (&buffer)[BUFFER_SIZE], T&& t) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer, BUFFER_SIZE);
        return detail::format_in_manager(ostream_manager, false, std::forward<T>(t));
    }

    template <typename TChar, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] std::expected<void, FMTResult> format_in_char(TChar* const buffer, const std::size_t buffer_size, T&& t) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer, buffer_size);
        return detail::format_in_manager(ostream_manager, false, std::forward<T>(t));
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] std::expected<void, FMTResult> cfile_print(FILE* stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        SF_TRY(detail::format_in_manager(ostream_manager, false, std::forward<T>(t)));

        std::fwrite(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] std::expected<void, FMTResult> cfile_println(FILE* stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        SF_TRY(detail::format_in_manager(ostream_manager, true, std::forward<T>(t)));

        std::fwrite(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] std::expected<void, FMTResult> file_print(std::basic_ostream<TChar>& stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        SF_TRY(detail::format_in_manager(ostream_manager, false, std::forward<T>(t)));

        stream.write(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()));
        stream.flush();
        return {};
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] std::expected<void, FMTResult> file_println(std::basic_ostream<TChar>& stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        SF_TRY(detail::format_in_manager(ostream_manager, true, std::forward<T>(t)));

        stream.write(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()));
        stream.flush();
        return {};
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] std::expected<void, FMTResult> format_in_string(std::basic_string<TChar>& str, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        SF_TRY(detail::format_in_manager(ostream_manager, false, std::forward<T>(t)));
        str = ostream_manager.get_last_generated_string_view();
        return {};
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    [[nodiscard]] inline std::expected<std::basic_string<TChar>, FMTResult> format_string(T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        SF_TRY(detail::format_in_manager(ostream_manager, false, std::forward<T>(t)));
        return std::string{ostream_manager.get_last_generated_string_view()};
    }
}  // namespace stream::fmt

namespace stream::fmt {
    template <typename FormatterExecutor>
    struct FormatterType<FMTResult, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(FMTResult result, FormatterExecutor& executor) {
            switch (result) {
                case FMTResult::FunctionNotImpl:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("FunctionNotImpl");
                case FMTResult::Buffer_NonValid:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Buffer_NonValid");
                case FMTResult::Buffer_OutOfBoundAccess:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Buffer_OutOfBoundAccess");
                case FMTResult::Buffer_UnableToReserveMemory:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Buffer_UnableToReserveMemory");
                case FMTResult::Parse_NonValidDigit:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Parse_NonValidDigit");
                case FMTResult::Parse_TokenNotExpected:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Parse_TokenNotExpected");
                case FMTResult::ArgsInterface_Unavaible:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("ArgsInterface_Unavaible");
                case FMTResult::ArgsInterface_InvalidTypeID:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("ArgsInterface_InvalidTypeID");
                case FMTResult::ArgsInterface_InvalidConversion:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("ArgsInterface_InvalidConversion");
                case FMTResult::ArgsInterface_CantMatchNamedArgs:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("ArgsInterface_CantMatchNamedArgs");
                case FMTResult::ArgsInterface_IndexOutOfBounds:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("ArgsInterface_IndexOutOfBounds");
                case FMTResult::Specifiers_Full:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Specifiers_Full");
                case FMTResult::Specifiers_Invalid:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Specifiers_Invalid");
                case FMTResult::Specifiers_DoesNotExist:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Specifiers_DoesNotExist");
                case FMTResult::Context_ParsingFormat:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Context_ParsingFormat");
                case FMTResult::Context_ArgumentIndexResolution:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Context_ArgumentIndexResolution");
                case FMTResult::Context_ArgumentIndexExpected:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Context_ArgumentIndexExpected");
                case FMTResult::Context_CannotapplyType:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Context_CannotapplyType");
                case FMTResult::GivenArgs_UnableToDeduceSize:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("GivenArgs_UnableToDeduceSize");
                case FMTResult::Manager_StaticMemory:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Manager_StaticMemory");
                case FMTResult::Manager_AllocationFailed:
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("Manager_AllocationFailed");
            }
        }
    };
}  // namespace stream::fmt
