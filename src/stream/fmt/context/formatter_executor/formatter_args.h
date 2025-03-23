
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
        static inline constexpr std::size_t size() { return 0; }

    public:
        template <typename FormatterExecutor>
        [[nodiscard]] inline std::expected<void, FMTResult> run_type_at(FormatterExecutor&, std::int32_t)
        {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
        template <typename TChar>
        [[nodiscard]] inline std::expected<std::int32_t, FMTResult> get_index_of_current_named_arg(buf::StreamView<TChar>&, std::int32_t)
        {
            return std::unexpected(FMTResult::ArgsInterface_CantMatchNamedArgs);
        }
        [[nodiscard]] inline std::expected<PointerID, FMTResult> get_pointerid_at(std::int32_t)
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
        static inline constexpr std::size_t size() { return sizeof...(Rest) + 1; }

    public:
        template <typename Executor>
        [[nodiscard]] inline std::expected<void, FMTResult> run_type_at(Executor& executor, std::int32_t idx)
        {
            if (idx == 0)
            {
                return executor.write_type(m_Value);
            }
            return FormatterArgs<Rest...>::run_type_at(executor, idx - 1);
        }

    public:
        template <typename TChar>
        [[nodiscard]] inline std::expected<std::int32_t, FMTResult> get_index_of_current_named_arg(buf::StreamView<TChar>& format, std::int32_t beginSearchIndex)
        {
            if constexpr (detail::IsANamedArgs<detail::get_base_type<TypeWithoutRef>>::value)
            {
                bool currentIsANamedArg = SF_TRY(buf::FMTParamsManip(format).next_is_named_args(m_Value.get_name()));
                if (currentIsANamedArg)
                    return beginSearchIndex;
            }
            return FormatterArgs<Rest...>::get_index_of_current_named_arg(format, beginSearchIndex + 1);
        }

    public:
        [[nodiscard]] inline std::expected<PointerID, FMTResult> get_pointerid_at(std::int32_t idx)
        {
            if (idx == 0)
                return PointerID{.type_info = typeid(const TypeWithoutRef), .ptr = const_cast<void*>(static_cast<const void*>(&m_Value))};
            return FormatterArgs<Rest...>::get_pointerid_at(idx - 1);
        }

    public:
        template <typename T>
        [[nodiscard]] inline std::expected<T, FMTResult> GetConvertedTypeAt(std::int32_t idx)
        {
            if (idx == 0)
            {
                if constexpr (FMTCanContextConvert<TypeWithoutRef, T>)
                    { return FMTContextConvert<TypeWithoutRef, T>::convert(m_Value); }
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
            , executor(executor)
            , args_interface(std::forward<Args>(args)...)
        {}
        ~FormatterArgsInterface() override = default;

    public:
        size_t size() override { return args_interface.size(); }

        [[nodiscard]] std::expected<void, FMTResult> run_type_at(std::int32_t idx) override
        {
            return args_interface.run_type_at(executor, idx);
        }
        [[nodiscard]] std::expected<std::int32_t, FMTResult> get_index_of_current_named_arg(buf::StreamView<TChar>& format) override
        {
            return args_interface.get_index_of_current_named_arg(format, std::int32_t{0});
        }
        [[nodiscard]] std::expected<PointerID, FMTResult> get_pointerid_at(std::int32_t idx) override
        {
            return args_interface.get_pointerid_at(idx); 
        }

    public:
        [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> get_string_at(std::int32_t idx) override
        {
            return args_interface.template GetConvertedTypeAt<std::basic_string_view<TChar>>(idx);
        }
        [[nodiscard]] std::expected<std::int64_t, FMTResult> get_int_at(std::int32_t idx) override
        {
            return args_interface.template GetConvertedTypeAt<std::int64_t>(idx);
        }

    protected:
        FormatterExecutor& executor;
        ContextArgsType args_interface;
    };
}
