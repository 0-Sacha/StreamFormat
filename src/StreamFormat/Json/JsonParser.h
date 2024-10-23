#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"

#include "JsonObjects.h"

namespace StreamFormat::JSON::Detail
{
    class JsonParser
    {
    public:
        JsonParser()
            : BufferIn()
        {}

        JsonParser(const FMT::Detail::BufferInfo<const char>& input)
            : BufferIn(input)
        {}

        JsonParser(const char* const buffer, const std::size_t bufferSize)
            : BufferIn(buffer, bufferSize)
        {}

    public:
        inline FMT::Detail::BufferManipResult IsJsonStringBegin() const { return FMT::Detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('"'); }
        inline FMT::Detail::BufferManipResult IsJsonNumberBegin() const { return FMT::Detail::BufferTestAccess<const char>(BufferIn).IsADigit() || FMT::Detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('+', '-', '.'); }
        inline FMT::Detail::BufferManipResult IsJsonBooleanBegin() const { return FMT::Detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('t', 'f'); }
        inline FMT::Detail::BufferManipResult IsJsonStructBegin() const { return FMT::Detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('{'); }
        inline FMT::Detail::BufferManipResult IsJsonArrayBegin() const { return FMT::Detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('['); }
        inline FMT::Detail::BufferManipResult IsJsonNullBegin() const { return FMT::Detail::BufferTestAccess<const char>(BufferIn).IsEqualTo('n'); }

    public:
        FMT::Detail::BufferInfo<const char> BufferIn;

    public:
        struct Intermediate;

    public:
        template <typename T>
        void Parse(T& t);

        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate GetStructIntermediate();
        ArrayIntermediate  GetArrayIntermediate();
    };
}

namespace StreamFormat::JSON::Detail
{
    struct JsonParser::Intermediate
    {
        std::string_view Data;

        void Parse(Detail::JsonParser& parser);

        template <typename T>
        void Parse(T& t)
        {
            JsonParser parser;
            parser.Parse(t);
        }
    };

    struct JsonParser::StructIntermediate
    {
    public:
        friend JsonParser;

    private:
        std::unordered_map<std::string, Detail::JsonParser::Intermediate> Objects;

        void Parse(Detail::JsonParser& parser);

    public:
        template <typename T>
        void Parse(const std::string& name, T& t)
        {
            if (Objects.contains(name) == false) throw Detail::JsonGivenTypeError{};
            Objects[name].Parse(t);
        }
    };

    struct JsonParser::ArrayIntermediate
    {
    public:
        friend JsonParser;

    private:
        std::vector<Detail::JsonParser::Intermediate> Objects;

        void Parse(Detail::JsonParser& parser);

    public:
        template <typename T>
        void Parse(const std::size_t idx, T& t)
        {
            if (idx >= Objects.size()) throw Detail::JsonGivenTypeError{};
            Objects[idx].Parse(t);
        }
    };

    inline JsonParser::StructIntermediate JsonParser::GetStructIntermediate()
    {
        JsonParser::StructIntermediate res;
        res.Parse(*this);
        return res;
    }
    inline JsonParser::ArrayIntermediate JsonParser::GetArrayIntermediate()
    {
        JsonParser::ArrayIntermediate res;
        res.Parse(*this);
        return res;
    }
}
