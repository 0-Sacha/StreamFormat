#pragma once

#include "StreamFormat/FMT/Detail/Detail.h"
#include "StreamFormat/FMT/Buffer/FMTBufferOutManip.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    struct NoStrideFunction
    {
        inline explicit NoStrideFunction(FMTBufferOutInfo<TChar>& buffer)
            : Buffer(buffer)
            , SizeBuffer(BufferAccess(buffer).GetBufferCurrentSize())
        {}

        ~NoStrideFunction() { FMTBufferOutManip(Buffer).AddNoStride(BufferAccess(Buffer).GetBufferCurrentSize() - SizeBuffer); }

        FMTBufferOutInfo<TChar>& Buffer;
        std::size_t SizeBuffer;
    };
}
