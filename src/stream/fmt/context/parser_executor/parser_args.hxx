#pragma once

#include "stream/fmt/context/basic_context/basic_args_interface.h"
#include "stream/fmt/detail/prelude.h"

namespace stream::fmt::detail {
    /****************************/
    /******** Args tuple ********/
    /****************************/
    template <typename... Types>
    struct ParserArgs;

    template <>
    struct ParserArgs<> {
    public:
        ParserArgs() = default;

    public:
        static inline constexpr std::size_t size() {
            return 0;
        }

    public:
        template <typename FormatterExecutor>
        [[nodiscard]] inline std::expected<void, FMTResult> run_type_at(FormatterExecutor&, std::int32_t) {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
        template <typename TChar>
        [[nodiscard]] inline std::expected<std::int32_t, FMTResult> get_index_of_current_named_arg(buf::StreamView<TChar>& format, std::int32_t) {
            return std::unexpected(FMTResult::ArgsInterface_CantMatchNamedArgs);
        }
        [[nodiscard]] inline std::expected<PointerID, FMTResult> get_pointerid_at(std::int32_t) {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
        template <typename T>
        [[nodiscard]] inline std::expected<T, FMTResult> get_converted_type_at(std::int32_t) {
            return std::unexpected(FMTResult::ArgsInterface_IndexOutOfBounds);
        }
    };

    template <typename Type, typename... Rest>
    struct ParserArgs<Type, Rest...> : ParserArgs<Rest...> {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        ParserArgs(TypeWithoutRef& t, Rest&... rest) : ParserArgs<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}

    private:
        TypeWithoutRef& m_Value;

    public:
        static inline constexpr std::size_t size() {
            return sizeof...(Rest) + 1;
        }

    public:
        template <typename Executor>
        [[nodiscard]] inline std::expected<void, FMTResult> run_type_at(Executor& executor, std::int32_t idx) {
            if (idx == 0) {
                return executor.read_type(m_Value);
            }
            return ParserArgs<Rest...>::run_type_at(executor, idx - 1);
        }

    public:
        template <typename TChar>
        [[nodiscard]] inline std::expected<std::int32_t, FMTResult> get_index_of_current_named_arg(buf::StreamView<TChar>& format, std::int32_t begin_search_index) {
            if constexpr (detail::IsANamedArgs<detail::get_base_type<TypeWithoutRef>>::value) {
                bool current_is_a_named_arg = SF_TRY(buf::FMTParamsManip(format).next_is_named_args(m_Value.get_name()));
                if (current_is_a_named_arg) return begin_search_index;
            }
            return ParserArgs<Rest...>::get_index_of_current_named_arg(format, begin_search_index + 1);
        }

    public:
        [[nodiscard]] inline std::expected<PointerID, FMTResult> get_pointerid_at(std::int32_t idx) {
            if (idx == 0) return PointerID{.type_info = typeid(TypeWithoutRef), .ptr = static_cast<void*>(&m_Value)};
            return ParserArgs<Rest...>::get_pointerid_at(idx - 1);
        }

    public:
        template <typename T>
        [[nodiscard]] inline std::expected<T, FMTResult> get_converted_type_at(std::int32_t idx) {
            if (idx == 0) {
                if constexpr (FMTCanContextConvert<TypeWithoutRef, T>) {
                    return FMTContextConvert<TypeWithoutRef, T>::convert(m_Value);
                } else {
                    return std::unexpected(FMTResult::ArgsInterface_InvalidConversion);
                }
            }
            return ParserArgs<Rest...>::template get_converted_type_at<T>(idx - 1);
        }
    };


    /********************************/
    /******** Args interface ********/
    /********************************/
    template <typename TChar, typename ParserExecutor, typename... Args>
    class ParserArgsInterface : public BasicArgsInterface<TChar> {
    public:
        using ContextArgsType = ParserArgs<Args...>;

    public:
        ParserArgsInterface(ParserExecutor& executor, Args&&... args) : BasicArgsInterface<TChar>(), executor(executor), args_interface(std::forward<Args>(args)...) {}
        ~ParserArgsInterface() override = default;

    public:
        std::size_t size() override {
            return args_interface.size();
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> run_type_at(std::int32_t idx) override {
            return args_interface.run_type_at(executor, idx);
        }
        [[nodiscard]] std::expected<std::int32_t, FMTResult> get_index_of_current_named_arg(buf::StreamView<TChar>& format) override {
            return args_interface.get_index_of_current_named_arg(format, std::int32_t{0});
        }
        [[nodiscard]] inline std::expected<PointerID, FMTResult> get_pointerid_at(std::int32_t idx) override {
            return args_interface.get_pointerid_at(idx);
        }

    public:
        [[nodiscard]] std::expected<typename std::basic_string_view<TChar>, FMTResult> get_string_at(std::int32_t idx) override {
            return args_interface.template get_converted_type_at<typename std::basic_string_view<TChar>>(idx);
        }
        [[nodiscard]] std::expected<std::int64_t, FMTResult> get_int_at(std::int32_t idx) override {
            return args_interface.template get_converted_type_at<std::int64_t>(idx);
        }

    protected:
        ParserExecutor& executor;
        ContextArgsType args_interface;
    };
}  // namespace stream::fmt::detail
