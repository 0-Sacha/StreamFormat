#pragma once

#include "StreamFormat/Json/JsonSerializer.h"

#include <map>

namespace StreamFormat::JSON
{
    template <typename K, typename T>
    struct JsonSerializer<std::map<K, T>>
    {
        using KeyType             = K;
        using StructSubObjectType = T;

        static inline void Parse(std::map<K, T>& t, Detail::JsonParser& parser) { JsonStructSerializer::LoadAllSubObjects<std::map<K, T>>(t, parser); }
        static inline void AddStructSubObject(std::map<K, T>& t, std::size_t, std::string&& name, StructSubObjectType&& subObject)
        {
            t.insert({std::move(name), std::move(subObject)});
        }

        static inline void Format(const std::map<K, T>& t, Detail::JsonFormatter& formatter)
        {
            JsonStructSerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonStructSerializer::FormatObject(name, object, idx++, formatter);
            JsonStructSerializer::FormatEnd(formatter);
        }
    };

    template <typename K, typename T>
    struct JsonSerializer<std::multimap<K, T>>
    {
        using KeyType             = K;
        using StructSubObjectType = T;

        static inline void Parse(std::multimap<K, T>& t, Detail::JsonParser& parser) { JsonStructSerializer::LoadAllSubObjects<std::multimap<K, T>>(t, parser); }
        static inline void AddStructSubObject(std::multimap<K, T>& t, std::size_t, std::string&& name, StructSubObjectType&& subObject)
        {
            t.insert({std::move(name), std::move(subObject)});
        }

        static inline void Format(const std::multimap<K, T>& t, Detail::JsonFormatter& formatter)
        {
            JsonStructSerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonStructSerializer::FormatObject(name, object, idx++, formatter);
            JsonStructSerializer::FormatEnd(formatter);
        }
    };
}
