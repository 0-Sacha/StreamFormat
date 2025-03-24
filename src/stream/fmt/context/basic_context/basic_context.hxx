#pragma once

#include "stream/fmt/detail/convert_traits.hxx"
#include "stream/fmt/detail/prelude.hxx"
#include "stream/fmt/detail/specifiers.hxx"

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"

#include "basic_args_interface.hxx"

#include "text_properties_executor.hxx"
#include "text_properties_manager.hxx"

namespace stream::fmt::context {
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class context_executor {
    public:
        context_executor(detail::ITextPropertiesExecutor& text_properties_executor) : data{}, text_manager{text_properties_executor} {}
        virtual ~context_executor() = default;

    public:
        virtual void exec_settings()                                = 0;
        virtual void exec_raw_string(std::basic_string_view<TChar>) = 0;

    public:
        detail::FormatData<TChar>            data;
        detail::TextPropertiesManager<TChar> text_manager;
    };

    template <typename CharType>
    class BasicContext {
    public:
        using TChar = CharType;

    public:
        BasicContext(context_executor<TChar>& executor, buf::StreamView<TChar> fmtstream, detail::BasicArgsInterface<TChar>& args_interface);
        virtual ~BasicContext() = default;

    public:
        context_executor<TChar>& executor;

        buf::StreamView<TChar>             fmtstream;
        detail::BasicArgsInterface<TChar>& args_interface;
        std::int32_t                       values_index;

    public:
        void run();

    private:
        std::optional<std::int32_t> get_format_index_number();
        std::optional<std::int32_t> get_format_index_name();
        std::optional<std::int32_t> get_format_index_sub_index();

    public:
        std::optional<std::int32_t> get_format_index();
        template <typename T>
        T format_read_parameter(const T& default_value);

    protected:
        void formatdata_apply_next_override();

    protected:
        std::basic_string_view<TChar> parse_next_override_format_data();

        void parse_format_data_base();
        void parse_format_data_special();
        void parse_format_data_special_shift_type(const detail::ShiftInfo::ShiftType type);
        void parse_format_dataCustom();
        void parse_format_data();

        void parse_variable(std::int32_t format_idx);
        void parse();

    public:
        template <typename Func, typename... Args>
        inline void ExecNextFormatData(Func&& func, Args&&... args) {
            if (executor.data.next_override.size() == 0) return func(std::forward<Args>(args)...);
            detail::FormatData<TChar> format_data_copy = executor.data;
            formatdata_apply_next_override();
            func(std::forward<Args>(args)...);
            executor.data = format_data_copy;
        }
    };
}  // namespace stream::fmt::context

namespace stream::fmt::context {
    template <typename TChar>
    BasicContext<TChar>::BasicContext(context_executor<TChar>& executor, buf::StreamView<TChar> format, detail::BasicArgsInterface<TChar>& args_interface)
        : executor(executor), fmtstream{format}, args_interface{args_interface}, values_index{0} {}

    template <typename TChar>
    void BasicContext<TChar>::run() {
        while (!fmtstream.is_end_of_string()) {
            const TChar* begin_continuous_string = fmtstream.current_pos;
            std::size_t  size_continuous_string  = 0;
            while (fmtstream.is_end_of_string() == false && buf::TestAccess(fmtstream).is_equal_to('{') == false) {
                ++size_continuous_string;
                buf::Manip(fmtstream).forward();
            }
            executor.exec_raw_string(std::basic_string_view<TChar>(begin_continuous_string, size_continuous_string));

            if (fmtstream.is_end_of_string() == false && buf::TestAccess(fmtstream).is_equal_to('{')) {
                parse();
            }
        }
    }

    template <typename TChar>
    void BasicContext<TChar>::formatdata_apply_next_override() {
        if (executor.data.next_override.size() == 0) {
            return;
        }

        buf::StreamView<TChar> overridePos(executor.data.next_override);
        buf::StreamView<TChar> format_pos = fmtstream;
        fmtstream                         = overridePos;
        parse_format_data();
        fmtstream = format_pos;
    }

    template <typename TChar>
    template <typename T>
    T BasicContext<TChar>::format_read_parameter(const T& default_value) {
        if (!buf::TestAccess(fmtstream).is_equal_to('{')) {
            T t;
            buf::ReadManip(fmtstream).fast_read_integer(t);
            return t;
        }

        // SubIndex
        buf::TestManip(fmtstream).skip_one_of('{');
        std::optional<std::int32_t> format_idx = get_format_index();
        if constexpr (std::is_convertible_v<T, int64_t>)
            return args_interface.get_int_at(format_idx.value());
        else if constexpr (std::is_convertible_v<T, std::basic_string_view<TChar>>)
            return args_interface.get_string_at(format_idx.value());

        throw std::runtime_error("fmt error: Context_ArgumentIndexExpected");
    }
}  // namespace stream::fmt::context

#include "basic_context_parse_impl.hxx"
