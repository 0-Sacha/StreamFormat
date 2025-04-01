#pragma once

#include "basic_formatter_executor.hxx"

#include "stream/fmt/buf/streamio_manager/dynamic_streamio_manager.hxx"
#include "stream/fmt/buf/streamio_manager/given_streamio_manager.hxx"
#include "stream/fmt/buf/streamio_manager/static_streamio_manager.hxx"

#include "formatter_text_properties_executor/formatter_text_properties_executor_ansi.hxx"

#include <memory>

namespace stream::fmt {
    /////---------- Impl with as Format ----------//////
    namespace detail {
        template <typename TChar, typename... Args>
            requires(IsCharType<TChar>::value)
        void format_in_manager(buf::BasicStreamIOManager<TChar>& ostream_manager, bool newline, buf::StreamView<TChar> format, Args&&... args) {
            using TCharResolved = std::remove_const_t<TChar>;

            detail::FormatterTextPropertiesExecutorANSI<TCharResolved> text_properties_executor;
            buf::FMTStreamIO<TCharResolved>                            ostream = buf::FMTStreamIO<TCharResolved>::create(ostream_manager);
            context::BasicFormatterExecutor<TCharResolved>             executor(ostream, text_properties_executor);
            executor.run(format, std::forward<Args>(args)...);
            if (newline) buf::ManipIO(ostream).pushback('\n');
            return executor.terminate();
        }

        template <typename TChar, typename T>
            requires(IsCharType<TChar>::value)
        void format_in_manager(buf::BasicStreamIOManager<TChar>& ostream_manager, bool newline, T&& t) {
            using TCharResolved = std::remove_const_t<TChar>;

            detail::FormatterTextPropertiesExecutorANSI<TCharResolved> text_properties_executor;
            buf::FMTStreamIO<TCharResolved>                            ostream = buf::FMTStreamIO<TCharResolved>::create(ostream_manager);
            context::BasicFormatterExecutor<TCharResolved>             executor(ostream, text_properties_executor);
            executor.write_type(std::forward<T>(t));
            if (newline) buf::ManipIO(ostream).pushback('\n');
            return executor.terminate();
        }
    }  // namespace detail

    template <typename TChar, typename Format, std::size_t BUFFER_SIZE, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    void format_in_char(TChar (&buffer)[BUFFER_SIZE], Format&& format_input, Args&&... args) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer);
        return detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    void format_in_char(TChar* const buffer, const std::size_t buffer_size, Format&& format_input, Args&&... args) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer, buffer_size);
        return detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    void cfile_print(FILE* stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);

        std::fwrite(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size(), 1, stream);
        std::fflush(stream);
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    void cfile_println(FILE* stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        detail::format_in_manager(ostream_manager, true, buf::StreamView{format_input}, std::forward<Args>(args)...);

        std::fwrite(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size(), 1, stream);
        std::fflush(stream);
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    void file_print(std::basic_ostream<TChar>& stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);

        stream.write(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size());
        stream.flush();
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    void file_println(std::basic_ostream<TChar>& stream, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        detail::format_in_manager(ostream_manager, true, buf::StreamView{format_input}, std::forward<Args>(args)...);

        stream.write(ostream_manager.get_buffer(), ostream_manager.get_last_generated_data_size());
        stream.flush();
    }

    template <typename TChar, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    void format_in_string(std::basic_string<TChar>& str, Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);
        str = ostream_manager.get_last_generated_string_view();
    }

    template <typename TChar = char, typename Format, typename... Args>
        requires(detail::IsCharType<TChar>::value && buf::convertible_to_buffer_info_view<Format>)
    inline std::basic_string<TChar> format_string(Format&& format_input, Args&&... args) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(256);
        detail::format_in_manager(ostream_manager, false, buf::StreamView{format_input}, std::forward<Args>(args)...);
        return std::basic_string<TChar>{ostream_manager.get_last_generated_string_view()};
    }

    /////---------- NO-FORMAT Impl except for string which are formatted to avoid {} ----------//////

    template <typename TChar, size_t BUFFER_SIZE, typename T>
        requires(detail::IsCharType<TChar>::value)
    void format_in_char(TChar (&buffer)[BUFFER_SIZE], T&& t) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer, BUFFER_SIZE);
        return detail::format_in_manager(ostream_manager, false, std::forward<T>(t));
    }

    template <typename TChar, typename T>
        requires(detail::IsCharType<TChar>::value)
    void format_in_char(TChar* const buffer, const std::size_t buffer_size, T&& t) {
        buf::GivenStreamIOManager<TChar> ostream_manager(buffer, buffer_size);
        return detail::format_in_manager(ostream_manager, false, std::forward<T>(t));
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    void cfile_print(FILE* stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        detail::format_in_manager(ostream_manager, false, std::forward<T>(t));

        std::fwrite(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()), 1, stream);
        std::fflush(stream);
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    void cfile_println(FILE* stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        detail::format_in_manager(ostream_manager, true, std::forward<T>(t));

        std::fwrite(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()), 1, stream);
        std::fflush(stream);
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    void file_print(std::basic_ostream<TChar>& stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        detail::format_in_manager(ostream_manager, false, std::forward<T>(t));

        stream.write(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()));
        stream.flush();
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    void file_println(std::basic_ostream<TChar>& stream, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        detail::format_in_manager(ostream_manager, true, std::forward<T>(t));

        stream.write(ostream_manager.get_buffer(), static_cast<std::streamsize>(ostream_manager.get_last_generated_data_size()));
        stream.flush();
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    void format_in_string(std::basic_string<TChar>& str, T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        detail::format_in_manager(ostream_manager, false, std::forward<T>(t));
        str = ostream_manager.get_last_generated_string_view();
    }

    template <typename TChar = char, typename T>
        requires(detail::IsCharType<TChar>::value)
    inline std::basic_string<TChar> format_string(T&& t) {
        buf::DynamicStreamIOManager<TChar> ostream_manager(32);
        detail::format_in_manager(ostream_manager, false, std::forward<T>(t));
        return std::string{ostream_manager.get_last_generated_string_view()};
    }
}  // namespace stream::fmt
