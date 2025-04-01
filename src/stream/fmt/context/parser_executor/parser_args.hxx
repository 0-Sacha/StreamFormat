#pragma once

#include "stream/fmt/context/basic_context/basic_args_interface.hxx"
#include "stream/fmt/detail/prelude.hxx"
#include "stream/fmt/context/formatter_executor/named_args.hxx"

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
        void run_type_at(FormatterExecutor&, std::int32_t) {
            throw std::runtime_error("fmt error: ArgsInterface_IndexOutOfBounds");
        }
        template <typename TChar>
        inline std::optional<std::int32_t> get_index_of_current_named_arg(buf::StreamView<TChar>& format, std::int32_t) {
            return std::nullopt;
        }
        inline PointerID get_pointerid_at(std::int32_t) {
            throw std::runtime_error("fmt error: ArgsInterface_IndexOutOfBounds");
        }
        template <typename T>
        inline T get_converted_type_at(std::int32_t) {
            throw std::runtime_error("fmt error: ArgsInterface_IndexOutOfBounds");
        }
    };

    template <typename Type, typename... Rest>
    struct ParserArgs<Type, Rest...> : ParserArgs<Rest...> {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        ParserArgs(TypeWithoutRef& t, Rest&... rest) : ParserArgs<Rest...>(std::forward<Rest>(rest)...), value_(t) {}

    private:
        TypeWithoutRef& value_;

    public:
        static inline constexpr std::size_t size() {
            return sizeof...(Rest) + 1;
        }

    public:
        template <typename Executor>
        void run_type_at(Executor& executor, std::int32_t idx) {
            if (idx == 0) {
                return executor.read_type(value_);
            }
            return ParserArgs<Rest...>::run_type_at(executor, idx - 1);
        }

    public:
        template <typename TChar>
        inline std::optional<std::int32_t> get_index_of_current_named_arg(buf::StreamView<TChar>& format, std::int32_t begin_search_index) {
            if constexpr (detail::IsANamedArgs<detail::get_base_type<TypeWithoutRef>>::value) {
                bool current_is_a_named_arg = buf::FMTParamsManip(format).next_is_named_args(value_.get_name());
                if (current_is_a_named_arg) return begin_search_index;
            }
            return ParserArgs<Rest...>::get_index_of_current_named_arg(format, begin_search_index + 1);
        }

    public:
        inline PointerID get_pointerid_at(std::int32_t idx) {
            if (idx == 0) return PointerID{.type_info = typeid(TypeWithoutRef), .ptr = static_cast<void*>(&value_)};
            return ParserArgs<Rest...>::get_pointerid_at(idx - 1);
        }

    public:
        template <typename T>
        inline T get_converted_type_at(std::int32_t idx) {
            if (idx == 0) {
                if constexpr (FMTCanContextConvert<TypeWithoutRef, T>) {
                    return FMTContextConvert<TypeWithoutRef, T>::convert(value_);
                } else {
                    throw std::runtime_error("fmt error: ArgsInterface_InvalidConversion");
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
        void run_type_at(std::int32_t idx) override {
            return args_interface.run_type_at(executor, idx);
        }
        std::optional<std::int32_t> get_index_of_current_named_arg(buf::StreamView<TChar>& format) override {
            return args_interface.get_index_of_current_named_arg(format, std::int32_t{0});
        }
        inline PointerID get_pointerid_at(std::int32_t idx) override {
            return args_interface.get_pointerid_at(idx);
        }

    public:
        typename std::basic_string_view<TChar> get_string_at(std::int32_t idx) override {
            return args_interface.template get_converted_type_at<typename std::basic_string_view<TChar>>(idx);
        }
        std::int64_t get_int_at(std::int32_t idx) override {
            return args_interface.template get_converted_type_at<std::int64_t>(idx);
        }

    protected:
        ParserExecutor& executor;
        ContextArgsType args_interface;
    };
}  // namespace stream::fmt::detail
