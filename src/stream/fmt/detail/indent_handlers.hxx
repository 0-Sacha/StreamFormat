#pragma once

#include "stream/fmt/detail/prelude.hxx"
#include "stream/fmt/buf/fmt_manip_io.hxx"

namespace stream::fmt::detail {
    template <typename TChar>
    struct NoStrideFunction {
        inline explicit NoStrideFunction(buf::FMTStreamIO<TChar>& buffer_) : buffer(buffer_), size_buffer(buffer_.get_buffer_current_size()) {}

        ~NoStrideFunction() {
            buf::FMTManipIO(buffer).add_no_stride(buffer.get_buffer_current_size() - size_buffer);
        }

        buf::FMTStreamIO<TChar>& buffer;
        std::size_t              size_buffer;
    };
}  // namespace stream::fmt::detail
