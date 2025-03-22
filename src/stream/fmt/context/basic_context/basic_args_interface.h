#pragma once

#include "stream/fmt/detail/convert_traits.h"
#include "stream/fmt/detail/prelude.h"
#include "stream/fmt/buffer/buffer_info.h"

#include <any>
#include <functional>
#include <utility>

namespace stream::fmt::context
{
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class ContextExecutor;
}

namespace stream::fmt::detail
{
    struct PointerID
    {
        const std::type_info& TypeInfo;
        void* Ptr = nullptr;
    };

    template <typename TChar>
    class BasicArgsInterface
    {
    public:
        BasicArgsInterface() {}
        virtual ~BasicArgsInterface() = default;

    public:
        virtual size_t Size() = 0;

    public:
        [[nodiscard]] virtual std::expected<PointerID, FMTResult> GetPointerIDAt(std::int32_t idx) = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> RunTypeAtIndex(std::int32_t idx) = 0;
        [[nodiscard]] virtual std::expected<std::int32_t, FMTResult> GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format) = 0;
        [[nodiscard]] virtual std::expected<typename std::basic_string_view<TChar>, FMTResult> GetStringAt(std::int32_t idx) = 0;
        [[nodiscard]] virtual std::expected<std::int64_t, FMTResult> GetIntAt(std::int32_t idx) = 0;

    public:
        template <typename T>
        [[nodiscard]] std::expected<const T*, FMTResult> GetTypeAt(std::int32_t idx)
        {
            PointerID ptr = SF_TRY(GetPointerIDAt(idx));
            if (ptr.TypeInfo != typeid(T))
                { return std::unexpected(FMTResult::ArgsInterface_InvalidTypeID); }
            return reinterpret_cast<const T*>(ptr.Ptr);
        }

        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> RunFuncFromTypeAtIndex(std::int32_t idx, std::function<std::expected<void, FMTResult>(const T&)> func)
        {
            const T* value = SF_TRY(GetTypeAt<T>(idx));
            SF_TRY(func(*value));
            return {};
        }
    };

    template <typename TChar>
    class EmptyContextArgsTupleInterface : public BasicArgsInterface<TChar>
    {
    public:
        EmptyContextArgsTupleInterface() {}
        ~EmptyContextArgsTupleInterface() override = default;

    public:
        size_t Size() override { return 0; }

    public:
        [[nodiscard]] std::expected<PointerID, FMTResult> GetPointerIDAt(std::int32_t) override { return std::unexpected(FMTResult::ArgsInterface_Unavaible); }
        [[nodiscard]] std::expected<PointerID, FMTResult> RunTypeAtIndex(std::int32_t) override { return std::unexpected(FMTResult::ArgsInterface_Unavaible); }
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetIndexOfCurrentNamedArg(BufferInfoView<TChar>&) override { return std::unexpected(FMTResult::ArgsInterface_Unavaible); }
        [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> GetStringAt(std::int32_t) override { return std::unexpected(FMTResult::ArgsInterface_Unavaible); }
        [[nodiscard]] std::expected<std::int64_t, FMTResult> GetIntAt(std::int32_t) override { return std::unexpected(FMTResult::ArgsInterface_Unavaible); }
    };
}
