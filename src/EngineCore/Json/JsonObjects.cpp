
#include "JsonObjects.h"
#include "Serializers/JsonObjectsSerializer.h"


namespace EngineCore::JSON
{
	void JsonStringObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonStringObject>::Parse(*this, parser);
	}
	void JsonStringObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonStringObject>::Format(*this, formatter);
	}

	void JsonNumberObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonNumberObject>::Parse(*this, parser);
	}
	void JsonNumberObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonNumberObject>::Format(*this, formatter);
	}

	void JsonBooleanObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonBooleanObject>::Parse(*this, parser);
	}
	void JsonBooleanObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonBooleanObject>::Format(*this, formatter);
	}

	void JsonStructObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonStructObject>::Parse(*this, parser);
	}
	void JsonStructObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonStructObject>::Format(*this, formatter);
	}

	void JsonArrayObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonArrayObject>::Parse(*this, parser);
	}
	void JsonArrayObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonArrayObject>::Format(*this, formatter);
	}

	void JsonNullObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonNullObject>::Parse(*this, parser);
	}
	void JsonNullObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonNullObject>::Format(*this, formatter);
	}
}
