#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/BasicBufferOut.h"
#include "JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    class JsonFormatter
    {
    public:
        using JsonBufferOut = EngineCore::FMT::Detail::BasicBufferOut<char>;

    public:
        JsonFormatter(EngineCore::FMT::Detail::BasicBufferManager<char>& bufferManager)
            : m_BufferOut(bufferManager)
            , m_Indent(0)
            , m_IndentSize(4)
            , m_IndentWithSpaces(true)
            , m_OneLine(false)
        {}

    public:
        JsonBufferOut& BufferOut() { return m_BufferOut; }
        const JsonBufferOut& BufferOut() const { return m_BufferOut; }

    protected:
        JsonBufferOut m_BufferOut;

    public:
        template <typename T>
        void Format(const T& t);

        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate GetStructIntermediate();
        ArrayIntermediate GetArrayIntermediate();

    public:
        void Indent()
        {
            if (m_OneLine) return;

            if (m_IndentWithSpaces)
                m_BufferOut.PushBack(' ', m_Indent * m_IndentSize);
            else
                m_BufferOut.PushBack('\t', m_Indent * m_IndentSize);
        }

        void NewLine()          { if (m_OneLine) return; m_BufferOut.PushBack('\n'); Indent(); }
        void BeginNewObject()   { ++m_Indent; }
        void EndNewObject()     { --m_Indent; }

    protected:
        std::size_t m_Indent;
        std::size_t m_IndentSize;
		bool m_IndentWithSpaces;
		bool m_OneLine;
    };
}

namespace EngineCore::JSON::Detail
{
    struct JsonFormatter::StructIntermediate
    {
    public:
        StructIntermediate(JsonFormatter& formatter);
        ~StructIntermediate();

    public:
        template<typename T>
        void Format(const std::string& name, const T& t);

    public:
        JsonFormatter& Formatter;
        std::uint32_t Idx;
    };

    struct JsonFormatter::ArrayIntermediate
    {
    public:
        ArrayIntermediate(JsonFormatter& formatter);
        ~ArrayIntermediate();

    public:
        template<typename T>
        void Format(const T& t);

    public:
        JsonFormatter& Formatter;
        std::uint32_t Idx;
    };

    inline JsonFormatter::StructIntermediate JsonFormatter::GetStructIntermediate()
    {
        return JsonFormatter::StructIntermediate(*this);
    }

    inline JsonFormatter::ArrayIntermediate JsonFormatter::GetArrayIntermediate()
    {
        return JsonFormatter::ArrayIntermediate(*this);
    }
}
