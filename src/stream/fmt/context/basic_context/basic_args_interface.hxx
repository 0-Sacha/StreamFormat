#pragma once

#include "stream/fmt/detail/convert_traits.h"
#include "stream/fmt/detail/prelude.h"
#include "stream/fmt/buf/stream.h"

#include <any>
#include <functional>
#include <utility>

namespace stream::fmt::context {
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class context_executor;
}  // namespace stream::fmt::context

namespace stream::fmt::detail {
    struct PointerID {
        const std::type_info& type_info;
        void*                 ptr = nullptr;
    };

    template <typename TChar>
    class BasicArgsInterface {
    public:
        BasicArgsInterface() {}
        virtual ~BasicArgsInterface() = default;

    public:
        virtual size_t size() = 0;

    public:
        [[nodiscard]] virtual std::expected<PointerID, FMTResult>                              get_pointerid_at(std::int32_t idx)                             = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult>                                   run_type_at(std::int32_t idx)                                  = 0;
        [[nodiscard]] virtual std::expected<std::int32_t, FMTResult>                           get_index_of_current_named_arg(buf::StreamView<TChar>& format) = 0;
        [[nodiscard]] virtual std::expected<typename std::basic_string_view<TChar>, FMTResult> get_string_at(std::int32_t idx)                                = 0;
        [[nodiscard]] virtual std::expected<std::int64_t, FMTResult>                           get_int_at(std::int32_t idx)                                   = 0;

    public:
        template <typename T>
        [[nodiscard]] std::expected<const T*, FMTResult> get_type_at(std::int32_t idx) {
            PointerID ptr = SF_TRY(get_pointerid_at(idx));
            if (ptr.type_info != typeid(T)) {
                return std::unexpected(FMTResult::ArgsInterface_InvalidTypeID);
            }
            return reinterpret_cast<const T*>(ptr.ptr);
        }

        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> run_func_from_type_at(std::int32_t idx, std::function<std::expected<void, FMTResult>(const T&)> func) {
            const T* value = SF_TRY(get_type_at<T>(idx));
            SF_TRY(func(*value));
            return {};
        }
    };

    template <typename TChar>
    class EmptyContextArgsTupleInterface : public BasicArgsInterface<TChar> {
    public:
        EmptyContextArgsTupleInterface() {}
        ~EmptyContextArgsTupleInterface() override = default;

    public:
        size_t size() override {
            return 0;
        }

    public:
        [[nodiscard]] std::expected<PointerID, FMTResult> get_pointerid_at(std::int32_t) override {
            return std::unexpected(FMTResult::ArgsInterface_Unavaible);
        }
        [[nodiscard]] std::expected<PointerID, FMTResult> run_type_at(std::int32_t) override {
            return std::unexpected(FMTResult::ArgsInterface_Unavaible);
        }
        [[nodiscard]] std::expected<std::int32_t, FMTResult> get_index_of_current_named_arg(buf::StreamView<TChar>&) override {
            return std::unexpected(FMTResult::ArgsInterface_Unavaible);
        }
        [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> get_string_at(std::int32_t) override {
            return std::unexpected(FMTResult::ArgsInterface_Unavaible);
        }
        [[nodiscard]] std::expected<std::int64_t, FMTResult> get_int_at(std::int32_t) override {
            return std::unexpected(FMTResult::ArgsInterface_Unavaible);
        }
    };
}  // namespace stream::fmt::detail
