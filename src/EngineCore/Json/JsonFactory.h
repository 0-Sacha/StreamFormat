#pragma once

#include "JsonObjects.h"
#include "JsonFormatter.h"
#include "JsonParser.h"
#include "JsonSerializer.h"
#include "JsonObjectsSerializer.h"

#include <filesystem>
#include <memory>

namespace EngineCore::JSON
{
    class JsonFactory
    {
	public:
		static std::unique_ptr<JsonObject> FromPath(const std::filesystem::path& path);
		static void SaveToPath(JsonObject& json, const std::filesystem::path& path);
    };
}

namespace EngineCore::JSON::Detail
{
	class JsonFactoryDetail
	{
	public:
		static void ToFMTBufferOut(const JsonObject& json, FMT::Detail::BasicBufferOut<char>& buffer)
		{
			JsonFormatter jsonFormatter(buffer.GetBufferManager());
			jsonFormatter.BufferOut().ReloadBuffer(buffer);
			JsonSerializer<JsonObject>::Dump(json, jsonFormatter);
			buffer.ReloadBuffer(jsonFormatter.BufferOut());
		}
	};
}

#include "EngineCore//FMT/Formatter.h"
namespace EngineCore::FMT
{
	template<typename FormatterContext>
	struct FormatterType<JSON::JsonObject, FormatterContext> {
		static void Write(const typename JSON::JsonObject& json, FormatterContext& context)
		{
			JSON::Detail::JsonFactoryDetail::ToFMTBufferOut(json, context.BufferOut());
		}
	};
}
