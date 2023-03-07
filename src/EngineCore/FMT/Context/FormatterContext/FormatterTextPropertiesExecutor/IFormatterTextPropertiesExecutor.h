#pragma once 

#include "EngineCore/FMT/Detail/Detail.h"
#include "EngineCore/FMT/Context/BasicContext/ITextPropertiesExecutor.h"

namespace EngineCore::FMT::Detail
{
    template <typename BufferOutType>
	class IFormatterTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        void SetBuffer(BufferOutType* buffer) { m_Buffer = buffer; }

    protected:
        BufferOutType* m_Buffer;
    };
}
