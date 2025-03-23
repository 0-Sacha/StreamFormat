#pragma once

#include "stream/fmt/buf/stream.h"

#include "json_objects.h"

namespace stream::json::detail
{
    class JsonParser
    {
    public:
        JsonParser()
            : istream()
        {}

        JsonParser(fmt::buf::StreamView<char>& input)
            : istream(input)
        {}

    public:
        inline bool is_json_string_begin() const { return fmt::buf::TestAccess<const char>(istream).is_equal_to('"'); }
        inline bool is_json_number_begin() const { return fmt::buf::TestAccess<const char>(istream).is_a_digit() || fmt::buf::TestAccess<const char>(istream).is_equal_to('+', '-', '.'); }
        inline bool is_json_boolean_begin() const { return fmt::buf::TestAccess<const char>(istream).is_equal_to('t', 'f'); }
        inline bool is_json_struct_begin() const { return fmt::buf::TestAccess<const char>(istream).is_equal_to('{'); }
        inline bool is_json_array_begin() const { return fmt::buf::TestAccess<const char>(istream).is_equal_to('['); }
        inline bool is_json_null_begin() const { return fmt::buf::TestAccess<const char>(istream).is_equal_to('n'); }

    public:
        fmt::buf::Stream<const char> istream;

    public:
        struct Intermediate;

    public:
        template <typename T>
        void parse(T& t);

        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate get_struct_intermediate();
        ArrayIntermediate  get_array_intermediate();
    };
}

namespace stream::json::detail
{
    struct JsonParser::Intermediate
    {
        std::string_view data;

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

    inline JsonParser::StructIntermediate JsonParser::get_struct_intermediate()
    {
        JsonParser::StructIntermediate res;
        res.parse(*this);
        return res;
    }
    inline JsonParser::ArrayIntermediate JsonParser::get_array_intermediate()
    {
        JsonParser::ArrayIntermediate res;
        res.parse(*this);
        return res;
    }
}
