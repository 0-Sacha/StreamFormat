#pragma once

#include "EngineCore/Json/JsonObjects.h"
#include "EngineCore/Json/JsonSerializer.h"

#include <vector>

namespace EngineCore::JSON
{
    template <typename T>
	struct JsonSerializer<std::vector<T>>
    {
        using SubObjectType = T;

        static inline void Load(std::vector<T>& t, Detail::JsonParser& parser) {
            JsonSerializer<Detail::ForwardAsJsonArray<std::vector<T>>>::LoadSubObjects(t, parser);
        }
        static inline void AddSubObject(std::vector<T>& t, std::size_t, SubObjectType&& subObject) {
            t.emplace_back(std::move(subObject));
        }

		static inline void Dump(const std::vector<T>& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<Detail::ForwardAsJsonArray<std::vector<T>>>::DumpBegin(formatter);
            std::size_t idx = 0;
            for (const SubObjectType& subObject : t) 
                JsonSerializer<Detail::ForwardAsJsonArray<std::vector<T>>>::DumpObject(subObject, idx++, formatter);
            JsonSerializer<Detail::ForwardAsJsonArray<std::vector<T>>>::DumpEnd(formatter);
        }
    };
}
