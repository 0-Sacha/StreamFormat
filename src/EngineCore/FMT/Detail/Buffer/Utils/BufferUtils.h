#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferIn/BasicBufferIn.h"
#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/BasicBufferOut.h"

#include "EngineCore/FMT/Detail/Buffer/BufferManager/DynamicBufferManager.h"
#include "EngineCore/FMT/Detail/Buffer/BufferManager/StaticBufferManager.h"
#include "EngineCore/FMT/Detail/Buffer/BufferManager/GivenBufferManager.h"

namespace EngineCore::FMT
{
    template<typename CharBuffer>
    class BufferUtils
    {
    public:
        using BufferInType = Detail::BasicBufferIn<CharBuffer>;
        using BufferOutType = Detail::BasicBufferOut<CharBuffer>;

    public:
        static void ParseEscapedQuotedString(BufferInType& buffer, BufferOutType& dataOut)
        {
            buffer.Skip('"');
            while(buffer.IsEnd() == false)
            {
                const CharBuffer* beginString = buffer.GetBufferCurrentPos();
                buffer.GoTo('"', '\\');
                const CharBuffer* endString = buffer.GetBufferCurrentPos();
                dataOut.Append(beginString, endString);

                if (buffer.IsEqualTo('"'))
                    break;
                
                buffer.Skip('\\');
                switch (buffer.Get())
                {
                    // TODO : Do all others escape char
                    case '"': dataOut.PushBack('"'); break;
                    case 't': dataOut.PushBack('\t'); break;
                    case 'r': dataOut.PushBack('\r'); break;
                    case 'n': dataOut.PushBack('\n'); break;
                    default: break;
                }
            }
            buffer.Skip('"');
        }

        static void WriteEscapedQuotedString(BufferOutType& buffer, BufferInType& dataIn)
        {
            buffer.PushBack('"');
            while(dataIn.IsEnd() == false)
            {
                const CharBuffer* beginString = dataIn.GetBufferCurrentPos();
                dataIn.GoTo('\\');
                const CharBuffer* endString = dataIn.GetBufferCurrentPos();
                buffer.Append(beginString, endString);

                if (dataIn.IsEnd()) break;
                
                dataIn.Skip('\\');
                switch (dataIn.Get())
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
