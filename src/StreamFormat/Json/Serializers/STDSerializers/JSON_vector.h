#pragma once

#include "StreamFormat/Json/JsonObjects.h"
#include "StreamFormat/Json/JsonSerializer.h"

#include <vector>

namespace StreamFormat::JSON
{
    template <typename T>
    struct JsonSerializer<std::vector<T>>
    {
        using ArraySubObjectType = T;

        static inline void Parse(std::vector<T>& t, Detail::JsonParser& parser) { JsonArraySerializer::LoadAllSubObjects<std::vector<T>>(t, parser); }
        static inline void AddArraySubObject(std::vector<T>& t, std::size_t, ArraySubObjectType&& subObject) { t.emplace_back(std::move(subObject)); }

        static inline void Format(const std::vector<T>& t, Detail::JsonFormatter& formatter)
        {
            JsonArraySerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const ArraySubObjectType& subObject : t)
                JsonArraySerializer::FormatObject(subObject, idx++, formatter);
            JsonArraySerializer::FormatEnd(formatter);
        }
    };
}
