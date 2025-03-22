#pragma once

#include "BasicParserExecutor.h"

#include "stream/fmt/buffer/buffer_out_manager/given_buffer_out_manager.h"
#include "stream/fmt/buffer/buffer_out_manager/static_buffer_out_manager.h"

#include "ParserTextPropertiesExecutor/ParserANSITextPropertiesExecutor.h"

namespace stream::fmt
{
    template <typename Buffer, typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> parse(Buffer&& bufferInput, Format&& formatInput, Args&&... args)
    {
        detail::BufferInfoView buffer{bufferInput};
        detail::BufferInfoView format{formatInput};
        using TChar = typename decltype(format)::TChar;

        detail::ParserNOTextPropertiesExecutor<std::remove_const_t<TChar>> textPropertiesExecutor;
        Context::BasicParserExecutor<std::remove_const_t<TChar>> executor(buffer, textPropertiesExecutor);
        SF_TRY(executor.Run(format, std::forward<Args>(args)...));
        return executor.Terminate();
    }
}
