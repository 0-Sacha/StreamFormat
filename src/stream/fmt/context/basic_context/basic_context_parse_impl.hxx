#pragma once

#include "basic_context.hxx"

#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"
#include "stream/fmt/buf/fmt_manip_io.hxx"
#include "stream/fmt/buf/fmt_read_manip.hxx"

#include "basic_context_parse_formatdata.hxx"

namespace stream::fmt::context {
    template <typename TChar>
    void BasicContext<TChar>::parse_variable(std::int32_t format_idx) {
        detail::FormatData<TChar> saveFormatData              = executor.data;
        executor.data                                         = detail::FormatData<TChar>{};
        detail::TextProperties::Properties saveTextProperties = executor.text_manager.save();

        if (buf::TestAccess(fmtstream).is_equal_to(':', '{')) {
            buf::Manip(fmtstream).forward();
            executor.data = ::stream::fmt::detail::parse_format_data(executor, fmtstream);
        }

        args_interface.run_type_at(format_idx);

        if (executor.data.keep_new_style == false) {
            executor.text_manager.reload(saveTextProperties);
        }

        executor.data = saveFormatData;
    }

    template <typename TChar>
    void BasicContext<TChar>::parse() {
        buf::Manip(fmtstream).forward();  // Ignore {

        if (buf::TestAccess(fmtstream).is_upper_case()) {
            executor.data = detail::parse_format_data(executor, fmtstream);
            return buf::FMTParamsManip(fmtstream).param_go_to_forward();  // Ignore }
        }

        std::optional<std::int32_t> format_idx = get_format_index(executor, fmtstream);
        if (format_idx.has_value()) {
            if (format_idx >= 0 && format_idx < args_interface.size()) {
                parse_variable(format_idx.value());
                return buf::FMTParamsManip(fmtstream).param_go_to_forward();  // Ignore }
            }
        }

        executor.exec_raw_string("{");
    }
}  // namespace stream::fmt::context
