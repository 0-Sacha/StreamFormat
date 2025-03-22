#pragma once

#include "stream/fmt/buffer/buffer_info.h"

#include "JsonObjects.h"

namespace stream::JSON::detail
{
    class JsonParser
    {
    public:
        JsonParser()
            : BufferIn()
        {}

        JsonParser(fmt::detail::BufferInfoView<char>& input)
            : BufferIn(input)
        {}

    public:
        inline bool IsJsonStringBegin() const { return fmt::detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('"'); }
        inline bool IsJsonNumberBegin() const { return fmt::detail::BufferTestAccess<const char>(BufferIn).IsADigit() || fmt::detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('+', '-', '.'); }
        inline bool IsJsonBooleanBegin() const { return fmt::detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('t', 'f'); }
        inline bool IsJsonStructBegin() const { return fmt::detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('{'); }
        inline bool IsJsonArrayBegin() const { return fmt::detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('['); }
        inline bool IsJsonNullBegin() const { return fmt::detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('n'); }

    public:
        fmt::detail::BufferInfo<const char> BufferIn;

    public:
        struct Intermediate;

    public:
        template <typename T>
        void parse(T& t);

        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate GetStructIntermediate();
        ArrayIntermediate  GetArrayIntermediate();
    };
}

namespace stream::JSON::detail
{
    struct JsonParser::Intermediate
    {
        std::string_view Data;

        void parse(detail::JsonParser& parser);

        template <typename T>
        void parse(T& t)
        {
            JsonParser parser;
            parser.parse(t);
        }
    };

    struct JsonParser::StructIntermediate
    {
    public:
        friend JsonParser;

    private:
        std::unordered_map<std::string, detail::JsonParser::Intermediate> Objects;

        void parse(detail::JsonParser& parser);

    public:
        template <typename T>
        void parse(const std::string& name, T& t)
        {
            if (Objects.contains(name) == false) throw detail::JsonGivenTypeError{};
            Objects[name].parse(t);
        }
    };

    struct JsonParser::ArrayIntermediate
    {
    public:
        friend JsonParser;

    private:
        std::vector<detail::JsonParser::Intermediate> Objects;

        void parse(detail::JsonParser& parser);

    public:
        template <typename T>
        void parse(const std::size_t idx, T& t)
        {
            if (idx >= Objects.size()) throw detail::JsonGivenTypeError{};
            Objects[idx].parse(t);
        }
    };

    inline JsonParser::StructIntermediate JsonParser::GetStructIntermediate()
    {
        JsonParser::StructIntermediate res;
        res.parse(*this);
        return res;
    }
    inline JsonParser::ArrayIntermediate JsonParser::GetArrayIntermediate()
    {
        JsonParser::ArrayIntermediate res;
        res.parse(*this);
        return res;
    }
}
