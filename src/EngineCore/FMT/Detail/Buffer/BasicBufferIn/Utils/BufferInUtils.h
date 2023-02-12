#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferIn/BasicBufferIn.h"
#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/BasicBufferOut.h"

namespace EngineCore::FMT
{
    template<typename CharBuffer>
    class BufferInUtils
    {
    public:
        using BufferInType = Detail::BasicBufferIn<CharBuffer>;
        using BufferOutType = Detail::BasicBufferOut<CharBuffer>;

    public:
        static std::basic_string<CharBuffer> ParseEscapedQuotedString(BufferInType& buffer)
        {
            std::basic_string<CharBuffer> res;
            buffer.Skip('"');
            while(buffer.IsEnd() == false)
            {
                const CharBuffer* beginString = buffer.GetBufferCurrentPos();
                buffer.GoTo('"', '\\');
                const CharBuffer* endString = buffer.GetBufferCurrentPos();
                res.append(beginString, endString);

                if (buffer.IsEqualTo('"'))
                    break;
                
                buffer.Skip('\\');
                switch (buffer.Get())
                {
                    // TODO : Do all others escape char
                    case '"': res.push_back('"'); break;
                    case 't': res.push_back('\t'); break;
                    case 'r': res.push_back('\r'); break;
                    case 'n': res.push_back('\n'); break;
                    default: break;
                }
            }
            buffer.Skip('"');
            return res;
        }
    };
}
