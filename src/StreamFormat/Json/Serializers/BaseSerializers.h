#pragma once

#include "../JsonObjects.h"
#include "../JsonSerializer.h"

#include <utility>

namespace StreamFormat::JSON
{
    template <typename T>
    requires (std::is_integral_v<T> && !std::is_floating_point_v<T>)
    struct JsonSerializer<T>
    {
        static inline void Parse(T& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseInteger(t, parser); }
        static inline void Format(const T t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatInteger(t, formatter); }
    };

    template <typename T>
    requires std::is_floating_point_v<T>
    struct JsonSerializer<T>
    {
        static inline void Parse(T& t, Detail::JsonParser& parser) { JsonNumberSerializer::ParseFloat(t, parser); }
        static inline void Format(const T t, Detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatFloat(t, formatter); }
    };

    template <typename T, std::size_t SIZE>
    struct JsonSerializer<T[SIZE]>
    {
        using ArraySubObjectType = T;
        static inline void AddArraySubObject(T (&t)[SIZE], std::size_t idx, ArraySubObjectType&& subObject) { t[idx] = std::move(subObject); }

        static inline void Parse(T (&t)[SIZE], Detail::JsonParser& parser)
        {
            if constexpr (FMT::Detail::IsCharType<T>::Value)
            {
                // TODO
            }
            else
            {
                JsonArraySerializer::LoadAllSubObjects<T[SIZE]>(t, parser);
            }
        }

        static inline void Format(const T (&t)[SIZE], Detail::JsonFormatter& formatter)
        {
            if constexpr (FMT::Detail::IsCharType<T>::Value)
            {
                // TODO
            }
            else
            {
                JsonArraySerializer::FormatBegin(formatter);
                for (std::size_t idx = 0; idx < SIZE; ++idx)
                    JsonArraySerializer::FormatObject(t[idx], idx, formatter);
                JsonArraySerializer::FormatEnd(formatter);
            }
        }
    };
    template <typename T>
    struct JsonSerializer<T*>
    {
        static inline void Parse([[maybe_unused]] T* t, Detail::JsonParser& parser)
        {
            if (t == nullptr) throw Detail::JsonGivenTypeError{};
            // TODO
        }
        static inline void Format([[maybe_unused]] const T* t, Detail::JsonFormatter& formatter)
        {
            if (t == nullptr) throw Detail::JsonGivenTypeError{};
            // TODO
        }
    };
}
