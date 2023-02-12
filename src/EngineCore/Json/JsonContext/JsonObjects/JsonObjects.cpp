
#include "JsonObjects.h"
#include "EngineCore/Json/JsonContext/JsonParser/JsonParser.h"
#include "EngineCore/Json/JsonContext/JsonFormatter/JsonFormatter.h"

namespace EngineCore::JSON::Detail
{
    void JsonObject::Parse(JsonParser& parser)
    {
        const char* begin = parser.GetBuffer().GetBufferCurrentPos();
        ParseImpl(parser);
        const char* end = parser.GetBuffer().GetBufferCurrentPos();
        Data = std::string_view(begin, end);
    }

    void JsonObject::Format(JsonFormatter& formatter) const
    {
        FormatImpl(formatter);
    }


    void JsonStringObject::ParseImpl(JsonParser& parser)
    {
        String.clear();
        String = EngineCore::FMT::BufferInUtils<char>::ParseEscapedQuotedString(parser.GetBuffer());
    }

    void JsonStringObject::FormatImpl(JsonFormatter& formatter) const
    {
        EngineCore::FMT::BufferOutUtils<char>::WriteEscapedQuotedString(formatter.GetBuffer(), String);
    }


    void JsonNumberObject::ParseImpl(JsonParser& parser)
    {
        const char* begin = parser.GetBuffer().GetBufferCurrentPos();

        parser.GetBuffer().FastReadFloat<double>(NumberAsDouble);
        const char* end = parser.GetBuffer().GetBufferCurrentPos();
        
        parser.GetBuffer().SetCurrentPos(begin);
        parser.GetBuffer().FastReadInt(NumberAsInt);

        parser.GetBuffer().SetCurrentPos(begin);
        parser.GetBuffer().FastReadUInt(NumberAsUInt);

        parser.GetBuffer().SetCurrentPos(end);
    }

    void JsonNumberObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.GetBuffer().FastWriteFloat<double>(NumberAsDouble);
    }


    void JsonBooleanObject::ParseImpl(JsonParser& parser)
    {
        if (parser.GetBuffer().IsSameSeqForward('t', 'r', 'u', 'e'))
            Boolean = true;
        else if (parser.GetBuffer().IsSameSeqForward('f', 'a', 'l', 's', 'e'))
            Boolean = false;
    }

    void JsonBooleanObject::FormatImpl(JsonFormatter& formatter) const
    {
        if (Boolean)
            formatter.GetBuffer().WriteCharPtr("true", 4);
        else
            formatter.GetBuffer().WriteCharPtr("false", 5);
    }


    void JsonStructObject::ParseImpl(JsonParser& parser)
    {
        parser.GetBuffer().Skip('{');

        while (parser.GetBuffer().IsEnd() == false)
        {
            parser.GetBuffer().GoTo('"', '}');
            if (parser.GetBuffer().IsEqualTo('}')) break;

            std::string name = EngineCore::FMT::BufferInUtils<char>::ParseEscapedQuotedString(parser.GetBuffer());

            parser.GetBuffer().IgnoreBlank();
            parser.GetBuffer().Skip(':');
            parser.GetBuffer().IgnoreBlank();

            std::unique_ptr<JsonObject> subObject = parser.LoadJsonObject();
            Objects.insert({ std::move(name), std::move(subObject) });

            parser.GetBuffer().GoTo(',', '}');
            if (parser.GetBuffer().IsEqualTo('}')) break;
            parser.GetBuffer().Skip(',');
        }

        parser.GetBuffer().Skip('}');
    }

    void JsonStructObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.GetBuffer().PushBack('{');

        bool first = true;
        for (const auto& [name, object] : Objects)
        {
            if (first)
                first = false;
            else
                formatter.GetBuffer().PushBack(',');

			EngineCore::FMT::BufferOutUtils<char>::WriteEscapedQuotedString(formatter.GetBuffer(), name);
			formatter.GetBuffer().PushBack(':');
			formatter.GetBuffer().PushBack(' ');
			formatter.DumpJsonObject(*object);
        }

        formatter.GetBuffer().PushBack('}');
    }


    void JsonArrayObject::ParseImpl(JsonParser& parser)
    {
        parser.GetBuffer().Skip('[');

        while (parser.GetBuffer().IsEnd() == false)
        {
            parser.GetBuffer().IgnoreBlank();

            std::unique_ptr<JsonObject> subObject = parser.LoadJsonObject();
            Objects.push_back(std::move(subObject));

            parser.GetBuffer().GoTo(',', ']');
            if (parser.GetBuffer().IsEqualTo(']')) break;
            parser.GetBuffer().Skip(',');
        }

        parser.GetBuffer().Skip(']');
    }

    void JsonArrayObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.GetBuffer().PushBack('[');

        bool first = true;
        for (const auto& object : Objects)
        {
            if (first)
                first = false;
            else
                formatter.GetBuffer().PushBack(',');

            formatter.DumpJsonObject(*object);
        }

        formatter.GetBuffer().PushBack(']');
    }


    void JsonNullObject::ParseImpl(JsonParser& parser)
    {
        parser.GetBuffer().IsSameForwardThrow("null");
    }

    void JsonNullObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.GetBuffer().WriteCharPtr("null", 4);
    }
}
