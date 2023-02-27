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
        static void ParseEscapedQuotedString(BufferInType& buffer, BufferOutType& stringOut)
        {
            buffer.Skip('"');
            while(buffer.IsEnd() == false)
            {
                const CharBuffer* beginString = buffer.GetBufferCurrentPos();
                buffer.GoTo('"', '\\');
                const CharBuffer* endString = buffer.GetBufferCurrentPos();
                stringOut.Append(beginString, endString);

                if (buffer.IsEqualTo('"'))
                    break;
                
                buffer.Skip('\\');
                switch (buffer.Get())
                {
                    // TODO : Do all others escape char
                    case '"': stringOut.PushBack('"'); break;
                    case 't': stringOut.PushBack('\t'); break;
                    case 'r': stringOut.PushBack('\r'); break;
                    case 'n': stringOut.PushBack('\n'); break;
                    default: break;
                }
            }
            buffer.Skip('"');
        }

        static void FormatEscapedQuotedString(BufferOutType& buffer, BufferInType& stringIn)
        {
            buffer.PushBack('"');
            while(stringIn.IsEnd() == false)
            {
                const CharBuffer* beginString = stringIn.GetBufferCurrentPos();
                stringIn.GoTo('\\');
                const CharBuffer* endString = stringIn.GetBufferCurrentPos();
                buffer.Append(beginString, endString);

                if (stringIn.IsEnd()) break;
                
                stringIn.Skip('\\');
                switch (stringIn.Get())
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
