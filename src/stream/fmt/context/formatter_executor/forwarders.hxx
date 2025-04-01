#pragma once

#include "stream/fmt/detail/specifiers.hxx"
#include "stream/fmt/buf/fmt_write_manip.hxx"
#include "stream/fmt/context/basic_context/basic_context_parse_formatdata.hxx"

#include <span>

namespace stream::fmt::detail {
    template <typename TChar>
    class ContainersUtility {
    public:
        static constexpr std::basic_string_view<TChar> default_join  = ", ";
        static constexpr std::basic_string_view<TChar> default_begin = "{ ";
        static constexpr std::basic_string_view<TChar> default_end   = " }";
    };

    template <typename FormatterExecutor>
    struct FunctionapplyNextOverride {
        inline explicit FunctionapplyNextOverride(FormatterExecutor& executor) : executor(executor), formatdata(executor.data) {
            buf::StreamView stream{executor.data.next_override};
            executor.data = parse_format_data(executor, stream);
        }

        inline ~FunctionapplyNextOverride() {
            executor.data = formatdata;
        }

        FormatterExecutor&                            executor;
        FormatData<typename FormatterExecutor::TChar> formatdata;
    };

    namespace forwarders {
        template <typename T, std::size_t Extend, typename FormatterExecutor>
        void format_span(const std::span<T, Extend> container, FormatterExecutor& executor) {
            std::size_t  begin_idx     = (std::size_t)executor.data.specifiers.get_as_number("begin", 0);
            std::size_t  end           = executor.data.specifiers.get_as_number("end", container.size());
            std::int32_t size_to_print = executor.data.specifiers.get_as_number("size", static_cast<std::int32_t>(end) - static_cast<std::int32_t>(begin_idx));

            buf::FMTWriteManip(executor.ostream).write_indent_sv(executor.data.specifiers.get_as_text("begin", ContainersUtility<char>::default_begin));
            std::basic_string_view<typename FormatterExecutor::TChar> join = executor.data.specifiers.get_as_text("join", ContainersUtility<char>::default_join);

            if (size_to_print > 0) {
                detail::FunctionapplyNextOverride apply_next_override(executor);

                bool first = true;
                std::for_each_n(container.begin() + begin_idx, static_cast<std::size_t>(size_to_print), [&](const auto& element) {
                    if (first) {
                        first = false;
                    } else {
                        buf::FMTWriteManip(executor.ostream).write_indent_sv(join);
                    }

                    executor.write_type(element);
                });
            }

            buf::FMTWriteManip(executor.ostream).write_indent_sv(executor.data.specifiers.get_as_text("end", ContainersUtility<char>::default_end));
        }

        template <typename TChar, typename FormatterExecutor>
        void format_string_view(const std::basic_string_view<TChar> container, FormatterExecutor& executor) {
            std::size_t  begin_idx     = (std::size_t)executor.data.specifiers.get_as_number("begin", 0);
            std::size_t  end           = executor.data.specifiers.get_as_number("end", container.size());
            std::int32_t size_to_print = executor.data.specifiers.get_as_number("size", static_cast<std::int32_t>(end) - static_cast<std::int32_t>(begin_idx));

            if (executor.data.specifiers.has("span")) {
                return format_span(std::span(container), executor);
            }

            if (executor.data.prefix_suffix) {
                buf::ManipIO(executor.ostream).pushback('\"');
            }

            if (size_to_print > 0) {
                // TODO: current indent ignore shift
                if (executor.data.specifiers.has("indent")) {
                    return buf::FMTWriteManip(executor.ostream).write_indent_sv(container.substr(begin_idx, static_cast<std::size_t>(size_to_print)));
                } else if (executor.data.has_spec == false) {
                    buf::WriteManip(executor.ostream).fast_write_sv(container.substr(begin_idx, static_cast<std::size_t>(size_to_print)));
                } else {
                    buf::FMTWriteManip(executor.ostream).write_sv(container.substr(begin_idx, static_cast<std::size_t>(size_to_print)), executor.data.shift);
                }
            }

            if (executor.data.prefix_suffix) {
                buf::ManipIO(executor.ostream).pushback('\"');
            }
        }
    }  // namespace forwarders
}  // namespace stream::fmt::detail
