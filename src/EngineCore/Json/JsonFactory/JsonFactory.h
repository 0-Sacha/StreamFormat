#pragma once

#include "EngineCore/Json/Json.h"
#include <filesystem>

namespace EngineCore::JSON
{
    class JsonFactory
    {
	public:
		static JsonContext FromPath(const std::filesystem::path& path);
		static void SaveToPath(JsonContext& json, const std::filesystem::path& path);
    };
}

namespace EngineCore::JSON::Detail
{
	class JsonFactoryDetail
	{
	public:
		static void ToFMTBufferOut(const JsonContext& json, FMT::Detail::BasicBufferOut<char>& buffer)
		{
			JsonFormatter jsonFormatter(buffer.GetBufferManager());
			jsonFormatter.BufferOut().ReloadBuffer(buffer);
			jsonFormatter.DumpJsonObject(json.GetObjects());
			buffer.ReloadBuffer(jsonFormatter.BufferOut());
		}
	};
}

#include "EngineCore//FMT/Formatter.h"
namespace EngineCore::FMT
{
	template<typename FormatterContext>
	struct FormatterType<JSON::JsonContext, FormatterContext> {
		static void Write(const typename JSON::JsonContext& json, FormatterContext& context)
		{
			JSON::Detail::JsonFactoryDetail::ToFMTBufferOut(json, context.BufferOut());
		}
	};
}
