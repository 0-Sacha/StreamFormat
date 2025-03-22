
#pragma once

#include "stream/fmt/context/basic_context/basic_args_interface.h"
#include "stream/fmt/detail/prelude.h"

#include "formatter_type.h"

namespace stream::fmt::detail
{
    /****************************/
    /******** Args tuple ********/
    /****************************/
    template <typename... Types>
    struct FormatterArgs;

    template <>
    struct FormatterArgs<>
    {
    public:
        static inline constexpr std::size_t Size() { return 0; }

    public:
        template <typename FormatterExecutor>
        [[nodiscard]] inline std::expected<void, FMTResult> RunTypeAtIndex(FormatterExecutor&, std::int32_t)
        {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
        template <typename TChar>
        [[nodiscard]] inline std::expected<std::int32_t, FMTResult> GetIndexOfCurrentNamedArg(BufferInfoView<TChar>&, std::int32_t)
        {
            return std::unexpected(FMTResult::ArgsInterface_CantMatchNamedArgs);
        }
        [[nodiscard]] inline std::expected<PointerID, FMTResult> GetPointerIDAt(std::int32_t)
        {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
        template <typename T>
        [[nodiscard]] inline std::expected<T, FMTResult> GetConvertedTypeAt(std::int32_t)
        {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
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
        [[nodiscard]] inline std::expected<void, FMTResult> RunTypeAtIndex(Executor& executor, std::int32_t idx)
        {
            if (idx == 0)
            {
                return executor.WriteType(m_Value);
            }
            return FormatterArgs<Rest...>::RunTypeAtIndex(executor, idx - 1);
        }

    public:
        template <typename TChar>
        [[nodiscard]] inline std::expected<std::int32_t, FMTResult> GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format, std::int32_t beginSearchIndex)
        {
            if constexpr (detail::IsANamedArgs<detail::GetBaseType<TypeWithoutRef>>::value)
            {
                bool currentIsANamedArg = SF_TRY(detail::FMTBufferParamsManip(format).NextIsNamedArgs(m_Value.GetName()));
                if (currentIsANamedArg)
                    return beginSearchIndex;
            }
            return FormatterArgs<Rest...>::GetIndexOfCurrentNamedArg(format, beginSearchIndex + 1);
        }

    public:
        [[nodiscard]] inline std::expected<PointerID, FMTResult> GetPointerIDAt(std::int32_t idx)
        {
            if (idx == 0)
                return PointerID{.TypeInfo = typeid(const TypeWithoutRef), .Ptr = const_cast<void*>(static_cast<const void*>(&m_Value))};
            return FormatterArgs<Rest...>::GetPointerIDAt(idx - 1);
        }

    public:
        template <typename T>
        [[nodiscard]] inline std::expected<T, FMTResult> GetConvertedTypeAt(std::int32_t idx)
        {
            if (idx == 0)
            {
                if constexpr (FMTCanContextConvert<TypeWithoutRef, T>)
                    { return FMTContextConvert<TypeWithoutRef, T>::Convert(m_Value); }
                else
                    { return std::unexpected(FMTResult::ArgsInterface_InvalidConversion); }
            }
            return FormatterArgs<Rest...>::template GetConvertedTypeAt<T>(idx - 1);
        }
    };


    /********************************/
    /******** Args interface ********/
    /********************************/
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

        [[nodiscard]] std::expected<void, FMTResult> RunTypeAtIndex(std::int32_t idx) override
        {
            return ArgsInterface.RunTypeAtIndex(Executor, idx);
        }
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format) override
        {
            return ArgsInterface.GetIndexOfCurrentNamedArg(format, std::int32_t{0});
        }
        [[nodiscard]] std::expected<PointerID, FMTResult> GetPointerIDAt(std::int32_t idx) override
        {
            return ArgsInterface.GetPointerIDAt(idx); 
        }

    public:
        [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> GetStringAt(std::int32_t idx) override
        {
            return ArgsInterface.template GetConvertedTypeAt<std::basic_string_view<TChar>>(idx);
        }
        [[nodiscard]] std::expected<std::int64_t, FMTResult> GetIntAt(std::int32_t idx) override
        {
            return ArgsInterface.template GetConvertedTypeAt<std::int64_t>(idx);
        }

    protected:
        FormatterExecutor& Executor;
        ContextArgsType ArgsInterface;
    };
}
