#pragma once 

#include "ProjectCore/FMT/Detail/Detail.h"
#include "ProjectCore/FMT/Context/BasicContext/ITextPropertiesExecutor.h"

namespace ProjectCore::FMT::Detail
{
    template <typename BufferOutType>
	class IFormatterTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        ~IFormatterTextPropertiesExecutor() override = default;
    
    public:
        void SetBuffer(BufferOutType* buffer) { m_Buffer = buffer; }

    protected:
        BufferOutType* m_Buffer;
    };
}
