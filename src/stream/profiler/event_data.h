#pragma once

#include "stream/Json.h"

namespace stream::ProfilerManager
{
    class EventData
    {
    public:
        virtual ~EventData() = default;

    public:
        virtual void ToJson(JSON::detail::JsonFormatter& formatter) const = 0;
        virtual void FromJson(JSON::detail::JsonParser& parser)           = 0;
    };

    class EventDataJsonObject final : public EventData
    {
    public:
        ~EventDataJsonObject() override = default;

    public:
        void                   ToJson(JSON::detail::JsonFormatter& formatter) const override { JSON::JsonSerializer<JSON::JsonStructObject>::format(Data, formatter); }
        void                   FromJson(JSON::detail::JsonParser& parser) override { JSON::JsonSerializer<JSON::JsonStructObject>::parse(Data, parser); }
        JSON::JsonStructObject Data;
    };
}
