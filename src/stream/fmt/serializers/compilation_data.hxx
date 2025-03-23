#pragma once

#include "stream/core/prelude.hxx"
#include "stream/flog.hxx"

namespace stream::fmt::detail {
    struct FileLocation {
        FileLocation(std::string_view file_name_, int file_line_ = 0) : file_name(file_name_), file_line(file_line_) {}

        std::string_view file_name;  // __FILE__
        int              file_line;  // __LINE__
    };

    struct FunctionProperties {
        FunctionProperties(std::string_view file_name_, int file_line_ = 0, std::string_view functionName = "", std::string_view function_signature_ = "",
                           std::string_view function_assembly_name_ = "")
            : location(file_name_, file_line_), function_name(functionName), function_signature(function_signature_), function_assembly_name(function_assembly_name_) {}

        FunctionProperties(FileLocation location, std::string_view functionName = "", std::string_view function_signature_ = "", std::string_view function_assembly_name_ = "")
            : location(location), function_name(functionName), function_signature(function_signature_), function_assembly_name(function_assembly_name_) {}

        FileLocation     location;
        std::string_view function_name;           // __FUNCTION__
        std::string_view function_signature;      // __FUNCSIG__ -- __PRETTY_FUNCTION__
        std::string_view function_assembly_name;  // __FUNCDNAME__
    };
}  // namespace stream::fmt::detail

#define STREAMFORMAT_FMT_FILE_LOCATION() stream::fmt::detail::FileLocation(__FILE__, __LINE__)
#define STREAMFORMAT_FMT_FUNCTION_PROPERTIES() stream::fmt::detail::FunctionProperties(STREAMFORMAT_FMT_FILE_LOCATION(), __FUNCTION__, __FUNCSIG__, __FUNCDNAME__)

namespace stream::fmt {
    template <typename FormatterExecutor>
    struct FormatterType<detail::FileLocation, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const detail::FileLocation& t, FormatterExecutor& executor) {
            SF_VERIFY(executor.write_type(t.file_name));
            SF_VERIFY(executor.ostream.pushback(':'));
            return executor.write_type(t.file_line);
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<detail::FunctionProperties, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const detail::FunctionProperties& t, FormatterExecutor& executor) {
            SF_VERIFY(executor.write_type(t.location));
            SF_VERIFY(executor.ostream.write_char_array(" @ "));
            return executor.write_type(t.function_name);
        }
    };
}  // namespace stream::fmt
