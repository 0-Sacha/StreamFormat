
#pragma once

#include "stream/fmt/context/basic_context/basic_args_interface.hxx"
#include "stream/fmt/detail/prelude.hxx"

#include "formatter_type.hxx"

namespace stream::fmt::detail {
    /****************************/
    /******** Args tuple ********/
    /****************************/
    template <typename... Types>
    struct FormatterArgs;

    template <>
    struct FormatterArgs<> {
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
        inline std::optional<std::int32_t> get_index_of_current_named_arg(buf::StreamView<TChar>& stream, std::int32_t) {
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
    struct FormatterArgs<Type, Rest...> : public FormatterArgs<Rest...> {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        FormatterArgs(const TypeWithoutRef& t, Rest&&... rest) : FormatterArgs<Rest...>(std::forward<Rest>(rest)...), value_(t) {}

    private:
        const TypeWithoutRef& value_;

    public:
        static inline constexpr std::size_t size() {
            return sizeof...(Rest) + 1;
        }

    public:
        template <typename Executor>
        void run_type_at(Executor& executor, std::int32_t idx) {
            if (idx == 0) {
                return executor.write_type(value_);
            }
            return FormatterArgs<Rest...>::run_type_at(executor, idx - 1);
        }

    public:
        template <typename TChar>
        inline std::optional<std::int32_t> get_index_of_current_named_arg(buf::StreamView<TChar>& format, std::int32_t begin_search_index) {
            if constexpr (detail::IsANamedArgs<detail::get_base_type<TypeWithoutRef>>::value) {
                bool current_is_a_named_arg = buf::FMTParamsManip(format).next_is_named_args(value_.get_name());
                if (current_is_a_named_arg) return begin_search_index;
            }
            return FormatterArgs<Rest...>::get_index_of_current_named_arg(format, begin_search_index + 1);
        }

    public:
        inline PointerID get_pointerid_at(std::int32_t idx) {
            if (idx == 0) return PointerID{.type_info = typeid(const TypeWithoutRef), .ptr = const_cast<void*>(static_cast<const void*>(&value_))};
            return FormatterArgs<Rest...>::get_pointerid_at(idx - 1);
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
            return FormatterArgs<Rest...>::template get_converted_type_at<T>(idx - 1);
        }
    };


    /********************************/
    /******** Args interface ********/
    /********************************/
    template <typename TChar, typename FormatterExecutor, typename... Args>
    class FormatterArgsInterface : public BasicArgsInterface<TChar> {
    public:
        using ContextArgsType = FormatterArgs<Args...>;

    public:
        FormatterArgsInterface(FormatterExecutor& executor, Args&&... args) : BasicArgsInterface<TChar>(), executor(executor), args_interface(std::forward<Args>(args)...) {}
        ~FormatterArgsInterface() override = default;

    public:
        size_t size() override {
            return args_interface.size();
        }

        void run_type_at(std::int32_t idx) override {
            return args_interface.run_type_at(executor, idx);
        }
        std::optional<std::int32_t> get_index_of_current_named_arg(buf::StreamView<TChar>& format) override {
            return args_interface.get_index_of_current_named_arg(format, std::int32_t{0});
        }
        PointerID get_pointerid_at(std::int32_t idx) override {
            return args_interface.get_pointerid_at(idx);
        }

    public:
        std::basic_string_view<TChar> get_string_at(std::int32_t idx) override {
            return args_interface.template get_converted_type_at<std::basic_string_view<TChar>>(idx);
        }
        std::int64_t get_int_at(std::int32_t idx) override {
            return args_interface.template get_converted_type_at<std::int64_t>(idx);
        }

    protected:
        FormatterExecutor& executor;
        ContextArgsType    args_interface;
    };
}  // namespace stream::fmt::detail
