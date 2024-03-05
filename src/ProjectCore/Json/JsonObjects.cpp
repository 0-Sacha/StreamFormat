#include "JsonObjects.h"
#include "Serializers/JsonObjectsSerializer.h"

namespace ProjectCore::JSON
{
    void JsonStringObject::ParserExecute(Detail::JsonParser& parser)
    {
        JsonSerializer<JsonStringObject>::Parse(*this, parser);
    }
    void JsonStringObject::FormatterExecute(Detail::JsonFormatter& formatter) const
    {
        JsonSerializer<JsonStringObject>::Format(*this, formatter);
    }

    void JsonNumberObject::ParserExecute(Detail::JsonParser& parser)
    {
        JsonSerializer<JsonNumberObject>::Parse(*this, parser);
    }
    void JsonNumberObject::FormatterExecute(Detail::JsonFormatter& formatter) const
    {
        JsonSerializer<JsonNumberObject>::Format(*this, formatter);
    }

    void JsonBooleanObject::ParserExecute(Detail::JsonParser& parser)
    {
        JsonSerializer<JsonBooleanObject>::Parse(*this, parser);
    }
    void JsonBooleanObject::FormatterExecute(Detail::JsonFormatter& formatter) const
    {
        JsonSerializer<JsonBooleanObject>::Format(*this, formatter);
    }

    void JsonStructObject::ParserExecute(Detail::JsonParser& parser)
    {
        JsonSerializer<JsonStructObject>::Parse(*this, parser);
    }
    void JsonStructObject::FormatterExecute(Detail::JsonFormatter& formatter) const
    {
        JsonSerializer<JsonStructObject>::Format(*this, formatter);
    }

    void JsonArrayObject::ParserExecute(Detail::JsonParser& parser)
    {
        JsonSerializer<JsonArrayObject>::Parse(*this, parser);
    }
    void JsonArrayObject::FormatterExecute(Detail::JsonFormatter& formatter) const
    {
        JsonSerializer<JsonArrayObject>::Format(*this, formatter);
    }

    void JsonNullObject::ParserExecute(Detail::JsonParser& parser)
    {
        JsonSerializer<JsonNullObject>::Parse(*this, parser);
    }
    void JsonNullObject::FormatterExecute(Detail::JsonFormatter& formatter) const
    {
        JsonSerializer<JsonNullObject>::Format(*this, formatter);
    }
}
