#pragma once

#include "ProjectCore/Json/JsonObjects.h"
#include "ProjectCore/Json/JsonSerializer.h"

#include <unordered_map>

namespace ProjectCore::JSON
{
    template <typename K, typename T>
	struct JsonSerializer<std::unordered_map<K, T>>
    {
        using KeyType = K;
        using StructSubObjectType = T;

        static inline void Parse(std::unordered_map<K, T>& t, Detail::JsonParser& parser) {
            JsonStructSerializer::LoadAllSubObjects<std::unordered_map<K, T>>(t, parser);
        }
        static inline void AddStructSubObject(std::unordered_map<K, T>& t, std::size_t, std::string&& name, StructSubObjectType&& subObject) {
            t.insert({std::move(name), std::move(subObject)});
        }

		static inline void Format(const std::unordered_map<K, T>& t, Detail::JsonFormatter& formatter) {
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
        using KeyType = K;
        using StructSubObjectType = T;

        static inline void Parse(std::unordered_multimap<K, T>& t, Detail::JsonParser& parser) {
            JsonStructSerializer::LoadAllSubObjects<std::unordered_multimap<K, T>>(t, parser);
        }
        static inline void AddStructSubObject(std::unordered_multimap<K, T>& t, std::size_t, std::string&& name, StructSubObjectType&& subObject) {
            t.insert({std::move(name), std::move(subObject)});
        }

		static inline void Format(const std::unordered_multimap<K, T>& t, Detail::JsonFormatter& formatter) {
            JsonStructSerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonStructSerializer::FormatObject(name, object, idx++, formatter);
            JsonStructSerializer::FormatEnd(formatter);
        }
    };
}
