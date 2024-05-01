#pragma once

#include "ProjectCore/FMT/Buffer/BasicBufferIn/BasicBufferIn.h"
#include "ProjectCore/FMT/Buffer/BufferInProperties/BufferInProperties.h"

#include "JsonObjects.h"

namespace ProjectCore::JSON::Detail
{
    class JsonParser
    {
    public:
        using JsonBufferIn = FMT::Detail::BasicBufferIn<char>;

    public:
        JsonParser()
            : m_BufferIn()
        {}
        
        JsonParser(const FMT::Detail::BufferInProperties<char>& bufferInProperties)
            : m_BufferIn(bufferInProperties)
        {}

        JsonParser(const char* const buffer, const std::size_t bufferSize)
            : m_BufferIn(buffer, bufferSize)
        {}

    public:
        inline bool IsJsonStringBegin() const       { return m_BufferIn.IsEqualTo('"'); }
        inline bool IsJsonNumberBegin() const       { return m_BufferIn.IsADigit() || m_BufferIn.IsEqualTo('+', '-', '.'); }
        inline bool IsJsonBooleanBegin() const      { return m_BufferIn.IsEqualTo('t', 'f'); }
        inline bool IsJsonStructBegin() const       { return m_BufferIn.IsEqualTo('{'); }
        inline bool IsJsonArrayBegin() const        { return m_BufferIn.IsEqualTo('['); }
        inline bool IsJsonNullBegin() const         { return m_BufferIn.IsEqualTo('n'); }

    public:
        JsonBufferIn& BufferIn()                { return m_BufferIn; }
        const JsonBufferIn& BufferIn() const    { return m_BufferIn; }

    protected:
        JsonBufferIn m_BufferIn;

    public:
        struct Intermediate;

    public:
        template <typename T>
        void Parse(T& t);
 
        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate GetStructIntermediate();
        ArrayIntermediate GetArrayIntermediate();
    };
}

namespace ProjectCore::JSON::Detail
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
            if (Objects.contains(name) == false)
                throw Detail::JsonGivenTypeError{};
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
            if (idx >= Objects.size())
                throw Detail::JsonGivenTypeError{};
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
