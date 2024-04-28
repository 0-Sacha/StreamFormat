#pragma once

#include "ProjectCore/FMT/Buffer/BasicBufferIn/BasicBufferIn.h"
#include "ProjectCore/FMT/Buffer/BasicBufferOut/BasicBufferOut.h"

#include "ProjectCore/FMT/Buffer/BufferOutManager/DynamicBufferOutManager.h"
#include "ProjectCore/FMT/Buffer/BufferOutManager/StaticBufferOutManager.h"
#include "ProjectCore/FMT/Buffer/BufferOutManager/GivenBufferOutManager.h"

namespace ProjectCore::FMT
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
                stringOut.FastWriteCharBound(beginString, endString);

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
                buffer.FastWriteCharBound(beginString, endString);

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
