#pragma once

#include "StreamFormat/FMT/Detail/ConvertTraits.h"
#include "StreamFormat/FMT/Detail/Detail.h"

#include <any>
#include <functional>
#include <utility>

namespace StreamFormat::FMT::Context
{
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class ContextExecutor;
}

namespace StreamFormat::FMT::Detail
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
        virtual void RunTypeAtIndex(std::int32_t idx) = 0;

        virtual std::int32_t GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format) = 0;
        virtual std::int32_t GetFormatIndexAt(std::int32_t idx) = 0;

        virtual PointerID GetTypeAt(std::int32_t idx) = 0;
        virtual typename std::basic_string_view<TChar> GetStringAt(std::int32_t idx) = 0;
        virtual int64_t GetIntAt(std::int32_t idx) = 0;

    public:
        template <typename T>
        const T* GetTypeAtIndex(std::int32_t idx)
        {
            PointerID ptr = GetTypeAt(idx);
            if (ptr.TypeInfo != typeid(T))
                return nullptr;
            return static_cast<const T*>(ptr.Ptr);
        }

        template <typename T>
        void RunFuncFromTypeAtIndex(std::int32_t idx, std::function<void(const T&)> func)
        {
            const T* value = GetTypeAtIndex<T>(idx);
            if (value != nullptr) func(*value);
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
        void RunTypeAtIndex(std::int32_t) override {}

        std::int32_t GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format) override { return std::int32_t{-1}; }
        std::int32_t GetFormatIndexAt(std::int32_t) override { return std::int32_t{-1}; }

        PointerID GetTypeAt(std::int32_t) override { return PointerID{.TypeInfo = typeid(void), .Ptr = nullptr}; }
        std::basic_string_view<TChar> GetStringAt(std::int32_t) override { return ""; }
        std::int64_t GetIntAt(std::int32_t) override { return 0; }
    };
}
