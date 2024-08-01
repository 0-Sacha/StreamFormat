#pragma once

#include "JsonObjects.h"
#include "StreamFormat/FMT/Buffer/BasicBufferOut/BasicBufferOut.h"

namespace StreamFormat::JSON::Detail
{
    class JsonFormatter
    {
    public:
        using JsonBufferOut = StreamFormat::FMT::Detail::BasicBufferOut<char>;

        struct FormatSettings
        {
            std::size_t                              IndentSize       = 4;
            bool                                     IndentWithSpaces = true;
            bool                                     OneLine          = false;
            bool                                     OrderedStruct    = false;
            StreamFormat::FMT::Detail::FloatPrecision FloatPrecision   = 7;
        };

    public:
        JsonFormatter(StreamFormat::FMT::Detail::BasicBufferOutManager<char>& BufferOutManager)
            : m_BufferOut(BufferOutManager)
            , m_Indent(0)
            , m_Settings()
        {}
        JsonFormatter(StreamFormat::FMT::Detail::BasicBufferOutManager<char>& BufferOutManager, FormatSettings settings)
            : m_BufferOut(BufferOutManager)
            , m_Indent(0)
            , m_Settings(settings)
        {}

    public:
        JsonBufferOut&       BufferOut() { return m_BufferOut; }
        const JsonBufferOut& BufferOut() const { return m_BufferOut; }

        FormatSettings&       Settings() { return m_Settings; }
        const FormatSettings& Settings() const { return m_Settings; }

    public:
        template <typename T>
        void Format(const T& t);

        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate GetStructIntermediate();
        ArrayIntermediate  GetArrayIntermediate();

    public:
        void Indent()
        {
            if (m_Settings.OneLine) return;

            if (m_Settings.IndentWithSpaces)
                m_BufferOut.PushBack(' ', m_Indent * m_Settings.IndentSize);
            else
                m_BufferOut.PushBack('\t', m_Indent * m_Settings.IndentSize);
        }

        void NewLine()
        {
            if (m_Settings.OneLine) return;
            m_BufferOut.PushBack('\n');
            Indent();
        }
        void BeginNewObject() { ++m_Indent; }
        void EndNewObject() { --m_Indent; }

    protected:
        JsonBufferOut  m_BufferOut;
        std::size_t    m_Indent;
        FormatSettings m_Settings;
    };
}

namespace StreamFormat::JSON::Detail
{
    struct JsonFormatter::StructIntermediate
    {
    public:
        StructIntermediate(JsonFormatter& formatter);
        ~StructIntermediate();

    public:
        template <typename T>
        void Format(const std::string_view name, const T& t);

    public:
        JsonFormatter& Formatter;
        std::uint32_t  Idx;
    };

    struct JsonFormatter::ArrayIntermediate
    {
    public:
        ArrayIntermediate(JsonFormatter& formatter);
        ~ArrayIntermediate();

    public:
        template <typename T>
        void Format(const T& t);

    public:
        JsonFormatter& Formatter;
        std::uint32_t  Idx;
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
