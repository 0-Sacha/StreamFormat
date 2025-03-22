#pragma once

#include "JsonFormatter.h"
#include "JsonParser.h"

#include "stream/fmt.h"
#include "stream/fmt/buffer/buffer_read_manip.h"
#include "stream/fmt/buffer/buffer_write_manip.h"
#include "stream/fmt/buffer/utils/buffer_utils.h"

#include <functional>
#include <string>

namespace stream::JSON
{
    template <typename T>
    struct JsonSerializer
    {
        static inline void parse(T&, detail::JsonParser&)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            fmt::FilePrint(std::cerr, "{C:red}JsonSerializer::Parse<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }

        static inline void format(const T&, detail::JsonFormatter& formatter)
        {
            fmt::detail::BufferWriteManip(formatter.buffer_out).FastWriteString(std::string_view("Unknown JsonFormatter for type : ")).value();
            fmt::detail::BufferWriteManip(formatter.buffer_out).FastWriteString(std::string_view(typeid(T).name())).value();

#ifdef UNKOWN_TYPE_MESSAGE
            fmt::FilePrint(std::cerr, "{C:red}JsonSerializer::Format<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }
    };

    template <typename T>
    struct JsonObjectSerializer
    {
        static inline void ReadObject(T&, const JsonObject&)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            fmt::FilePrint(std::cerr, "{C:red}JsonObjectSerializer::ReadObject<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }

        static inline void WriteObject(const T&, JsonObject&)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            fmt::FilePrint(std::cerr, "{C:red}JsonObjectSerializer::WriteObject<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }
    };

    struct JsonStringSerializer
    {
        static inline void ParseSTDString(std::string& t, detail::JsonParser& parser)
        {
            fmt::detail::DynamicBufferOutManager<char> bufferData;
            fmt::detail::BufferOutInfo<char> buffer = fmt::detail::BufferOutInfo<char>::Create(bufferData).value();
            fmt::detail::BufferUtils::parse_escaped_quoted_string(parser.BufferIn, buffer).value();
            fmt::detail::BufferOutManip(buffer).ComputeGeneratedSize();
            t = bufferData.GetLastGeneratedString();
        }

        static inline void FormatSTDString(const std::string_view t, detail::JsonFormatter& formatter)
        {
            fmt::detail::BufferInfo<const char> buffer(t.data(), t.size());
            fmt::detail::BufferUtils::FormatEscapedQuotedString(formatter.buffer_out, buffer).value();
        }
    };

    struct JsonNumberSerializer
    {
        template <typename FloatType>
        static inline void ParseFloat(FloatType& t, detail::JsonParser& parser)
        {
            fmt::detail::BufferReadManip(parser.BufferIn).FastReadFloat(t).value();
        }

        template <typename IntType>
        static inline void ParseInteger(IntType& t, detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn.CurrentPos;
            float tmp = 0;
            fmt::detail::BufferReadManip(parser.BufferIn).FastReadFloat(tmp).value();
            const char* end = parser.BufferIn.CurrentPos;

            parser.BufferIn.CurrentPos = begin;
            fmt::detail::BufferReadManip(parser.BufferIn).FastReadInteger(t).value();
            parser.BufferIn.CurrentPos = end;
        }

        template <typename FloatType>
        static inline void FormatFloat(const FloatType& t, detail::JsonFormatter& formatter)
        {
            fmt::detail::BufferWriteManip(formatter.buffer_out).FastWriteFloat(t, formatter.Settings.FloatPrecision).value();
        }

        template <typename IntType>
        static inline void FormatInteger(const IntType& t, detail::JsonFormatter& formatter)
        {
            fmt::detail::BufferWriteManip(formatter.buffer_out).FastWriteInteger(t).value();
        }
    };

    struct JsonBooleanSerializer
    {
        static inline void ParseBool(bool& t, detail::JsonParser& parser)
        {
            if (fmt::detail::BufferTestManip<const char>(parser.BufferIn).is_same_forward("true", 5).value())
                t = true;
            else if (fmt::detail::BufferTestManip<const char>(parser.BufferIn).is_same_forward("false", 5).value())
                t = false;
        }

        static inline void FormatBool(const bool& t, detail::JsonFormatter& formatter)
        {
            if (t)
                fmt::detail::BufferWriteManip(formatter.buffer_out).FastWriteCharArray("true", 5).value();
            else
                fmt::detail::BufferWriteManip(formatter.buffer_out).FastWriteCharArray("false", 5).value();
        }
    };

    struct JsonStructSerializer
    {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parser, std::function<void(T&, std::size_t, std::string&&, detail::JsonParser&)> subObjectParsingFunction)
        {
            fmt::detail::BufferTestAccess access(parser.BufferIn);
            fmt::detail::BufferTestManip manip(parser.BufferIn);

            manip.SkipOneOf('{').value();
            std::size_t idx = 0;

            while (fmt::detail::BufferAccess(parser.BufferIn).IsEndOfString() == false)
            {
                manip.GoTo('"', '}');
                if (access.IsEqualTo('}')) break;

                std::string name;
                JsonStringSerializer::ParseSTDString(name, parser);

                manip.IgnoreEveryBlanks();
                manip.SkipOneOf(':').value();
                manip.IgnoreEveryBlanks();

                subObjectParsingFunction(t, idx++, std::move(name), parser);

                manip.GoTo(',', '}');
                manip.SkipOneOf(',').value();
            }

            manip.SkipOneOf('}').value();
        }

        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parserObject)
        {
            LoadAllSubObjects<T>(t, parserObject, [](T& mainObject, std::size_t idx, std::string&& name, detail::JsonParser& parser) {
                typename JsonSerializer<T>::StructSubObjectType subObject;
                parser.parse(subObject);
                JsonSerializer<T>::AddStructSubObject(mainObject, idx, std::move(name), std::move(subObject));
            });
        }

        static inline void FormatBegin(detail::JsonFormatter& formatter) { fmt::detail::BufferOutManip(formatter.buffer_out).Pushback('{').value(); }

        static inline void FormatEnd(detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            fmt::detail::BufferOutManip(formatter.buffer_out).Pushback('}').value();
        }

        template <typename SubObject>
        static inline void FormatObject(const std::string_view name, const SubObject& subObject, const std::size_t idx, detail::JsonFormatter& formatter)
        {
            if (idx != 0) fmt::detail::BufferOutManip(formatter.buffer_out).Pushback(',').value();

            formatter.BeginNewObject();
            formatter.NewLine();
            JsonStringSerializer::FormatSTDString(name, formatter);
            fmt::detail::BufferOutManip(formatter.buffer_out).Pushback(':').value();
            fmt::detail::BufferOutManip(formatter.buffer_out).Pushback(' ').value();
            formatter.format(subObject);
            formatter.EndNewObject();
        }
    };

    struct JsonArraySerializer
    {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parser, std::function<void(T&, std::size_t, detail::JsonParser&)> subObjectParsingFunction)
        {
            fmt::detail::BufferTestAccess access(parser.BufferIn);
            fmt::detail::BufferTestManip manip(parser.BufferIn);
            
            manip.SkipOneOf('[').value();
            std::size_t idx = 0;

            while (fmt::detail::BufferAccess(parser.BufferIn).IsEndOfString() == false)
            {
                manip.IgnoreEveryBlanks();

                if (access.IsEqualTo(']')) break;

                subObjectParsingFunction(t, idx++, parser);

                manip.GoTo(',', ']');
                manip.SkipOneOf(',').value();
            }

            manip.SkipOneOf(']').value();
        }

        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parser)
        {
            LoadAllSubObjects<T>(t, parser, [](T& mainObject, std::size_t idx, detail::JsonParser& jsonParser) {
                typename JsonSerializer<T>::ArraySubObjectType subObject;
                jsonParser.parse(subObject);
                JsonSerializer<T>::AddArraySubObject(mainObject, idx, std::move(subObject));
            });
        }

        static inline void FormatBegin(detail::JsonFormatter& formatter) { fmt::detail::BufferOutManip(formatter.buffer_out).Pushback('[').value(); }

        static inline void FormatEnd(detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            fmt::detail::BufferOutManip(formatter.buffer_out).Pushback(']').value();
        }

        template <typename SubObject>
        static inline void FormatObject(const SubObject& subObject, const std::size_t idx, detail::JsonFormatter& formatter)
        {
            if (idx != 0) fmt::detail::BufferOutManip(formatter.buffer_out).Pushback(',').value();

            formatter.BeginNewObject();
            formatter.NewLine();
            formatter.format(subObject);
            formatter.EndNewObject();
        }
    };

    struct JsonNullSerializer
    {
        static inline void ParseNull(detail::JsonParser& parser) { fmt::detail::BufferTestManip(parser.BufferIn).is_same_forward("null", 4).value(); }

        static inline void FormatNull(detail::JsonFormatter& formatter) { fmt::detail::BufferWriteManip(formatter.buffer_out).FastWriteCharArray("null", 4).value(); }
    };
}

namespace stream::JSON::detail
{
    template <typename T>
    void JsonFormatter::format(const T& t)
    {
        JsonSerializer<T>::format(t, *this);
    }

    template <typename T>
    void JsonParser::parse(T& t)
    {
        JsonSerializer<T>::parse(t, *this);
    }
}

namespace stream::JSON
{
    template <typename T>
    struct FormatAsJson
    {
    public:
        FormatAsJson(const T& value)
            : Value(value)
        {}

    public:
        const T& Value;
    };
}

#include "stream/fmt.h"
namespace stream::fmt
{
#ifdef STREAMFORMAT_FORMATTER_DECLARED
    template <typename T, typename FormatterExecutor>
    struct FormatterType<JSON::FormatAsJson<T>, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const JSON::FormatAsJson<T>& json, FormatterExecutor& executor)
        {
            bool ordered_struct = executor.Data.Specifiers.Has("ordered_struct");
            JSON::detail::JsonFormatter::FormatSettings settings{.OrderedStruct = ordered_struct, .FloatPrecision = executor.Data.FloatPrecision};
            JSON::detail::JsonFormatter jsonFormatter(executor.buffer_out, settings);
            JSON::JsonSerializer<T>::format(json.Value, jsonFormatter);
            return {};
        }
    };
#endif

#ifdef STREAMFORMAT_PARSER_DECLARED
    template <typename T, typename ParserExecutor>
    struct ParserType<JSON::FormatAsJson<T>, ParserExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> parse(T& json, ParserExecutor& executor)
        {
            JSON::detail::JsonParser jsonParser(*executor.BufferIn.Manager);
            jsonParser.BufferIn.CurrentPos = executor.BufferIn.CurrentPos;
            // TODO:
            // JSON::JsonSerializer<T>::parse(json.Value, jsonParser);
            executor.BufferIn.CurrentPos = jsonParser.BufferIn.CurrentPos;
            return {};
        }
    };
#endif
}
