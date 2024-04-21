#pragma once 

#include "ProjectCore/FMT/Detail/Detail.h"
#include "ProjectCore/FMT/Context/BasicContext/ITextPropertiesExecutor.h"

namespace ProjectCore::FMT::Detail
{
    template <typename BufferInType>
    class IParserTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        ~IParserTextPropertiesExecutor() override = default;
        
    public:
        void SetBuffer(BufferInType* buffer) { m_Buffer = buffer; }

    protected:
        BufferInType* m_Buffer;
    };
}
