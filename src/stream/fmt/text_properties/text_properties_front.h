#pragma once

#include "base_text_properties.h"

namespace stream::fmt::detail {
    struct TextProperties::TextFront {
        struct reset_front {};

        struct FrontID;
        struct Front;
    };

    struct TextProperties::TextFront::FrontID {
    public:
        static inline constexpr std::uint8_t DefaultFrontID = 10;
        static inline constexpr std::uint8_t MinFrontID     = 10;
        static inline constexpr std::uint8_t MaxFrontID     = 19;

    public:
        std::uint8_t ID;

        constexpr FrontID() : ID(DefaultFrontID) {}
        constexpr FrontID(std::uint8_t id) : ID(id) {}

    public:
        constexpr bool operator==(const TextProperties::TextFront::FrontID& other) const {
            return ID == other.ID;
        }
        constexpr bool IsValid() const {
            return ID > MinFrontID && ID < MaxFrontID;
        }
    };

    bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs);

    struct TextProperties::TextFront::Front {
    public:
        constexpr Front(const TextProperties::TextFront::FrontID frontId = TextProperties::TextFront::FrontID::DefaultFrontID)
            : CurrentID(frontId.IsValid() ? frontId : TextProperties::TextFront::FrontID::DefaultFrontID) {}

    public:
        FrontID CurrentID;

    public:
        void modify_reset() {
            *this = Front{};
        }

        void apply(const TextProperties::TextFront::reset_front&) {
            modify_reset();
        }
        void apply(const TextProperties::TextFront::Front& given) {
            *this = given;
        }
        void apply(const TextProperties::TextFront::FrontID& given) {
            CurrentID = given;
        }

    public:
        bool need_modif(const TextProperties::TextFront::reset_front&) {
            return true;
        }
        bool need_modif(const TextProperties::TextFront::Front& given) {
            return *this != given;
        }
        bool need_modif(const TextProperties::TextFront::FrontID& given) {
            return CurrentID != given;
        }
    };

    inline bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs) {
        return lhs.CurrentID == rhs.CurrentID;
    }

    template <typename T>
    concept text_properties_front_can_apply = requires(const T& value, TextProperties::TextFront::Front& data) { data.apply(value); };

    template <typename T>
    struct TextPropertiesFrontIsapplyType {
        using BaseType              = get_base_type<T>;
        static constexpr bool value = std::is_same_v<BaseType, TextProperties::TextFront::reset_front> || std::is_same_v<BaseType, TextProperties::TextFront::Front> ||
                                      std::is_same_v<BaseType, TextProperties::TextFront::FrontID>;
    };

    template <typename T>
    concept TextPropertiesFrontIsapply = TextPropertiesFrontIsapplyType<T>::value;
}  // namespace stream::fmt::detail
