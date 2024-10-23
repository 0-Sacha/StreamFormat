#pragma once

#include "BasicParserExecutor.h"

#include "StreamFormat/FMT/Buffer/BufferOutManager/GivenBufferOutManager.h"
#include "StreamFormat/FMT/Buffer/BufferOutManager/StaticBufferOutManager.h"

#include "ParserTextPropertiesExecutor/ParserANSITextPropertiesExecutor.h"

namespace StreamFormat::FMT
{
    template <typename Buffer, typename Format, typename... Args>
    void Parse(Buffer&& bufferInput, Format&& formatInput, Args&&... args)
    {
        Detail::BufferInfoView buffer{bufferInput};
        Detail::BufferInfoView format{formatInput};
        using TChar = typename decltype(format)::TChar;

        Detail::ParserANSITextPropertiesExecutor<std::remove_const_t<TChar>> textPropertiesExecutor;
        Context::BasicParserExecutor<std::remove_const_t<TChar>> executor(buffer, textPropertiesExecutor);
        executor.Run(format, std::forward<Args>(args)...);
        executor.Terminate();
    }
}
