#pragma once

#include "JsonObjects.h"
#include "stream/fmt/buffer/buffer_out_manip.h"

namespace stream::JSON::detail
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
        JsonFormatter(stream::fmt::detail::BufferOutInfo<char>& bufferOut)
            : BufferOut(bufferOut)
            , Settings()
            , m_Indent(0)
        {}
        JsonFormatter(stream::fmt::detail::BufferOutInfo<char>& bufferOut, FormatSettings settings)
            : BufferOut(bufferOut)
            , Settings(settings)
            , m_Indent(0)
        {}

    public:
        template <typename T>
        void format(const T& t);

        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate GetStructIntermediate();
        ArrayIntermediate  GetArrayIntermediate();

    public:
        void Indent()
        {
            if (Settings.OneLine) return;

            if (Settings.IndentWithSpaces)
                fmt::detail::BufferOutManip(BufferOut).Pushback(' ', m_Indent * Settings.IndentSize).value();
            else
                fmt::detail::BufferOutManip(BufferOut).Pushback('\t', m_Indent * Settings.IndentSize).value();
        }

        void NewLine()
        {
            if (Settings.OneLine) return;
            fmt::detail::BufferOutManip(BufferOut).Pushback('\n').value();
            Indent();
        }
        void BeginNewObject() { ++m_Indent; }
        void EndNewObject() { --m_Indent; }

    public:
        stream::fmt::detail::BufferOutInfo<char>&  BufferOut;
        FormatSettings Settings;
    
    protected:
        std::size_t    m_Indent;
    };
}

namespace stream::JSON::detail
{
    struct JsonFormatter::StructIntermediate
    {
    public:
        StructIntermediate(JsonFormatter& formatter);
        ~StructIntermediate();

    public:
        template <typename T>
        void format(const std::string_view name, const T& t);

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
        void format(const T& t);

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
