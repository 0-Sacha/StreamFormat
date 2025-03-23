#pragma once

#include "stream/json/json_serializer.h"

#include <map>

namespace stream::json {
    template <typename K, typename T>
    struct JsonSerializer<std::map<K, T>> {
        using KeyType             = K;
        using StructSubObjectType = T;

        static void parse(std::map<K, T>& t, detail::JsonParser& parser) {
            JsonStructSerializer::LoadAllSubObjects<std::map<K, T>>(t, parser);
        }
        static void add_struct_sub_object(std::map<K, T>& t, std::size_t /*unused*/, std::string&& name, StructSubObjectType&& sub_object) {
            t.insert({std::move(name), std::move(sub_object)});
        }

        static void format(const std::map<K, T>& t, detail::JsonFormatter& formatter) {
            JsonStructSerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonStructSerializer::FormatObject(name, object, idx++, formatter);
            JsonStructSerializer::FormatEnd(formatter);
        }
    };

    template <typename K, typename T>
    struct JsonSerializer<std::multimap<K, T>> {
        using KeyType             = K;
        using StructSubObjectType = T;

        static void parse(std::multimap<K, T>& t, detail::JsonParser& parser) {
            JsonStructSerializer::LoadAllSubObjects<std::multimap<K, T>>(t, parser);
        }
        static void add_struct_sub_object(std::multimap<K, T>& t, std::size_t /*unused*/, std::string&& name, StructSubObjectType&& sub_object) {
            t.insert({std::move(name), std::move(sub_object)});
        }

        static void format(const std::multimap<K, T>& t, detail::JsonFormatter& formatter) {
            JsonStructSerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonStructSerializer::FormatObject(name, object, idx++, formatter);
            JsonStructSerializer::FormatEnd(formatter);
        }
    };
}  // namespace stream::json
