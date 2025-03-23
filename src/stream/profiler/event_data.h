#pragma once

#include "stream/json.h"

namespace stream::profiler
{
    class EventData
    {
    public:
        virtual ~EventData() = default;

    public:
        virtual void to_json(json::detail::JsonFormatter& formatter) const = 0;
        virtual void FromJson(json::detail::JsonParser& parser)           = 0;
    };

    class EventDataJsonObject final : public EventData
    {
    public:
        ~EventDataJsonObject() override = default;

    public:
        void                   to_json(json::detail::JsonFormatter& formatter) const override { json::JsonSerializer<json::JsonStructObject>::format(data, formatter); }
        void                   FromJson(json::detail::JsonParser& parser) override { json::JsonSerializer<json::JsonStructObject>::parse(data, parser); }
        json::JsonStructObject data;
    };
}
