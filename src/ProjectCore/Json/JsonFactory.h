#pragma once

#include "JsonObjects.h"
#include "JsonFormatter.h"
#include "JsonFormatter.impl"
#include "JsonParser.h"
#include "JsonSerializer.h"
#include "Serializers/JsonObjectsSerializer.h"

#include <filesystem>
#include <memory>

namespace ProjectCore::JSON
{
    class JsonFactory
    {
	public:
		static std::unique_ptr<JsonObject> FromPath(const std::filesystem::path& path);
		static void SaveToPath(JsonObject& json, const std::filesystem::path& path);
    };
}

#include "ProjectCore/FMT/FMT.h"
namespace ProjectCore::FMT
{
	template<typename FormatterContext>
	struct FormatterType<JSON::JsonObject, FormatterContext> {
		static void Format(const JSON::JsonObject& object, FormatterContext& context)
		{
			JSON::FormatAsJson<JSON::JsonObject> format(object);
			context.RunType(object);
		}
	};
}
