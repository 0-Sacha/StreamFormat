
#include "JsonObjects.h"
#include "JsonObjectsSerializer.h"

namespace EngineCore::JSON
{
	void JsonStringObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonStringObject>::Load(*this, parser);
	}
	void JsonStringObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonStringObject>::Dump(*this, formatter);
	}

	void JsonNumberObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonNumberObject>::Load(*this, parser);
	}
	void JsonNumberObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonNumberObject>::Dump(*this, formatter);
	}

	void JsonBooleanObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonBooleanObject>::Load(*this, parser);
	}
	void JsonBooleanObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonBooleanObject>::Dump(*this, formatter);
	}

	void JsonStructObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonStructObject>::Load(*this, parser);
	}
	void JsonStructObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonStructObject>::Dump(*this, formatter);
	}

	void JsonArrayObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonArrayObject>::Load(*this, parser);
	}
	void JsonArrayObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonArrayObject>::Dump(*this, formatter);
	}

	void JsonNullObject::Parse(Detail::JsonParser& parser)
	{
		JsonSerializer<JsonNullObject>::Load(*this, parser);
	}
	void JsonNullObject::Format(Detail::JsonFormatter& formatter) const
	{
		JsonSerializer<JsonNullObject>::Dump(*this, formatter);
	}
}
