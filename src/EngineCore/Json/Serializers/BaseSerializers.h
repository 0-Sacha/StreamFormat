#pragma once

#include "../JsonObjects.h"
#include "../JsonSerializer.h"

#include "EngineCore/FMT/Detail/Forwarders.h"

#include <utility>

namespace EngineCore::JSON
{
    // Int Types
    template <>
	struct JsonSerializer<std::int8_t>
    {
        static inline void Load(std::int8_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int8_t>>::LoadInt(t, parser);
        }
		static inline void Dump(const std::int8_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int8_t>>::DumpInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::int16_t>
    {
        static inline void Load(std::int16_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int16_t>>::LoadInt(t, parser);
        }
		static inline void Dump(const std::int16_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int16_t>>::DumpInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::int32_t>
    {
        static inline void Load(std::int32_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int32_t>>::LoadInt(t, parser);
        }
		static inline void Dump(const std::int32_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int32_t>>::DumpInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::int64_t>
    {
        static inline void Load(std::int64_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int64_t>>::LoadInt(t, parser);
        }
		static inline void Dump(const std::int64_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::int64_t>>::DumpInt(t, formatter);
        }
    };


    // UInt Types
    template <>
	struct JsonSerializer<std::uint8_t>
    {
        static inline void Load(std::uint8_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint8_t>>::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint8_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint8_t>>::DumpUInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::uint16_t>
    {
        static inline void Load(std::uint16_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint16_t>>::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint16_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint16_t>>::DumpUInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::uint32_t>
    {
        static inline void Load(std::uint32_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint32_t>>::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint32_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint32_t>>::DumpUInt(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<std::uint64_t>
    {
        static inline void Load(std::uint64_t& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint64_t>>::LoadUInt(t, parser);
        }
		static inline void Dump(const std::uint64_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<std::uint64_t>>::DumpUInt(t, formatter);
        }
    };


    // Float Types
    template <>
	struct JsonSerializer<float>
    {
        static inline void Load(float& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<float>>::LoadFloat(t, parser);
        }
		static inline void Dump(const float& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<float>>::DumpFloat(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<double>
    {
        static inline void Load(double& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<double>>::LoadFloat(t, parser);
        }
		static inline void Dump(const double& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<double>>::DumpFloat(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<long double>
    {
        static inline void Load(long double& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonNumber<long double>>::LoadFloat(t, parser);
        }
		static inline void Dump(const long double& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonNumber<long double>>::DumpFloat(t, formatter);
        }
    };


    template <typename Char>
	struct JsonSerializer<FMT::Detail::ForwardAsChar<Char>>
    {
        static inline void Load(Char& t, Detail::JsonParser& parser) {
            parser.BufferIn().Skip('"');
            t = parser.BufferIn().GetAndForward();
            parser.BufferIn().Skip('"'); 
        }
		static inline void Dump(const Char& t, Detail::JsonFormatter& formatter) {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack(t);
            formatter.BufferOut().PushBack('"');
        }
    };
    template <typename Char, std::size_t SIZE>
	struct JsonSerializer<FMT::Detail::ForwardAsCharArray<Char, SIZE>>
    {
        static inline void Load(Char(&t)[SIZE], Detail::JsonParser& parser) {
            parser.BufferIn().Skip('"');
            parser.BufferIn().Skip('"'); 
        }
		static inline void Dump(const Char(&t)[SIZE], Detail::JsonFormatter& formatter) {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack('"');
        }
    };
    template <typename Char>
	struct JsonSerializer<FMT::Detail::ForwardAsCharPointer<Char>>
    {
        static inline void Load(Char* t, Detail::JsonParser& parser) {
            parser.BufferIn().Skip('"');
            parser.BufferIn().Skip('"'); 
        }
		static inline void Dump(const Char* t, Detail::JsonFormatter& formatter) {
            formatter.BufferOut().PushBack('"');
            formatter.BufferOut().PushBack('"');
        }
    };

    template <>
	struct JsonSerializer<char>
    {
        static inline void Load(char& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char>>::Load(t, parser);
        }
		static inline void Dump(const char& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<wchar_t>
    {
        static inline void Load(wchar_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<wchar_t>>::Load(t, parser);
        }
		static inline void Dump(const wchar_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<wchar_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char8_t>
    {
        static inline void Load(char8_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char8_t>>::Load(t, parser);
        }
		static inline void Dump(const char8_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char8_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char16_t>
    {
        static inline void Load(char16_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char16_t>>::Load(t, parser);
        }
		static inline void Dump(const char16_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char16_t>>::Dump(t, formatter);
        }
    };
    template <>
	struct JsonSerializer<char32_t>
    {
        static inline void Load(char32_t& t, Detail::JsonParser& parser) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char32_t>>::Load(t, parser);
        }
		static inline void Dump(const char32_t& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<FMT::Detail::ForwardAsChar<char32_t>>::Dump(t, formatter);
        }
    };



}
