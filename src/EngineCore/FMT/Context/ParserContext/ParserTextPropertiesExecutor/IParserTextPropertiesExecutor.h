#pragma once 

#include "EngineCore/FMT/Detail/Detail.h"
#include "EngineCore/FMT/Context/BasicContext/ITextPropertiesExecutor.h"

namespace EngineCore::FMT::Detail
{
    template <typename BufferInType>
	class IParserTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        void SetBuffer(BufferInType* buffer) { m_Buffer = buffer; }

    protected:
        BufferInType* m_Buffer;
    };
}
