#pragma once

#include "../json_objects.h"
#include "../json_serializer.h"

#include <utility>

namespace stream::json {
    template <typename T>
        requires(std::is_integral_v<T> && !std::is_floating_point_v<T>)
    struct JsonSerializer<T> {
        static inline void parse(T& t, detail::JsonParser& parser) {
            JsonNumberSerializer::ParseInteger(t, parser);
        }
        static inline void format(const T t, detail::JsonFormatter& formatter) {
            JsonNumberSerializer::FormatInteger(t, formatter);
        }
    };

    template <typename T>
        requires std::is_floating_point_v<T>
    struct JsonSerializer<T> {
        static inline void parse(T& t, detail::JsonParser& parser) {
            JsonNumberSerializer::ParseFloat(t, parser);
        }
        static inline void format(const T t, detail::JsonFormatter& formatter) {
            JsonNumberSerializer::FormatFloat(t, formatter);
        }
    };

    template <typename T, std::size_t SIZE>
    struct JsonSerializer<T[SIZE]> {
        using ArraySubObjectType = T;
        static inline void AddArraySubObject(T (&t)[SIZE], std::size_t idx, ArraySubObjectType&& subObject) {
            t[idx] = std::move(subObject);
        }

        static inline void parse(T (&t)[SIZE], detail::JsonParser& parser) {
            if constexpr (fmt::detail::IsCharType<T>::value) {
                // TODO
            } else {
                JsonArraySerializer::LoadAllSubObjects<T[SIZE]>(t, parser);
            }
        }

        static inline void format(const T (&t)[SIZE], detail::JsonFormatter& formatter) {
            if constexpr (fmt::detail::IsCharType<T>::value) {
                // TODO
            } else {
                JsonArraySerializer::FormatBegin(formatter);
                for (std::size_t idx = 0; idx < SIZE; ++idx)
                    JsonArraySerializer::FormatObject(t[idx], idx, formatter);
                JsonArraySerializer::FormatEnd(formatter);
            }
        }
    };
    template <typename T>
    struct JsonSerializer<T*> {
        static inline void parse([[maybe_unused]] T* t, detail::JsonParser& parser) {
            if (t == nullptr) throw detail::JsonGivenTypeError{};
            // TODO
        }
        static inline void format([[maybe_unused]] const T* t, detail::JsonFormatter& formatter) {
            if (t == nullptr) throw detail::JsonGivenTypeError{};
            // TODO
        }
    };
}  // namespace stream::json
