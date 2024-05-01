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
        constexpr bool operator==(const TextProperties::TextFront::FrontID& other) const { return ID == other.ID; }
        constexpr bool IsValid() const { return ID > MinFrontID && ID < MaxFrontID; }
    };

    bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs);
    
    struct TextProperties::TextFront::Front
    {
    public:
        constexpr Front(const TextProperties::TextFront::FrontID frontId = TextProperties::TextFront::FrontID::DefaultFrontID)
            : CurrentID(frontId.IsValid() ? frontId : TextProperties::TextFront::FrontID::DefaultFrontID)
        {}
        
    public:
        FrontID CurrentID;

    public:
        void ModifyReset()                  { *this = Front{}; }
        
        void Apply(const TextProperties::TextFront::ResetFront&)       { ModifyReset(); }
        void Apply(const TextProperties::TextFront::Front& given)      { *this = given; }
        void Apply(const TextProperties::TextFront::FrontID& given)    { CurrentID = given; }
    
    public:
        bool NeedModif(const TextProperties::TextFront::ResetFront&)       { return true; }
        bool NeedModif(const TextProperties::TextFront::Front& given)      { return *this != given; }
        bool NeedModif(const TextProperties::TextFront::FrontID& given)    { return CurrentID != given; }
    };

    inline bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs)
    {
        return lhs.CurrentID == rhs.CurrentID;
    }

    template <typename T>
    concept TextPropertiesFrontCanApply = requires (const T& value, TextProperties::TextFront::Front& data)
    {
        data.Apply(value);
    };

    template <typename T>
    struct TextPropertiesFrontIsApplyType
    {
        using BaseType = GetBaseType<T>;
        static constexpr bool Value = std::is_same_v<BaseType, TextProperties::TextFront::ResetFront>
                                   || std::is_same_v<BaseType, TextProperties::TextFront::Front>
                                   || std::is_same_v<BaseType, TextProperties::TextFront::FrontID>;
    };

    template <typename T>
    concept TextPropertiesFrontIsApply = TextPropertiesFrontIsApplyType<T>::Value;
}
