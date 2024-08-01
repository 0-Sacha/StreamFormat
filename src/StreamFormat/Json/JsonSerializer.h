#pragma once

#include "JsonFormatter.h"
#include "JsonParser.h"

#include "StreamFormat/FMT.h"
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
            formatter.BufferOut().FastWriteCharArray("Unkown JsonFormatter for type : ");
            formatter.BufferOut().FastWriteCharPtrNSize(typeid(T).name());

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
            StreamFormat::FMT::Detail::DynamicBufferOutManager<char> bufferData;
            StreamFormat::FMT::Detail::BasicBufferOut<char>          buffer(bufferData);
            StreamFormat::FMT::BufferUtils<char>::ParseEscapedQuotedString(parser.BufferIn(), buffer);
            buffer.EndContext();
            t = bufferData.GetLastGeneratedString();
        }

        static inline void FormatSTDString(const std::string_view t, Detail::JsonFormatter& formatter)
        {
            StreamFormat::FMT::Detail::BufferInProperties<char> bufferInProperties(t);
            StreamFormat::FMT::Detail::BasicBufferIn<char>      buffer(bufferInProperties);
            StreamFormat::FMT::BufferUtils<char>::FormatEscapedQuotedString(formatter.BufferOut(), buffer);
        }
    };

    struct JsonNumberSerializer
    {
        template <typename FloatType>
        static inline void ParseFloat(FloatType& t, Detail::JsonParser& parser)
        {
            parser.BufferIn().FastReadFloatThrow<FloatType>(t);
        }

        template <typename IntType>
        static inline void ParseInt(IntType& t, Detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn().GetBufferCurrentPos();
            float       tmp   = 0;
            parser.BufferIn().FastReadFloatThrow<float>(tmp);
            const char* end = parser.BufferIn().GetBufferCurrentPos();

            parser.BufferIn().SetBufferCurrentPos(begin);
            parser.BufferIn().FastReadIntThrow(t);

            parser.BufferIn().SetBufferCurrentPos(end);
        }

        template <typename UIntType>
        static inline void ParseUInt(UIntType& t, Detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn().GetBufferCurrentPos();
            float       tmp   = 0;
            parser.BufferIn().FastReadFloatThrow<float>(tmp);
            const char* end = parser.BufferIn().GetBufferCurrentPos();

            parser.BufferIn().SetBufferCurrentPos(begin);
            parser.BufferIn().FastReadUIntThrow(t);

            parser.BufferIn().SetBufferCurrentPos(end);
        }

        template <typename FloatType>
        static inline void FormatFloat(const FloatType& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().FastWriteFloat(t, formatter.Settings().FloatPrecision);
        }

        template <typename IntType>
        static inline void FormatInt(const IntType& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().FastWriteInt(t);
        }

        template <typename UIntType>
        static inline void FormatUInt(const UIntType& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().FastWriteUInt(t);
        }
    };

    struct JsonBooleanSerializer
    {
        static inline void ParseBool(bool& t, Detail::JsonParser& parser)
        {
            if (parser.BufferIn().IsSameSeqForward('t', 'r', 'u', 'e'))
                t = true;
            else if (parser.BufferIn().IsSameSeqForward('f', 'a', 'l', 's', 'e'))
                t = false;
        }

        static inline void FormatBool(const bool& t, Detail::JsonFormatter& formatter)
        {
            if (t)
                formatter.BufferOut().PushBackSeq('t', 'r', 'u', 'e');
            else
                formatter.BufferOut().PushBackSeq('f', 'a', 'l', 's', 'e');
        }
    };

    struct JsonStructSerializer
    {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, Detail::JsonParser& parser, std::function<void(T&, std::size_t, std::string&&, Detail::JsonParser&)> subObjectParsingFunction)
        {
            parser.BufferIn().Skip('{');
            std::size_t idx = 0;

            while (parser.BufferIn().IsEnd() == false)
            {
                parser.BufferIn().GoTo('"', '}');
                if (parser.BufferIn().IsEqualTo('}')) break;

                std::string name;
                JsonStringSerializer::ParseSTDString(name, parser);

                parser.BufferIn().IgnoreAllBlanks();
                parser.BufferIn().Skip(':');
                parser.BufferIn().IgnoreAllBlanks();

                subObjectParsingFunction(t, idx++, std::move(name), parser);

                parser.BufferIn().GoTo(',', '}');
                parser.BufferIn().Ignore(',');
            }

            parser.BufferIn().Skip('}');
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

        static inline void FormatBegin(Detail::JsonFormatter& formatter) { formatter.BufferOut().PushBack('{'); }

        static inline void FormatEnd(Detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            formatter.BufferOut().PushBack('}');
        }

        template <typename SubObject>
        static inline void FormatObject(const std::string_view name, const SubObject& subObject, const std::size_t idx, Detail::JsonFormatter& formatter)
        {
            if (idx != 0) formatter.BufferOut().PushBack(',');

            formatter.BeginNewObject();
            formatter.NewLine();
            JsonStringSerializer::FormatSTDString(name, formatter);
            formatter.BufferOut().PushBack(':');
            formatter.BufferOut().PushBack(' ');
            formatter.Format(subObject);
            formatter.EndNewObject();
        }
    };

    struct JsonArraySerializer
    {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, Detail::JsonParser& parser, std::function<void(T&, std::size_t, Detail::JsonParser&)> subObjectParsingFunction)
        {
            parser.BufferIn().Skip('[');
            std::size_t idx = 0;

            while (parser.BufferIn().IsEnd() == false)
            {
                parser.BufferIn().IgnoreAllBlanks();

                if (parser.BufferIn().IsEqualTo(']')) break;

                subObjectParsingFunction(t, idx++, parser);

                parser.BufferIn().GoTo(',', ']');
                parser.BufferIn().Ignore(',');
            }

            parser.BufferIn().Skip(']');
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

        static inline void FormatBegin(Detail::JsonFormatter& formatter) { formatter.BufferOut().PushBack('['); }

        static inline void FormatEnd(Detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            formatter.BufferOut().PushBack(']');
        }

        template <typename SubObject>
        static inline void FormatObject(const SubObject& subObject, const std::size_t idx, Detail::JsonFormatter& formatter)
        {
            if (idx != 0) formatter.BufferOut().PushBack(',');

            formatter.BeginNewObject();
            formatter.NewLine();
            formatter.Format(subObject);
            formatter.EndNewObject();
        }
    };

    struct JsonNullSerializer
    {
        static inline void ParseNull(Detail::JsonParser& parser) { parser.BufferIn().IsSameSeqForwardThrow('n', 'u', 'l', 'l'); }

        static inline void FormatNull(Detail::JsonFormatter& formatter) { formatter.BufferOut().PushBackSeq('n', 'u', 'l', 'l'); }
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
    template <typename T, typename FormatterContext>
    struct FormatterType<JSON::FormatAsJson<T>, FormatterContext>
    {
        static void Format(const JSON::FormatAsJson<T>& json, FormatterContext& context)
        {
            bool                                        ordered_struct = context.GetFormatData().HasSpecifier("ordered_struct");
            JSON::Detail::JsonFormatter::FormatSettings settings{.OrderedStruct = ordered_struct, .FloatPrecision = context.GetFormatData().FloatPrecision};
            JSON::Detail::JsonFormatter                 jsonFormatter(context.BufferOut().GetBufferOutManager(), settings);
            jsonFormatter.BufferOut().ReloadBuffer(context.BufferOut());
            JSON::JsonSerializer<T>::Format(json.Value, jsonFormatter);
            context.BufferOut().ReloadBuffer(jsonFormatter.BufferOut());
        }
    };
#endif

#ifdef STREAMFORMAT_PARSER_DECLARED
    template <typename T, typename ParserContext>
    struct ParserType<JSON::FormatAsJson<T>, ParserContext>
    {
        static inline void Parse(T& json, ParserContext& context)
        {
            JSON::Detail::JsonParser jsonParser(context.BufferIn().GetBufferOutManager());
            jsonParser.BufferIn().ReloadBuffer(context.BufferIn());
            // TODO:
            // JSON::JsonSerializer<T>::Parse(json.Value, jsonParser);
            context.BufferIn().ReloadBuffer(jsonParser.BufferIn());
        }
    };
#endif
}
