#pragma once

#include "json_formatter_impl.h"
#include "json_formatter.h"
#include "json_objects.h"
#include "json_parser.h"
#include "json_serializer.h"
#include "serializers/json_objects_serializer.h"
#include "serializers/serializers.h"

#include <filesystem>
#include <memory>

namespace stream::json {
    class JsonFactory {
    public:
        template <typename T = std::unique_ptr<JsonObject>>
        static T FromPath(const std::filesystem::path& path);
        template <typename T = JsonObject>
        static void SaveToPath(T& json, const std::filesystem::path& path, detail::JsonFormatter::FormatSettings settings);
    };
}  // namespace stream::json

#include "stream/fmt.h"
namespace stream::fmt {
    template <typename FormatterExecutor>
    struct FormatterType<json::JsonObject, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const json::JsonObject& object, FormatterExecutor& executor) {
            return executor.write_type(json::FormatAsJson<json::JsonObject>(object));
        }
    };
}  // namespace stream::fmt

#include <fstream>
#include <utility>
#include "stream//fmt/buf/streamio_manager/dynamic_streamio_manager.h"
#include "serializers/json_objects_serializer.h"
namespace stream::json {
    template <typename T>
    T JsonFactory::FromPath(const std::filesystem::path& path) {
        std::ifstream file(path.string(), std::ios::in);

        if (file.is_open() == false) throw std::runtime_error("unable to open file");

        std::string buffer;

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        buffer.resize(static_cast<std::size_t>(size));
        file.read(buffer.data(), size);
        file.close();

        fmt::buf::StreamView<char> input(buffer.data(), buffer.size());
        detail::JsonParser         parser(input);
        T                          res;
        JsonSerializer<T>::parse(res, parser);
        return res;
    }

    template <typename T>
    void JsonFactory::SaveToPath(T& json, const std::filesystem::path& path, detail::JsonFormatter::FormatSettings settings) {
        std::ofstream file(path.string(), std::ios::out);

        if (file.is_open() == false) throw std::runtime_error("unable to open file");

        fmt::buf::DynamicStreamIOManager<char> StreamIOManager(256);
        fmt::buf::StreamIO<char>               ostream = fmt::buf::StreamIO<char>::create(StreamIOManager).value();
        detail::JsonFormatter                  formatter(ostream, settings);
        JsonSerializer<T>::format(json, formatter);

        file.write(StreamIOManager.get_buffer(), static_cast<std::streamsize>(StreamIOManager.get_last_generated_data_size()));
        file.flush();
        file.close();
    }
}  // namespace stream::json
