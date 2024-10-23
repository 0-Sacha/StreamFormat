#pragma once

#include "JsonFormatter-inl.h"
#include "JsonFormatter.h"
#include "JsonObjects.h"
#include "JsonParser.h"
#include "JsonSerializer.h"
#include "Serializers/JsonObjectsSerializer.h"
#include "Serializers/Serializers.h"

#include <filesystem>
#include <memory>

namespace StreamFormat::JSON
{
    class JsonFactory
    {
    public:
        template <typename T = std::unique_ptr<JsonObject>>
        static T FromPath(const std::filesystem::path& path);
        template <typename T = JsonObject>
        static void SaveToPath(T& json, const std::filesystem::path& path, Detail::JsonFormatter::FormatSettings settings);
    };
}

#include "StreamFormat/FMT.h"
namespace StreamFormat::FMT
{
    template <typename FormatterExecutor>
    struct FormatterType<JSON::JsonObject, FormatterExecutor>
    {
        static void Format(const JSON::JsonObject& object, FormatterExecutor& executor) { executor.WriteType(JSON::FormatAsJson<JSON::JsonObject>(object)); }
    };
}

#include <fstream>
#include <utility>
#include "StreamFormat//FMT/Buffer/BufferOutManager/DynamicBufferOutManager.h"
#include "Serializers/JsonObjectsSerializer.h"
namespace StreamFormat::JSON
{
    template <typename T>
    T JsonFactory::FromPath(const std::filesystem::path& path)
    {
        std::ifstream file(path.string(), std::ios::in);

        if (file.is_open() == false) throw std::runtime_error("unable to open file");

        std::string buffer;

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        buffer.resize(static_cast<std::size_t>(size));
        file.read(buffer.data(), size);
        file.close();

        FMT::Detail::BufferInfo<char> input(buffer.data(), buffer.size());
        Detail::JsonParser parser(input);
        T res;
        JsonSerializer<T>::Parse(res, parser);
        return res;
    }

    template <typename T>
    void JsonFactory::SaveToPath(T& json, const std::filesystem::path& path, Detail::JsonFormatter::FormatSettings settings)
    {
        std::ofstream file(path.string(), std::ios::out);

        if (file.is_open() == false) throw std::runtime_error("unable to open file");

        FMT::Detail::DynamicBufferOutManager<char> BufferOutManager(256);
        FMT::Detail::BufferOutInfo<char> bufferOut{BufferOutManager};
        Detail::JsonFormatter formatter(bufferOut, settings);
        JsonSerializer<T>::Format(json, formatter);

        file.write(BufferOutManager.GetBuffer(), static_cast<std::streamsize>(BufferOutManager.GetLastGeneratedDataSize()));
        file.flush();
        file.close();
    }
}
