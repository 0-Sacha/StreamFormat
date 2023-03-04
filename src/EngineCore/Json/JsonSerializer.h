#pragma once

#include "JsonParser.h"
#include "JsonFormatter.h"

#include "EngineCore/FMT/Detail/Buffer/Utils/BufferUtils.h"

#include <string>
#include <functional>

namespace EngineCore::JSON
{
    template<typename T>
	struct JsonSerializer
    {
		static inline void Parse(T& t, Detail::JsonParser& parser)
        {
#ifdef ENGINECORE_COMPILER_VS
            __debugbreak();
#else
            throw JsonTypeSerializerNotImpl{};
#endif
        }

		static inline void Format(const T& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().WriteCharArray("Unkown JsonFormatter for type : ");
            formatter.BufferOut().WriteCharPtr(typeid(T).name());

#ifndef ENGINECORE_COMPILER_VS
            throw JsonTypeSerializerNotImpl{};
#endif
        }
	};

	struct JsonStringSerializer
    {
        static inline void ParseSTDString(std::string& t, Detail::JsonParser& parser)
        {
            EngineCore::FMT::Detail::DynamicBufferOutManager<char> bufferData;
            EngineCore::FMT::Detail::BasicBufferOut<char> buffer(bufferData);
            EngineCore::FMT::BufferUtils<char>::ParseEscapedQuotedString(parser.BufferIn(), buffer);
            t = bufferData.GetLastGeneratedString();
        }

		static inline void FormatSTDString(const std::string& t, Detail::JsonFormatter& formatter)
        {
            EngineCore::FMT::Detail::BufferInProperties<char> bufferInProperties(t);
            EngineCore::FMT::Detail::BasicBufferIn<char> buffer(bufferInProperties);
            EngineCore::FMT::BufferUtils<char>::FormatEscapedQuotedString(formatter.BufferOut(), buffer);
        }
    };

	struct JsonNumberSerializer
    {
        template <typename FloatType>
        static inline void ParseFloat(FloatType& t, Detail::JsonParser& parser)
        {
            parser.BufferIn().FastReadFloat<FloatType>(t);
        }

        template <typename IntType>
        static inline void ParseInt(IntType& t, Detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn().GetBufferCurrentPos();
            float tmp = 0;
            parser.BufferIn().FastReadFloat<float>(tmp);
            const char* end = parser.BufferIn().GetBufferCurrentPos();
            
            parser.BufferIn().SetBufferCurrentPos(begin);
            parser.BufferIn().FastReadInt(t);

            parser.BufferIn().SetBufferCurrentPos(end);
        }

        template <typename UIntType>
        static inline void ParseUInt(UIntType& t, Detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn().GetBufferCurrentPos();
            float tmp = 0;
            parser.BufferIn().FastReadFloat<float>(tmp);
            const char* end = parser.BufferIn().GetBufferCurrentPos();
            
            parser.BufferIn().SetBufferCurrentPos(begin);
            parser.BufferIn().FastReadUInt(t);

            parser.BufferIn().SetBufferCurrentPos(end);
        }

        template <typename FloatType>
		static inline void FormatFloat(const FloatType& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().FastWriteFloat(t);
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
                t  = false;
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
        static inline void LoadAllSubObjects(T& t, Detail::JsonParser& parser)
        {
            LoadAllSubObjects<T>(t, parser, [](T& t, std::size_t idx, std::string&& name, Detail::JsonParser& parser){
                typename JsonSerializer<T>::StructSubObjectType subObject;
                parser.Parse(subObject);
                JsonSerializer<T>::AddStructSubObject(t, idx, std::move(name), std::move(subObject));
            });
        }

		static inline void FormatBegin(Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBack('{');
        }

        static inline void FormatEnd(Detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            formatter.BufferOut().PushBack('}');
        }

        template <typename SubObject>
        static inline void FormatObject(const std::string& name, const SubObject& subObject, const std::size_t idx, Detail::JsonFormatter& formatter)
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
            LoadAllSubObjects<T>(t, parser, [](T& t, std::size_t idx, Detail::JsonParser& parser){
                typename JsonSerializer<T>::ArraySubObjectType subObject;
                parser.Parse(subObject);
                JsonSerializer<T>::AddArraySubObject(t, idx, std::move(subObject));
            });
        }

		static inline void FormatBegin(Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBack('[');
        }

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
        static inline void ParseNull(Detail::JsonParser& parser)
        {
            parser.BufferIn().IsSameSeqForwardThrow('n', 'u', 'l', 'l');
        }

		static inline void FormatNull(Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBackSeq('n', 'u', 'l', 'l');
        }
    };
}

namespace EngineCore::JSON::Detail
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

namespace EngineCore::JSON
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

#include "EngineCore/FMT/FMT.h"
namespace EngineCore::FMT
{
	template<typename T, typename FormatterContext>
	struct FormatterType<JSON::FormatAsJson<T>, FormatterContext> {
		static void Format(const JSON::FormatAsJson<T>& json, FormatterContext& context)
		{
            JSON::Detail::JsonFormatter jsonFormatter(context.BufferOut().GetBufferOutManager());
			jsonFormatter.BufferOut().ReloadBuffer(context.BufferOut());
            JSON::JsonSerializer<T>::Format(json.Value, jsonFormatter);
			context.BufferOut().ReloadBuffer(jsonFormatter.BufferOut());
		}
	};
}
