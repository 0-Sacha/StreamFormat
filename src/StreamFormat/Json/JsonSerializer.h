#pragma once

#include "JsonFormatter.h"
#include "JsonParser.h"

#include "StreamFormat/FMT.h"
#include "StreamFormat/FMT/Buffer/BufferReadManip.h"
#include "StreamFormat/FMT/Buffer/BufferWriteManip.h"
#include "StreamFormat/FMT/Buffer/Utils/BufferUtils.h"

#include <functional>
#include <string>

namespace StreamFormat::JSON
{
    template <typename T>
    struct JsonSerializer
    {
        static inline void Parse(T&, Detail::JsonParser&)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            FMT::FilePrint(std::cerr, "{C:red}JsonSerializer::Parse<{}> not impl", typeid(T).name());
#endif
#ifdef UNKOWN_TYPE_THROW
            throw Detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw Detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }

        static inline void Format(const T&, Detail::JsonFormatter& formatter)
        {
            FMT::Detail::BufferWriteManip(formatter.BufferOut).FastWriteString(std::string_view("Unknown JsonFormatter for type : "));
            FMT::Detail::BufferWriteManip(formatter.BufferOut).FastWriteString(std::string_view(typeid(T).name()));

#ifdef UNKOWN_TYPE_MESSAGE
            FMT::FilePrint(std::cerr, "{C:red}JsonSerializer::Format<{}> not impl", typeid(T).name());
#endif
#ifdef UNKOWN_TYPE_THROW
            throw Detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw Detail::JsonTypeSerializerNotImpl{};
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
            FMT::FilePrint(std::cerr, "{C:red}JsonObjectSerializer::ReadObject<{}> not impl", typeid(T).name());
#endif
#ifdef UNKOWN_TYPE_THROW
            throw Detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw Detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }

        static inline void WriteObject(const T&, JsonObject&)
        {
#ifdef UNKOWN_TYPE_MESSAGE
            FMT::FilePrint(std::cerr, "{C:red}JsonObjectSerializer::WriteObject<{}> not impl", typeid(T).name());
#endif
#ifdef UNKOWN_TYPE_THROW
            throw Detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw Detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }
    };

    struct JsonStringSerializer
    {
        static inline void ParseSTDString(std::string& t, Detail::JsonParser& parser)
        {
            FMT::Detail::DynamicBufferOutManager<char> bufferData;
            FMT::Detail::BufferOutInfo<char> buffer(bufferData);
            FMT::Detail::BufferUtils::ParseEscapedQuotedString(parser.BufferIn, buffer);
            FMT::Detail::BufferOutManip(buffer).ComputeGeneratedSize();
            t = bufferData.GetLastGeneratedString();
        }

        static inline void FormatSTDString(const std::string_view t, Detail::JsonFormatter& formatter)
        {
            FMT::Detail::BufferInfo<const char> buffer(t.data(), t.size());
            FMT::Detail::BufferUtils::FormatEscapedQuotedString(formatter.BufferOut, buffer);
        }
    };

    struct JsonNumberSerializer
    {
        template <typename FloatType>
        static inline void ParseFloat(FloatType& t, Detail::JsonParser& parser)
        {
            FMT::Detail::BufferReadManip(parser.BufferIn).FastReadFloat(t);
        }

        template <typename IntType>
        static inline void ParseInteger(IntType& t, Detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn.CurrentPos;
            float tmp = 0;
            FMT::Detail::BufferReadManip(parser.BufferIn).FastReadFloat(tmp);
            const char* end = parser.BufferIn.CurrentPos;

            parser.BufferIn.CurrentPos = begin;
            FMT::Detail::BufferReadManip(parser.BufferIn).FastReadInteger(t);
            parser.BufferIn.CurrentPos = end;
        }

        template <typename FloatType>
        static inline void FormatFloat(const FloatType& t, Detail::JsonFormatter& formatter)
        {
            FMT::Detail::BufferWriteManip(formatter.BufferOut).FastWriteFloat(t, formatter.Settings.FloatPrecision);
        }

        template <typename IntType>
        static inline void FormatInteger(const IntType& t, Detail::JsonFormatter& formatter)
        {
            FMT::Detail::BufferWriteManip(formatter.BufferOut).FastWriteInteger(t);
        }
    };

    struct JsonBooleanSerializer
    {
        static inline void ParseBool(bool& t, Detail::JsonParser& parser)
        {
            if (FMT::Detail::BufferTestManip<const char>(parser.BufferIn).IsSameForward("true", 5))
                t = true;
            else if (FMT::Detail::BufferTestManip<const char>(parser.BufferIn).IsSameForward("false", 5))
                t = false;
        }

        static inline void FormatBool(const bool& t, Detail::JsonFormatter& formatter)
        {
            if (t)
                FMT::Detail::BufferWriteManip(formatter.BufferOut).FastWriteCharArray("true", 5);
            else
                FMT::Detail::BufferWriteManip(formatter.BufferOut).FastWriteCharArray("false", 5);
        }
    };

    struct JsonStructSerializer
    {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, Detail::JsonParser& parser, std::function<void(T&, std::size_t, std::string&&, Detail::JsonParser&)> subObjectParsingFunction)
        {
            FMT::Detail::BufferTestAccess access(parser.BufferIn);
            FMT::Detail::BufferTestManip manip(parser.BufferIn);

            manip.Skip('{');
            std::size_t idx = 0;

            while (FMT::Detail::BufferAccess(parser.BufferIn).IsEndOfString() == false)
            {
                manip.GoTo('"', '}');
                if (access.IsEqualTo('}')) break;

                std::string name;
                JsonStringSerializer::ParseSTDString(name, parser);

                manip.SkipAllBlanks();
                manip.Skip(':');
                manip.SkipAllBlanks();

                subObjectParsingFunction(t, idx++, std::move(name), parser);

                manip.GoTo(',', '}');
                manip.Skip(',');
            }

            manip.Skip('}');
        }

        template <typename T>
        static inline void LoadAllSubObjects(T& t, Detail::JsonParser& parserObject)
        {
            LoadAllSubObjects<T>(t, parserObject, [](T& mainObject, std::size_t idx, std::string&& name, Detail::JsonParser& parser) {
                typename JsonSerializer<T>::StructSubObjectType subObject;
                parser.Parse(subObject);
                JsonSerializer<T>::AddStructSubObject(mainObject, idx, std::move(name), std::move(subObject));
            });
        }

        static inline void FormatBegin(Detail::JsonFormatter& formatter) { FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback('{'); }

        static inline void FormatEnd(Detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback('}');
        }

        template <typename SubObject>
        static inline void FormatObject(const std::string_view name, const SubObject& subObject, const std::size_t idx, Detail::JsonFormatter& formatter)
        {
            if (idx != 0) FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback(',');

            formatter.BeginNewObject();
            formatter.NewLine();
            JsonStringSerializer::FormatSTDString(name, formatter);
            FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback(':');
            FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback(' ');
            formatter.Format(subObject);
            formatter.EndNewObject();
        }
    };

    struct JsonArraySerializer
    {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, Detail::JsonParser& parser, std::function<void(T&, std::size_t, Detail::JsonParser&)> subObjectParsingFunction)
        {
            FMT::Detail::BufferTestAccess access(parser.BufferIn);
            FMT::Detail::BufferTestManip manip(parser.BufferIn);
            
            manip.Skip('[');
            std::size_t idx = 0;

            while (FMT::Detail::BufferAccess(parser.BufferIn).IsEndOfString() == false)
            {
                manip.SkipAllBlanks();

                if (access.IsEqualTo(']')) break;

                subObjectParsingFunction(t, idx++, parser);

                manip.GoTo(',', ']');
                manip.Skip(',');
            }

            manip.Skip(']');
        }

        template <typename T>
        static inline void LoadAllSubObjects(T& t, Detail::JsonParser& parser)
        {
            LoadAllSubObjects<T>(t, parser, [](T& mainObject, std::size_t idx, Detail::JsonParser& jsonParser) {
                typename JsonSerializer<T>::ArraySubObjectType subObject;
                jsonParser.Parse(subObject);
                JsonSerializer<T>::AddArraySubObject(mainObject, idx, std::move(subObject));
            });
        }

        static inline void FormatBegin(Detail::JsonFormatter& formatter) { FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback('['); }

        static inline void FormatEnd(Detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback(']');
        }

        template <typename SubObject>
        static inline void FormatObject(const SubObject& subObject, const std::size_t idx, Detail::JsonFormatter& formatter)
        {
            if (idx != 0) FMT::Detail::BufferOutManip(formatter.BufferOut).Pushback(',');

            formatter.BeginNewObject();
            formatter.NewLine();
            formatter.Format(subObject);
            formatter.EndNewObject();
        }
    };

    struct JsonNullSerializer
    {
        static inline void ParseNull(Detail::JsonParser& parser) { FMT::Detail::BufferTestManip(parser.BufferIn).IsSameForward("null", 4); }

        static inline void FormatNull(Detail::JsonFormatter& formatter) { FMT::Detail::BufferWriteManip(formatter.BufferOut).FastWriteCharArray("null", 4); }
    };
}

namespace StreamFormat::JSON::Detail
{
    template <typename T>
    void JsonFormatter::Format(const T& t)
    {
        JsonSerializer<T>::Format(t, *this);
    }

    template <typename T>
    void JsonParser::Parse(T& t)
    {
        JsonSerializer<T>::Parse(t, *this);
    }
}

namespace StreamFormat::JSON
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

#include "StreamFormat/FMT.h"
namespace StreamFormat::FMT
{
#ifdef STREAMFORMAT_FORMATTER_DECLARED
    template <typename T, typename FormatterExecutor>
    struct FormatterType<JSON::FormatAsJson<T>, FormatterExecutor>
    {
        static void Format(const JSON::FormatAsJson<T>& json, FormatterExecutor& executor)
        {
            bool ordered_struct = executor.Data.Specifiers.Has("ordered_struct");
            JSON::Detail::JsonFormatter::FormatSettings settings{.OrderedStruct = ordered_struct, .FloatPrecision = executor.Data.FloatPrecision};
            JSON::Detail::JsonFormatter jsonFormatter(executor.BufferOut, settings);
            JSON::JsonSerializer<T>::Format(json.Value, jsonFormatter);
        }
    };
#endif

#ifdef STREAMFORMAT_PARSER_DECLARED
    template <typename T, typename ParserExecutor>
    struct ParserType<JSON::FormatAsJson<T>, ParserExecutor>
    {
        static inline void Parse(T& json, ParserExecutor& executor)
        {
            JSON::Detail::JsonParser jsonParser(*executor.BufferIn.Manager);
            jsonParser.BufferIn.CurrentPos = executor.BufferIn.CurrentPos;
            // TODO:
            // JSON::JsonSerializer<T>::Parse(json.Value, jsonParser);
            executor.BufferIn.CurrentPos = jsonParser.BufferIn.CurrentPos;
        }
    };
#endif
}
