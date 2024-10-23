
#pragma once

#include "StreamFormat/FMT/Context/BasicContext/BasicArgsInterface.h"
#include "StreamFormat/FMT/Detail/Detail.h"

#include "FormatterType.h"

namespace StreamFormat::FMT::Detail
{
    template <typename... Types>
    struct FormatterArgs;

    template <>
    struct FormatterArgs<>
    {
    public:
        FormatterArgs() = default;

    public:
        static inline constexpr std::size_t Size() { return 0; }

    public:
        template <typename FormatterExecutor>
        inline void RunTypeAtIndex(FormatterExecutor&, std::int32_t)
        {
            throw Detail::FMTGivenIndexError();
        }

        template <typename FormatterExecutor>
        inline std::int32_t GetIndexOfCurrentNamedArg(FormatterExecutor&, std::int32_t)
        {
            return std::int32_t{-1};
        }

        inline PointerID GetTypeAtIndex(std::int32_t) { return PointerID{.TypeInfo = typeid(void), .Ptr = nullptr}; }

        template <typename T>
        inline void GetTypeAtIndexConvert(T*, std::int32_t)
            {}
    };

    template <typename Type, typename... Rest>
    struct FormatterArgs<Type, Rest...> : public FormatterArgs<Rest...>
    {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        FormatterArgs(const TypeWithoutRef& t, Rest&&... rest)
            : FormatterArgs<Rest...>(std::forward<Rest>(rest)...)
            , m_Value(t)
        {}

    private:
        const TypeWithoutRef& m_Value;

    public:
        static inline constexpr std::size_t Size() { return sizeof...(Rest) + 1; }

    public:
        template <typename Executor>
        inline void RunTypeAtIndex(Executor& executor, std::int32_t idx)
        {
            if (idx == 0) return executor.WriteType(m_Value);
            return FormatterArgs<Rest...>::RunTypeAtIndex(executor, idx - 1);
        }

    public:
        template <typename TChar>
        inline std::int32_t GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format, std::int32_t beginSearchIndex)
        {
            if constexpr (Detail::IsANamedArgs<Detail::GetBaseType<TypeWithoutRef>>::value)
            {
                if (Detail::FMTBufferParamsManip(format).NextIsNamedArgs(m_Value.GetName()))
                    return beginSearchIndex;
            }
            return FormatterArgs<Rest...>::GetIndexOfCurrentNamedArg(format, beginSearchIndex + 1);
        }

    public:
        inline PointerID GetTypeAtIndex(std::int32_t idx)
        {
            if (idx == 0) return PointerID{.TypeInfo = typeid(const TypeWithoutRef), .Ptr = const_cast<void*>(static_cast<const void*>(&m_Value))};
            return FormatterArgs<Rest...>::GetTypeAtIndex(idx - 1);
        }

    public:
        template <typename T>
        inline void GetTypeAtIndexConvert(T* value, std::int32_t idx)
        {
            if (idx == 0)
            {
                if constexpr (FMTCanContextConvert<TypeWithoutRef, T>)
                {
                    *value = FMTContextConvert<TypeWithoutRef, T>::Convert(m_Value);
                    return;
                }
                else
                {
                    // Warrning : Need to transmit : 'Could not convert'
                    return;
                }
            }
            return FormatterArgs<Rest...>::template GetTypeAtIndexConvert<T>(value, idx - 1);
        }
    };

    template <typename TChar, typename FormatterExecutor, typename... Args>
    class FormatterArgsInterface : public BasicArgsInterface<TChar>
    {
    public:
        using ContextArgsType = FormatterArgs<Args...>;
        
    public:
        FormatterArgsInterface(FormatterExecutor& executor, Args&&... args)
            : BasicArgsInterface<TChar>()
            , Executor(executor)
            , ArgsInterface(std::forward<Args>(args)...)
        {}
        ~FormatterArgsInterface() override = default;

    public:
        size_t Size() override { return ArgsInterface.Size(); }

        void RunTypeAtIndex(std::int32_t idx) override
        {
            return ArgsInterface.RunTypeAtIndex(Executor, idx);
        }
        std::int32_t GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format) override
        {
            return ArgsInterface.GetIndexOfCurrentNamedArg(format, std::int32_t{0});
        }
        PointerID GetTypeAt(std::int32_t idx) override
        {
            return ArgsInterface.GetTypeAtIndex(idx); 
        }

    public:
        template <typename T>
        T GetTAtConvert(std::int32_t idx)
        {
            T res;
            ArgsInterface.template GetTypeAtIndexConvert<T>(&res, idx);
            return res;
        }

        std::int32_t GetFormatIndexAt(std::int32_t idx) override { return GetTAtConvert<std::int32_t>(idx); }

        std::basic_string_view<TChar> GetStringAt(std::int32_t idx) override
        {
            return GetTAtConvert<std::basic_string_view<TChar>>(idx);
        }

        std::int64_t GetIntAt(std::int32_t idx) override { return GetTAtConvert<std::int64_t>(idx); }

    protected:
        FormatterExecutor& Executor;
        ContextArgsType ArgsInterface;
    };
}
