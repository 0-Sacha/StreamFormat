#pragma once

#include "../JsonObjects.h"
#include "../JsonSerializer.h"

#include "ProjectCore/FMT/Detail/Forwarders.h"

#include <utility>

namespace ProjectCore::JSON
{
    // Int Types
    template <>
    struct JsonSerializer<std::int8_t>
    {
        static inline void Parse(std::int8_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseInt(t, parser); }
        static inline void Format(const std::int8_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatInt(t, formatter); }
    };
    template <>
    struct JsonSerializer<std::int16_t>
    {
        static inline void Parse(std::int16_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseInt(t, parser); }
        static inline void Format(const std::int16_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatInt(t, formatter); }
    };
    template <>
    struct JsonSerializer<std::int32_t>
    {
        static inline void Parse(std::int32_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseInt(t, parser); }
        static inline void Format(const std::int32_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatInt(t, formatter); }
    };
    template <>
    struct JsonSerializer<std::int64_t>
    {
        static inline void Parse(std::int64_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseInt(t, parser); }
        static inline void Format(const std::int64_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatInt(t, formatter); }
    };
    template <>
    struct JsonObjectSerializer<std::int8_t>
    {
        static inline void ReadObject(std::int8_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::int8_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<std::int16_t>
    {
        static inline void ReadObject(std::int16_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::int16_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<std::int32_t>
    {
        static inline void ReadObject(std::int32_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::int32_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<std::int64_t>
    {
        static inline void ReadObject(std::int64_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::int64_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };

    // UInt Types
    template <>
    struct JsonSerializer<std::uint8_t>
    {
        static inline void Parse(std::uint8_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseUInt(t, parser); }
        static inline void Format(const std::uint8_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatUInt(t, formatter); }
    };
    template <>
    struct JsonSerializer<std::uint16_t>
    {
        static inline void Parse(std::uint16_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseUInt(t, parser); }
        static inline void Format(const std::uint16_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatUInt(t, formatter); }
    };
    template <>
    struct JsonSerializer<std::uint32_t>
    {
        static inline void Parse(std::uint32_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseUInt(t, parser); }
        static inline void Format(const std::uint32_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatUInt(t, formatter); }
    };
    template <>
    struct JsonSerializer<std::uint64_t>
    {
        static inline void Parse(std::uint64_t& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseUInt(t, parser); }
        static inline void Format(const std::uint64_t& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatUInt(t, formatter); }
    };
    template <>
    struct JsonObjectSerializer<std::uint8_t>
    {
        static inline void ReadObject(std::uint8_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::uint8_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<std::uint16_t>
    {
        static inline void ReadObject(std::uint16_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::uint16_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<std::uint32_t>
    {
        static inline void ReadObject(std::uint32_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::uint32_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<std::uint64_t>
    {
        static inline void ReadObject(std::uint64_t& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const std::uint64_t& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };

    // Float Types
    template <>
    struct JsonSerializer<float>
    {
        static inline void Parse(float& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseFloat(t, parser); }
        static inline void Format(const float& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatFloat(t, formatter); }
    };
    template <>
    struct JsonSerializer<double>
    {
        static inline void Parse(double& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseFloat(t, parser); }
        static inline void Format(const double& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatFloat(t, formatter); }
    };
    template <>
    struct JsonSerializer<long double>
    {
        static inline void Parse(long double& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseFloat(t, parser); }
        static inline void Format(const long double& t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatFloat(t, formatter); }
    };
    template <>
    struct JsonObjectSerializer<float>
    {
        static inline void ReadObject(float& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const float& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<double>
    {
        static inline void ReadObject(double& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const double& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };
    template <>
    struct JsonObjectSerializer<long double>
    {
        static inline void ReadObject(long double& t, const JsonObject& object) { t = object.As<JsonNumberObject>().Number; }
        static inline void WriteObject(const long double& t, JsonObject& object) { object.As<JsonNumberObject>().Number = t; }
    };

    template <typename Char>
    struct JsonSerializer<FMT::Detail::ForwardAsChar<Char>>
    {
        static inline void Parse(Char& t, Detail::JsonParser& parser)
        {
            parser.BufferIn().Skip('"');
            t = static_cast<Char>(parser.BufferIn().GetAndForward());
            parser.BufferIn().Skip('"');
        }
        static inline void Format(const Char& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack(static_cast<char>(t));
            formatter.BufferOut().PushBack('"');
        }
    };
    template <typename Char, std::size_t SIZE>
    struct JsonSerializer<FMT::Detail::ForwardAsCharArray<Char, SIZE>>
    {
        static inline void Parse([[maybe_unused]] Char (&t)[SIZE], Detail::JsonParser& parser)
        {
            parser.BufferIn().Skip('"');
            parser.BufferIn().Skip('"');
        }
        static inline void Format([[maybe_unused]] const Char (&t)[SIZE], Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack('"');
        }
    };
    template <typename Char>
    struct JsonSerializer<FMT::Detail::ForwardAsCharPointer<Char>>
    {
        static inline void Parse([[maybe_unused]] Char* t, Detail::JsonParser& parser)
        {
            parser.BufferIn().Skip('"');
            parser.BufferIn().Skip('"');
        }
        static inline void Format([[maybe_unused]] const Char* t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack('"');
        }
    };

    template <>
    struct JsonSerializer<char>
    {
        static inline void Parse(char& t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsChar<char>>::Parse(t, parser); }
        static inline void Format(const char& t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsChar<char>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<wchar_t>
    {
        static inline void Parse(wchar_t& t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsChar<wchar_t>>::Parse(t, parser); }
        static inline void Format(const wchar_t& t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsChar<wchar_t>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<char8_t>
    {
        static inline void Parse(char8_t& t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsChar<char8_t>>::Parse(t, parser); }
        static inline void Format(const char8_t& t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsChar<char8_t>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<char16_t>
    {
        static inline void Parse(char16_t& t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsChar<char16_t>>::Parse(t, parser); }
        static inline void Format(const char16_t& t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsChar<char16_t>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<char32_t>
    {
        static inline void Parse(char32_t& t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsChar<char32_t>>::Parse(t, parser); }
        static inline void Format(const char32_t& t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsChar<char32_t>>::Format(t, formatter); }
    };

    template <std::size_t SIZE>
    struct JsonSerializer<char[SIZE]>
    {
        static inline void Parse(char (&t)[SIZE], Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharArray<char, SIZE>>::Parse(t, parser); }
        static inline void Format(const char (&t)[SIZE], Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsCharArray<char, SIZE>>::Format(t, formatter); }
    };
    template <std::size_t SIZE>
    struct JsonSerializer<wchar_t[SIZE]>
    {
        static inline void Parse(wchar_t (&t)[SIZE], Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharArray<wchar_t, SIZE>>::Parse(t, parser); }
        static inline void Format(const wchar_t (&t)[SIZE], Detail::JsonFormatter& formatter)
        {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<wchar_t, SIZE>>::Format(t, formatter);
        }
    };
    template <std::size_t SIZE>
    struct JsonSerializer<char8_t[SIZE]>
    {
        static inline void Parse(char8_t (&t)[SIZE], Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharArray<char8_t, SIZE>>::Parse(t, parser); }
        static inline void Format(const char8_t (&t)[SIZE], Detail::JsonFormatter& formatter)
        {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char8_t, SIZE>>::Format(t, formatter);
        }
    };
    template <std::size_t SIZE>
    struct JsonSerializer<char16_t[SIZE]>
    {
        static inline void Parse(char16_t (&t)[SIZE], Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharArray<char16_t, SIZE>>::Parse(t, parser); }
        static inline void Format(const char16_t (&t)[SIZE], Detail::JsonFormatter& formatter)
        {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char16_t, SIZE>>::Format(t, formatter);
        }
    };
    template <std::size_t SIZE>
    struct JsonSerializer<char32_t[SIZE]>
    {
        static inline void Parse(char32_t (&t)[SIZE], Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharArray<char32_t, SIZE>>::Parse(t, parser); }
        static inline void Format(const char32_t (&t)[SIZE], Detail::JsonFormatter& formatter)
        {
            JsonSerializer<FMT::Detail::ForwardAsCharArray<char32_t, SIZE>>::Format(t, formatter);
        }
    };

    template <>
    struct JsonSerializer<char*>
    {
        static inline void Parse(char* t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char>>::Parse(t, parser); }
        static inline void Format(const char* t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<wchar_t*>
    {
        static inline void Parse(wchar_t* t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<wchar_t>>::Parse(t, parser); }
        static inline void Format(const wchar_t* t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<wchar_t>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<char8_t*>
    {
        static inline void Parse(char8_t* t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char8_t>>::Parse(t, parser); }
        static inline void Format(const char8_t* t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char8_t>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<char16_t*>
    {
        static inline void Parse(char16_t* t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char16_t>>::Parse(t, parser); }
        static inline void Format(const char16_t* t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char16_t>>::Format(t, formatter); }
    };
    template <>
    struct JsonSerializer<char32_t*>
    {
        static inline void Parse(char32_t* t, Detail::JsonParser& parser) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char32_t>>::Parse(t, parser); }
        static inline void Format(const char32_t* t, Detail::JsonFormatter& formatter) { JsonSerializer<FMT::Detail::ForwardAsCharPointer<char32_t>>::Format(t, formatter); }
    };

    template <typename T>
    struct JsonSerializer<T*>
    {
        static inline void Parse(T* t, Detail::JsonParser& parser)
        {
            if (t == nullptr) throw Detail::JsonGivenTypeError{};
            JsonSerializer<T>::Parse(*t, parser);
        }
        static inline void Format(const T* t, Detail::JsonFormatter& formatter)
        {
            if (t == nullptr) throw Detail::JsonGivenTypeError{};
            JsonSerializer<T>::Format(*t, formatter);
        }
    };

    template <typename T, std::size_t SIZE>
    struct JsonSerializer<T[SIZE]>
    {
        using ArraySubObjectType = T;

        static inline void Parse(T (&t)[SIZE], Detail::JsonParser& parser) { JsonArraySerializer::LoadAllSubObjects<T[SIZE]>(t, parser); }
        static inline void AddArraySubObject(T (&t)[SIZE], std::size_t idx, ArraySubObjectType&& subObject) { t[idx] = std::move(subObject); }

        static inline void Format(const T (&t)[SIZE], Detail::JsonFormatter& formatter)
        {
            JsonArraySerializer::FormatBegin(formatter);
            for (std::size_t idx = 0; idx < SIZE; ++idx)
                JsonArraySerializer::FormatObject(t[idx], idx, formatter);
            JsonArraySerializer::FormatEnd(formatter);
        }
    };
}
