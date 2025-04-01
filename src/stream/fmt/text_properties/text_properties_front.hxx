#pragma once

#include "base_text_properties.hxx"

namespace stream::fmt::detail {
    struct TextProperties::TextFront {
        struct ResetFront {};

        struct FrontID;
        struct Front;
    };

    struct TextProperties::TextFront::FrontID {
    public:
        static inline constexpr std::uint8_t DefaultFrontID = 10;
        static inline constexpr std::uint8_t MinFrontID     = 10;
        static inline constexpr std::uint8_t MaxFrontID     = 19;

    public:
        std::uint8_t id;

        constexpr FrontID() : id(DefaultFrontID) {}
        constexpr FrontID(std::uint8_t id_) : id(id_) {}

    public:
        constexpr bool operator==(const TextProperties::TextFront::FrontID& other) const {
            return id == other.id;
        }
        constexpr bool is_valid() const {
            return id > MinFrontID && id < MaxFrontID;
        }
    };

    bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs);

    struct TextProperties::TextFront::Front {
    public:
        constexpr Front(const TextProperties::TextFront::FrontID front_id = TextProperties::TextFront::FrontID::DefaultFrontID)
            : current_id(front_id.is_valid() ? front_id : TextProperties::TextFront::FrontID::DefaultFrontID) {}

    public:
        FrontID current_id;

    public:
        void modify_reset() {
            *this = Front{};
        }

        void apply(const TextProperties::TextFront::ResetFront&) {
            modify_reset();
        }
        void apply(const TextProperties::TextFront::Front& given) {
            *this = given;
        }
        void apply(const TextProperties::TextFront::FrontID& given) {
            current_id = given;
        }

    public:
        bool need_modif(const TextProperties::TextFront::ResetFront&) {
            return true;
        }
        bool need_modif(const TextProperties::TextFront::Front& given) {
            return *this != given;
        }
        bool need_modif(const TextProperties::TextFront::FrontID& given) {
            return current_id != given;
        }
    };

    inline bool operator==(const TextProperties::TextFront::Front& lhs, const TextProperties::TextFront::Front& rhs) {
        return lhs.current_id == rhs.current_id;
    }

    template <typename T>
    concept text_properties_front_can_apply = requires(const T& value, TextProperties::TextFront::Front& data) { data.apply(value); };

    template <typename T>
    struct TextPropertiesFrontIsapplyType {
        using BaseType              = get_base_type<T>;
        static constexpr bool value = std::is_same_v<BaseType, TextProperties::TextFront::ResetFront> || std::is_same_v<BaseType, TextProperties::TextFront::Front> ||
                                      std::is_same_v<BaseType, TextProperties::TextFront::FrontID>;
    };

    template <typename T>
    concept TextPropertiesFrontIsapply = TextPropertiesFrontIsapplyType<T>::value;
}  // namespace stream::fmt::detail
