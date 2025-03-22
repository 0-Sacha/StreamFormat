#pragma once

#include "stream/fmt/detail/prelude.h"
#include "stream/fmt/buffer/fmt_buffer_out_manip.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    struct NoStrideFunction
    {
        inline explicit NoStrideFunction(FMTBufferOutInfo<TChar>& buffer)
            : Buffer(buffer)
            , SizeBuffer(BufferAccess(buffer).GetBufferCurrentSize())
        {}

        ~NoStrideFunction() { FMTBufferOutManip(buffer).AddNoStride(BufferAccess(buffer).GetBufferCurrentSize() - SizeBuffer); }

        FMTBufferOutInfo<TChar>& Buffer;
        std::size_t SizeBuffer;
    };
}
