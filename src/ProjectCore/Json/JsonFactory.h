#pragma once

#include "JsonObjects.h"
#include "JsonFormatter.h"
#include "JsonFormatter.impl"
#include "JsonParser.h"
#include "JsonSerializer.h"
#include "Serializers/JsonObjectsSerializer.h"
#include "Serializers/Serializers.h"

#include <filesystem>
#include <memory>

namespace ProjectCore::JSON
{
    class JsonFactory
    {
    public:
        template<typename T = std::unique_ptr<JsonObject>>
        static T FromPath(const std::filesystem::path& path);
        template<typename T = JsonObject>
        static void SaveToPath(T& json, const std::filesystem::path& path, Detail::JsonFormatter::FormatSettings settings);
    };
}

#include "ProjectCore/FMT/FMT.h"
namespace ProjectCore::FMT
{
    template<typename FormatterContext>
    struct FormatterType<JSON::JsonObject, FormatterContext> {
        static void Format(const JSON::JsonObject& object, FormatterContext& context)
        {
            context.RunType(JSON::FormatAsJson<JSON::JsonObject>(object));
        }
    };
}

#include "ProjectCore//FMT/Detail/Buffer/BufferOutManager/DynamicBufferOutManager.h"
#include <fstream>
#include <utility>
#include "Serializers/JsonObjectsSerializer.h"
namespace ProjectCore::JSON
{
    template<typename T>
    T JsonFactory::FromPath(const std::filesystem::path& path)
    {
        std::ifstream file(path.string(), std::ios::in);
        
        if (file.is_open() == false)
            throw std::runtime_error("unable to open file");
        
        std::string buffer;

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        buffer.resize(static_cast<std::size_t>(size));
        file.read(buffer.data(), size);
        file.close();

        FMT::Detail::BufferInProperties<char> parserProperties(buffer.data(), buffer.size());
        Detail::JsonParser parser(parserProperties);
        T res;
        JsonSerializer<T>::Parse(res, parser);
        return res;
    }
    
    template<typename T>
    void JsonFactory::SaveToPath(T& json, const std::filesystem::path& path, Detail::JsonFormatter::FormatSettings settings)
    {
        std::ofstream file(path.string(), std::ios::out);

        if (file.is_open() == false)
            throw std::runtime_error("unable to open file");

        FMT::Detail::DynamicBufferOutManager<char> BufferOutManager(256);
        Detail::JsonFormatter formatter(BufferOutManager, settings);
        JsonSerializer<T>::Format(json, formatter);
        
        file.write(BufferOutManager.GetBuffer(), static_cast<std::streamsize>(BufferOutManager.GetLastGeneratedDataSize()));
        file.flush();
        file.close();
    }
}
