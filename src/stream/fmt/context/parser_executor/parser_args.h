#pragma once

#include "stream/fmt/context/basic_context/basic_args_interface.h"
#include "stream/fmt/detail/prelude.h"

namespace stream::fmt::detail
{
    /****************************/
    /******** Args tuple ********/
    /****************************/
    template <typename... Types>
    struct ParserArgs;

    template <>
    struct ParserArgs<>
    {
    public:
        ParserArgs() = default;

    public:
        static inline constexpr std::size_t Size() { return 0; }

    public:
        template <typename FormatterExecutor>
        [[nodiscard]] inline std::expected<void, FMTResult> RunTypeAtIndex(FormatterExecutor&, std::int32_t)
        {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
        template <typename TChar>
        [[nodiscard]] inline std::expected<std::int32_t, FMTResult> GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format, std::int32_t)
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
    struct ParserArgs<Type, Rest...> : ParserArgs<Rest...>
    {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        ParserArgs(TypeWithoutRef& t, Rest&... rest)
            : ParserArgs<Rest...>(std::forward<Rest>(rest)...)
            , m_Value(t)
        {}

    private:
        TypeWithoutRef& m_Value;

    public:
        static inline constexpr std::size_t Size() { return sizeof...(Rest) + 1; }

    public:
        template <typename Executor>
        [[nodiscard]] inline std::expected<void, FMTResult> RunTypeAtIndex(Executor& executor, std::int32_t idx)
        {
            if (idx == 0)
            {
                return executor.ReadType(m_Value);
            }
            return ParserArgs<Rest...>::RunTypeAtIndex(executor, idx - 1);
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
            return ParserArgs<Rest...>::GetIndexOfCurrentNamedArg(format, beginSearchIndex + 1);
        }

    public:
        [[nodiscard]] inline std::expected<PointerID, FMTResult> GetPointerIDAt(std::int32_t idx)
        {
            if (idx == 0) return PointerID{.TypeInfo = typeid(TypeWithoutRef), .Ptr = static_cast<void*>(&m_Value)};
            return ParserArgs<Rest...>::GetPointerIDAt(idx - 1);
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
            return ParserArgs<Rest...>::template GetConvertedTypeAt<T>(idx - 1);
        }
    };


    /********************************/
    /******** Args interface ********/
    /********************************/
    template <typename TChar, typename ParserExecutor, typename... Args>
    class ParserArgsInterface : public BasicArgsInterface<TChar>
    {
    public:
        using ContextArgsType = ParserArgs<Args...>;

    public:
        ParserArgsInterface(ParserExecutor& executor, Args&&... args)
            : BasicArgsInterface<TChar>()
            , Executor(executor)
            , ArgsInterface(std::forward<Args>(args)...)
        {}
        ~ParserArgsInterface() override = default;

    public:
        std::size_t Size() override { return ArgsInterface.Size(); }

    public:
        [[nodiscard]] std::expected<void, FMTResult> RunTypeAtIndex(std::int32_t idx) override
        {
            return ArgsInterface.RunTypeAtIndex(Executor, idx);
        }
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetIndexOfCurrentNamedArg(BufferInfoView<TChar>& format) override
        {
            return ArgsInterface.GetIndexOfCurrentNamedArg(format, std::int32_t{0});
        }
        [[nodiscard]] inline std::expected<PointerID, FMTResult> GetPointerIDAt(std::int32_t idx) override
        {
            return ArgsInterface.GetPointerIDAt(idx);
        }

    public:
        [[nodiscard]] std::expected<typename std::basic_string_view<TChar>, FMTResult> GetStringAt(std::int32_t idx) override
        {
            return ArgsInterface.template GetConvertedTypeAt<typename std::basic_string_view<TChar>>(idx);
        }
        [[nodiscard]] std::expected<std::int64_t, FMTResult> GetIntAt(std::int32_t idx) override
        {
            return ArgsInterface.template GetConvertedTypeAt<std::int64_t>(idx);
        }

    protected:
        ParserExecutor& Executor;
        ContextArgsType ArgsInterface;
    };
}
