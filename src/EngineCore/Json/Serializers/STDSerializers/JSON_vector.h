#pragma once

#include "EngineCore/Json/JsonObjects.h"
#include "EngineCore/Json/JsonSerializer.h"

#include <vector>

namespace EngineCore::JSON
{
    template <typename T>
	struct JsonSerializer<std::vector<T>>
    {
        using ArraySubObjectType = T;

        static inline void Load(std::vector<T>& t, Detail::JsonParser& parser) {
            JsonArraySerializer::LoadAllSubObjects<std::vector<T>>(t, parser);
        }
        static inline void AddArraySubObject(std::vector<T>& t, std::size_t, ArraySubObjectType&& subObject) {
            t.emplace_back(std::move(subObject));
        }

		static inline void Dump(const std::vector<T>& t, Detail::JsonFormatter& formatter) {
            JsonArraySerializer::DumpBegin(formatter);
            std::size_t idx = 0;
            for (const ArraySubObjectType& subObject : t) 
                JsonArraySerializer::DumpObject(subObject, idx++, formatter);
            JsonArraySerializer::DumpEnd(formatter);
        }
    };
}
