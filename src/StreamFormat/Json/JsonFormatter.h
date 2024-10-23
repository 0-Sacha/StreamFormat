#pragma once

#include "JsonObjects.h"
#include "StreamFormat/FMT/Buffer/BufferOutManip.h"

namespace StreamFormat::JSON::Detail
{
    class JsonFormatter
    {
    public:
        struct FormatSettings
        {
            std::size_t  IndentSize       = 4;
            bool         IndentWithSpaces = true;
            bool         OneLine          = false;
            bool         OrderedStruct    = false;
            std::int32_t FloatPrecision   = 7;
        };

    public:
        JsonFormatter(StreamFormat::FMT::Detail::BufferOutInfo<char>& bufferOut)
            : BufferOut(bufferOut)
            , Settings()
            , m_Indent(0)
        {}
        JsonFormatter(StreamFormat::FMT::Detail::BufferOutInfo<char>& bufferOut, FormatSettings settings)
            : BufferOut(bufferOut)
            , Settings(settings)
            , m_Indent(0)
        {}

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
            if (Settings.OneLine) return;

            if (Settings.IndentWithSpaces)
                FMT::Detail::BufferOutManip(BufferOut).Pushback(' ', m_Indent * Settings.IndentSize);
            else
                FMT::Detail::BufferOutManip(BufferOut).Pushback('\t', m_Indent * Settings.IndentSize);
        }

        void NewLine()
        {
            if (Settings.OneLine) return;
            FMT::Detail::BufferOutManip(BufferOut).Pushback('\n');
            Indent();
        }
        void BeginNewObject() { ++m_Indent; }
        void EndNewObject() { --m_Indent; }

    public:
        StreamFormat::FMT::Detail::BufferOutInfo<char>&  BufferOut;
        FormatSettings Settings;
    
    protected:
        std::size_t    m_Indent;
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
