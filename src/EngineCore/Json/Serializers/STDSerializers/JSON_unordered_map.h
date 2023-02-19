#pragma once

#include "EngineCore/Json/JsonObjects.h"
#include "EngineCore/Json/JsonSerializer.h"

#include <unordered_map>

namespace EngineCore::JSON
{
    template <typename K, typename T>
	struct JsonSerializer<std::unordered_map<K, T>>
    {
        using KeyType = K;
        using SubObjectType = T;

        static inline void Load(std::unordered_map<K, T>& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonStruct<std::unordered_map<K, T>>>::LoadSubObjects(t, parser);
        }
        static inline void AddSubObject(std::unordered_map<K, T>& t, std::size_t, std::string&& name, SubObjectType&& subObject) {
            t.insert({std::move(name), std::move(subObject)});
        }

		static inline void Dump(const std::unordered_map<K, T>& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonArray<std::unordered_map<K, T>>>::DumpBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonSerializer<Detail::ForwardAsJsonStruct<std::unordered_map<K, T>>>::DumpObject(name, object, idx++, formatter);
            JsonSerializer<Detail::ForwardAsJsonArray<std::unordered_map<K, T>>>::DumpEnd(formatter);
        }
    };

    template <typename K, typename T>
	struct JsonSerializer<std::unordered_multimap<K, T>>
    {
        using KeyType = K;
        using SubObjectType = T;

        static inline void Load(std::unordered_multimap<K, T>& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonStruct<std::unordered_multimap<K, T>>>::LoadSubObjects(t, parser);
        }
        static inline void AddSubObject(std::unordered_multimap<K, T>& t, std::size_t, std::string&& name, SubObjectType&& subObject) {
            t.insert({std::move(name), std::move(subObject)});
        }

		static inline void Dump(const std::unordered_multimap<K, T>& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonArray<std::unordered_multimap<K, T>>>::DumpBegin(formatter);
            std::size_t idx = 0;
            for (const auto& [name, object] : t)
                JsonSerializer<Detail::ForwardAsJsonStruct<std::unordered_multimap<K, T>>>::DumpObject(name, object, idx++, formatter);
            JsonSerializer<Detail::ForwardAsJsonArray<std::unordered_multimap<K, T>>>::DumpEnd(formatter);
        }
    };
}
