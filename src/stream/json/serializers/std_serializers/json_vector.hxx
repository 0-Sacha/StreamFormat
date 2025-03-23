#pragma once

#include "stream/json/json_objects.hxx"
#include "stream/json/json_serializer.hxx"

#include <vector>

namespace stream::json {
    template <typename T>
    struct JsonSerializer<std::vector<T>> {
        using ArraySubObjectType = T;

        static inline void parse(std::vector<T>& t, detail::JsonParser& parser) {
            JsonArraySerializer::LoadAllSubObjects<std::vector<T>>(t, parser);
        }
        static inline void AddArraySubObject(std::vector<T>& t, std::size_t, ArraySubObjectType&& subObject) {
            t.emplace_back(std::move(subObject));
        }

        static inline void format(const std::vector<T>& t, detail::JsonFormatter& formatter) {
            JsonArraySerializer::FormatBegin(formatter);
            std::size_t idx = 0;
            for (const ArraySubObjectType& subObject : t)
                JsonArraySerializer::FormatObject(subObject, idx++, formatter);
            JsonArraySerializer::FormatEnd(formatter);
        }
    };
}  // namespace stream::json
