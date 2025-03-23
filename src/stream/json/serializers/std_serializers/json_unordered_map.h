#pragma once

#include "stream/json/json_objects.h"
#include "stream/json/json_serializer.h"

#include <unordered_map>

namespace stream::json
{
    template <typename K, typename T>
    struct JsonSerializer<std::unordered_map<K, T>>
    {
        using KeyType             = K;
        using StructSubObjectType = T;

        static inline void parse(std::unordered_map<K, T>& t, detail::JsonParser& parser) { JsonStructSerializer::LoadAllSubObjects<std::unordered_map<K, T>>(t, parser); }
        static inline void AddStructSubObject(std::unordered_map<K, T>& t, std::size_t, std::string&& name, StructSubObjectType&& subObject)
        {
            t.insert({std::move(name), std::move(subObject)});
        }

        static inline void format(const std::unordered_map<K, T>& t, detail::JsonFormatter& formatter)
        {
            JsonStructSerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonStructSerializer::FormatObject(name, object, idx++, formatter);
            JsonStructSerializer::FormatEnd(formatter);
        }
    };

    template <typename K, typename T>
    struct JsonSerializer<std::unordered_multimap<K, T>>
    {
        using KeyType             = K;
        using StructSubObjectType = T;

        static inline void parse(std::unordered_multimap<K, T>& t, detail::JsonParser& parser)
        {
            JsonStructSerializer::LoadAllSubObjects<std::unordered_multimap<K, T>>(t, parser);
        }
        static inline void AddStructSubObject(std::unordered_multimap<K, T>& t, std::size_t, std::string&& name, StructSubObjectType&& subObject)
        {
            t.insert({std::move(name), std::move(subObject)});
        }

        static inline void format(const std::unordered_multimap<K, T>& t, detail::JsonFormatter& formatter)
        {
            JsonStructSerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonStructSerializer::FormatObject(name, object, idx++, formatter);
            JsonStructSerializer::FormatEnd(formatter);
        }
    };
}
