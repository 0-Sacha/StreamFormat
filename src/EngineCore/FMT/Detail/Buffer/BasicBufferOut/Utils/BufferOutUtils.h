#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/BasicBufferOut.h"
#include "EngineCore/FMT/Detail/Buffer/BasicBufferIn/BasicBufferIn.h"

namespace EngineCore::FMT
{
    template<typename CharBuffer>
    class BufferOutUtils
    {
    public:
        using BufferOutType = Detail::BasicBufferOut<CharBuffer>;
        using BufferInType = Detail::BasicBufferIn<CharBuffer>;

    public:
        static void WriteEscapedQuotedString(BufferOutType& buffer, const std::basic_string<CharBuffer>& str)
        {
            buffer.PushBack('"');
            BufferInType strAsBuffer(str.data(), str.size());

            while(strAsBuffer.IsEnd() == false)
            {
                const CharBuffer* beginString = strAsBuffer.GetBufferCurrentPos();
                strAsBuffer.GoTo('\\');
                const CharBuffer* endString = strAsBuffer.GetBufferCurrentPos();
                buffer.Append(beginString, endString);

                if (strAsBuffer.IsEnd()) break;
                
                strAsBuffer.Skip('\\');
                switch (strAsBuffer.Get())
                {
                    // TODO : Do all others escape char
                    case '"': buffer.PushBack('"'); break;
                    case 't': buffer.PushBack('\t'); break;
                    case 'r': buffer.PushBack('\r'); break;
                    case 'n': buffer.PushBack('\n'); break;
                    default: break;
                }
            }

            buffer.PushBack('"');
        }
    };
}
