
#include "JsonObjects.h"
#include "EngineCore/Json/JsonContext/JsonParser/JsonParser.h"
#include "EngineCore/Json/JsonContext/JsonFormatter/JsonFormatter.h"

namespace EngineCore::JSON::Detail
{
    void JsonObject::Parse(JsonParser& parser)
    {
        const char* begin = parser.BufferIn().GetBufferCurrentPos();
        ParseImpl(parser);
        const char* end = parser.BufferIn().GetBufferCurrentPos();
        Data = std::string_view(begin, end);
    }

    void JsonObject::Format(JsonFormatter& formatter) const
    {
        FormatImpl(formatter);
    }


    void JsonStringObject::ParseImpl(JsonParser& parser)
    {
        String.clear();
        String = EngineCore::FMT::BufferInUtils<char>::ParseEscapedQuotedString(parser.BufferIn());
    }

    void JsonStringObject::FormatImpl(JsonFormatter& formatter) const
    {
        EngineCore::FMT::BufferOutUtils<char>::WriteEscapedQuotedString(formatter.BufferOut(), String);
    }


    void JsonNumberObject::ParseImpl(JsonParser& parser)
    {
        const char* begin = parser.BufferIn().GetBufferCurrentPos();

        parser.BufferIn().FastReadFloat<double>(NumberAsDouble);
        const char* end = parser.BufferIn().GetBufferCurrentPos();
        
        parser.BufferIn().SetBufferCurrentPos(begin);
        parser.BufferIn().FastReadInt(NumberAsInt);

        parser.BufferIn().SetBufferCurrentPos(begin);
        parser.BufferIn().FastReadUInt(NumberAsUInt);

        parser.BufferIn().SetBufferCurrentPos(end);
    }

    void JsonNumberObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.BufferOut().FastWriteFloat<double>(NumberAsDouble);
    }


    void JsonBooleanObject::ParseImpl(JsonParser& parser)
    {
        if (parser.BufferIn().IsSameSeqForward('t', 'r', 'u', 'e'))
            Boolean = true;
        else if (parser.BufferIn().IsSameSeqForward('f', 'a', 'l', 's', 'e'))
            Boolean = false;
    }

    void JsonBooleanObject::FormatImpl(JsonFormatter& formatter) const
    {
        if (Boolean)
            formatter.BufferOut().WriteCharPtr("true", 4);
        else
            formatter.BufferOut().WriteCharPtr("false", 5);
    }


    void JsonStructObject::ParseImpl(JsonParser& parser)
    {
        parser.BufferIn().Skip('{');

        while (parser.BufferIn().IsEnd() == false)
        {
            parser.BufferIn().GoTo('"', '}');
            if (parser.BufferIn().IsEqualTo('}')) break;

            std::string name = EngineCore::FMT::BufferInUtils<char>::ParseEscapedQuotedString(parser.BufferIn());

            parser.BufferIn().IgnoreAllBlanks();
            parser.BufferIn().Skip(':');
            parser.BufferIn().IgnoreAllBlanks();

            std::unique_ptr<JsonObject> subObject = parser.LoadJsonObject();
            Objects.insert({ std::move(name), std::move(subObject) });

            parser.BufferIn().GoTo(',', '}');
            parser.BufferIn().Ignore(',');
        }

        parser.BufferIn().Skip('}');
    }

    void JsonStructObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.BufferOut().PushBack('{');

        bool first = true;
        for (const auto& [name, object] : Objects)
        {
            if (first)
                first = false;
            else
                formatter.BufferOut().PushBack(',');

            formatter.BeginNewObject();
            formatter.NewLine();
			EngineCore::FMT::BufferOutUtils<char>::WriteEscapedQuotedString(formatter.BufferOut(), name);
			formatter.BufferOut().PushBack(':');
			formatter.BufferOut().PushBack(' ');
			formatter.DumpJsonObject(*object);
            formatter.EndNewObject();
        }
		formatter.NewLine();
        formatter.BufferOut().PushBack('}');
    }


    void JsonArrayObject::ParseImpl(JsonParser& parser)
    {
        parser.BufferIn().Skip('[');

        while (parser.BufferIn().IsEnd() == false)
        {
            parser.BufferIn().IgnoreAllBlanks();

            if (parser.BufferIn().IsEqualTo(']')) break;

            std::unique_ptr<JsonObject> subObject = parser.LoadJsonObject();
            Objects.push_back(std::move(subObject));

            parser.BufferIn().GoTo(',', ']');
            parser.BufferIn().Ignore(',');
        }

        parser.BufferIn().Skip(']');
    }

    void JsonArrayObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.BufferOut().PushBack('[');

        bool first = true;
        for (const auto& object : Objects)
        {
            if (first)
                first = false;
            else
                formatter.BufferOut().PushBack(',');

            formatter.BeginNewObject();
            formatter.NewLine();
            formatter.DumpJsonObject(*object);
            formatter.EndNewObject();
        }

        formatter.NewLine();
		formatter.BufferOut().PushBack(']');
    }


    void JsonNullObject::ParseImpl(JsonParser& parser)
    {
        parser.BufferIn().IsSameForwardThrow("null");
    }

    void JsonNullObject::FormatImpl(JsonFormatter& formatter) const
    {
        formatter.BufferOut().WriteCharPtr("null", 4);
    }
}
