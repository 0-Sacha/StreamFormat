#pragma once

#include "BasicParserContext-impl.h"
#include "BasicParserContext.h"

#include "ProjectCore/FMT/Buffer/BufferOutManager/GivenBufferOutManager.h"
#include "ProjectCore/FMT/Buffer/BufferOutManager/StaticBufferOutManager.h"

#include "ParserTextPropertiesExecutor/ParserANSITextPropertiesExecutor.h"

namespace ProjectCore::FMT
{
    template <typename FormatData = std::string_view, typename BufferData = FormatData, typename... Args>
    requires(Detail::CanBeUseForFMTBufferIn<FormatData>&& Detail::CanBeUseForFMTBufferIn<BufferData>) void Parse(const BufferData& bufferData, const FormatData& formatData,
                                                                                                                 Args&&... args)
    {
        using ContextType         = Context::BasicParserContext<typename Detail::FMTCharTypeFromBuffer<FormatData>::Type, typename Detail::FMTCharTypeFromBuffer<BufferData>::Type>;
        auto contextArgsInterface = Detail::ParserContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
        Detail::BufferInProperties<typename Detail::FMTCharTypeFromBuffer<FormatData>::Type> formatProperties(formatData);
        Detail::FMTFormatBuffer<typename Detail::FMTCharTypeFromBuffer<FormatData>::Type>    format(formatProperties);
        Detail::ParserANSITextPropertiesExecutor<typename ContextType::BufferInType>         textPropertiesExecutor;
        Detail::BufferInProperties<typename Detail::FMTCharTypeFromBuffer<BufferData>::Type> bufferProperties(bufferData);
        ContextType                                                                          context(bufferProperties, textPropertiesExecutor);
        context.Run(format, &contextArgsInterface);
        context.Terminate();
    }
}
