#include "json_objects.h"
#include "serializers/json_objects_serializer.h"

namespace stream::json {
    void JsonStringObject::ParserExecute(detail::JsonParser& parser) {
        JsonSerializer<JsonStringObject>::parse(*this, parser);
    }
    void JsonStringObject::FormatterExecute(detail::JsonFormatter& formatter) const {
        JsonSerializer<JsonStringObject>::format(*this, formatter);
    }

    void JsonNumberObject::ParserExecute(detail::JsonParser& parser) {
        JsonSerializer<JsonNumberObject>::parse(*this, parser);
    }
    void JsonNumberObject::FormatterExecute(detail::JsonFormatter& formatter) const {
        JsonSerializer<JsonNumberObject>::format(*this, formatter);
    }

    void JsonBooleanObject::ParserExecute(detail::JsonParser& parser) {
        JsonSerializer<JsonBooleanObject>::parse(*this, parser);
    }
    void JsonBooleanObject::FormatterExecute(detail::JsonFormatter& formatter) const {
        JsonSerializer<JsonBooleanObject>::format(*this, formatter);
    }

    void JsonStructObject::ParserExecute(detail::JsonParser& parser) {
        JsonSerializer<JsonStructObject>::parse(*this, parser);
    }
    void JsonStructObject::FormatterExecute(detail::JsonFormatter& formatter) const {
        JsonSerializer<JsonStructObject>::format(*this, formatter);
    }

    void JsonArrayObject::ParserExecute(detail::JsonParser& parser) {
        JsonSerializer<JsonArrayObject>::parse(*this, parser);
    }
    void JsonArrayObject::FormatterExecute(detail::JsonFormatter& formatter) const {
        JsonSerializer<JsonArrayObject>::format(*this, formatter);
    }

    void JsonNullObject::ParserExecute(detail::JsonParser& parser) {
        JsonSerializer<JsonNullObject>::parse(*this, parser);
    }
    void JsonNullObject::FormatterExecute(detail::JsonFormatter& formatter) const {
        JsonSerializer<JsonNullObject>::format(*this, formatter);
    }
}  // namespace stream::json
