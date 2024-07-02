#pragma once

#include "ProjectCore/Json.h"

namespace ProjectCore::ProfilerManager
{
    class EventData
    {
    public:
        virtual ~EventData() = default;

    public:
        virtual void ToJson(JSON::Detail::JsonFormatter& formatter) const = 0;
        virtual void FromJson(JSON::Detail::JsonParser& parser)           = 0;
    };

    class EventDataJsonObject final : public EventData
    {
    public:
        ~EventDataJsonObject() override = default;

    public:
        void                   ToJson(JSON::Detail::JsonFormatter& formatter) const override { JSON::JsonSerializer<JSON::JsonStructObject>::Format(Data, formatter); }
        void                   FromJson(JSON::Detail::JsonParser& parser) override { JSON::JsonSerializer<JSON::JsonStructObject>::Parse(Data, parser); }
        JSON::JsonStructObject Data;
    };
}
