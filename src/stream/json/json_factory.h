#pragma once

#include "JsonFormatter-inl.h"
#include "JsonFormatter.h"
#include "JsonObjects.h"
#include "JsonParser.h"
#include "JsonSerializer.h"
#include "serializers/JsonObjectsSerializer.h"
#include "serializers/Serializers.h"

#include <filesystem>
#include <memory>

namespace stream::JSON
{
    class JsonFactory
    {
    public:
        template <typename T = std::unique_ptr<JsonObject>>
        static T FromPath(const std::filesystem::path& path);
        template <typename T = JsonObject>
        static void SaveToPath(T& json, const std::filesystem::path& path, detail::JsonFormatter::FormatSettings settings);
    };
}

#include "stream/fmt.h"
namespace stream::fmt
{
    template <typename FormatterExecutor>
    struct FormatterType<JSON::JsonObject, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const JSON::JsonObject& object, FormatterExecutor& executor)
            { return executor.WriteType(JSON::FormatAsJson<JSON::JsonObject>(object)); }
    };
}

#include <fstream>
#include <utility>
#include "stream//fmt/buffer/buffer_out_manager/dynamic_buffer_out_manager.h"
#include "serializers/JsonObjectsSerializer.h"
namespace stream::JSON
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

        fmt::detail::BufferInfoView<char> input(buffer.data(), buffer.size());
        detail::JsonParser parser(input);
        T res;
        JsonSerializer<T>::parse(res, parser);
        return res;
    }

    template <typename T>
    void JsonFactory::SaveToPath(T& json, const std::filesystem::path& path, detail::JsonFormatter::FormatSettings settings)
    {
        std::ofstream file(path.string(), std::ios::out);

        if (file.is_open() == false) throw std::runtime_error("unable to open file");

        fmt::detail::DynamicBufferOutManager<char> BufferOutManager(256);
        fmt::detail::BufferOutInfo<char> bufferOut = fmt::detail::BufferOutInfo<char>::Create(BufferOutManager).value();
        detail::JsonFormatter formatter(bufferOut, settings);
        JsonSerializer<T>::format(json, formatter);

        file.write(BufferOutManager.GetBuffer(), static_cast<std::streamsize>(BufferOutManager.GetLastGeneratedDataSize()));
        file.flush();
        file.close();
    }
}
