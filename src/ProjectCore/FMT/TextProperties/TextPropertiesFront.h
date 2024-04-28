#pragma once

#include "BaseTextProperties.h"

namespace ProjectCore::FMT::Detail
{
    struct TextProperties::TextFront
    {
        struct ResetFront {};

        struct FrontID;
        struct Front;
    };

    struct TextProperties::TextFront::FrontID
    {
    public:
        static inline constexpr std::uint8_t DefaultFrontID    = 10;
        static inline constexpr std::uint8_t MinFrontID        = 10;
        static inline constexpr std::uint8_t MaxFrontID        = 19;

    public:
        std::uint8_t ID;

        constexpr FrontID()                 : ID(DefaultFrontID) {}
        constexpr FrontID(std::uint8_t id)  : ID(id) {}
    
    public:
        constexpr bool operator==(const FrontID& other) const { return ID == other.ID; }
        constexpr bool IsValid() const { return ID > MinFrontID && ID < MaxFrontID; }
    };

    bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs);
    
    struct TextProperties::TextFront::Front
    {
    public:
        constexpr Front(const FrontID frontId = FrontID::DefaultFrontID)
            : CurrentID(frontId.IsValid() ? frontId : FrontID::DefaultFrontID)
        {}
        
    public:
        FrontID CurrentID;

    public:
        void ModifyReset()                  { *this = Front{}; }
        
        void Apply(const ResetFront&)       { ModifyReset(); }
        void Apply(const Front& given)      { *this = given; }
        void Apply(const FrontID& given)    { CurrentID = given; }
    
    public:
        bool NeedModif(const ResetFront&)       { return true; }
        bool NeedModif(const Front& given)      { return *this != given; }
        bool NeedModif(const FrontID& given)    { return CurrentID != given; }
    };

    template<typename T>
    concept TextPropertiesFrontCanApply = requires (const T& value, TextProperties::TextFront::Front& data)
    {
        data.Apply(value);
    };

    inline bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs)
    {
        return lhs.CurrentID == rhs.CurrentID;
    }
}
