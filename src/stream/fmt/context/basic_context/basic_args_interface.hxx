#pragma once

#include "stream/fmt/detail/convert_traits.hxx"
#include "stream/fmt/detail/prelude.hxx"
#include "stream/fmt/buf/stream.hxx"

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
        virtual PointerID                              get_pointerid_at(std::int32_t idx)                             = 0;
        virtual void                                   run_type_at(std::int32_t idx)                                  = 0;
        virtual std::optional<std::int32_t>            get_index_of_current_named_arg(buf::StreamView<TChar>& format) = 0;
        virtual typename std::basic_string_view<TChar> get_string_at(std::int32_t idx)                                = 0;
        virtual std::int64_t                           get_int_at(std::int32_t idx)                                   = 0;

    public:
        template <typename T>
        const T* get_type_at(std::int32_t idx) {
            PointerID ptr = get_pointerid_at(idx);
            if (ptr.type_info != typeid(T)) {
                throw std::runtime_error("fmt error: ArgsInterface_InvalidTypeID");
            }
            return reinterpret_cast<const T*>(ptr.ptr);
        }

        template <typename T>
        void run_func_from_type_at(std::int32_t idx, std::function<void(const T&)> func) {
            const T* value = get_type_at<T>(idx);
            func(*value);
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
        PointerID get_pointerid_at(std::int32_t) override {
            throw std::runtime_error("fmt error: ArgsInterface_Unavailble");
        }
        PointerID run_type_at(std::int32_t) override {
            throw std::runtime_error("fmt error: ArgsInterface_Unavailble");
        }
        std::optional<std::int32_t> get_index_of_current_named_arg(buf::StreamView<TChar>&) override {
            throw std::runtime_error("fmt error: ArgsInterface_Unavailble");
            return std::nullopt;
        }
        std::basic_string_view<TChar> get_string_at(std::int32_t) override {
            throw std::runtime_error("fmt error: ArgsInterface_Unavailble");
        }
        std::int64_t get_int_at(std::int32_t) override {
            throw std::runtime_error("fmt error: ArgsInterface_Unavailble");
        }
    };
}  // namespace stream::fmt::detail
