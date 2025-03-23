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
        [[nodiscard]] virtual std::expected<void, FMTResult> exec_settings()                                = 0;
        [[nodiscard]] virtual std::expected<void, FMTResult> exec_raw_string(std::basic_string_view<TChar>) = 0;

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
        [[nodiscard]] std::expected<void, FMTResult> run();

    private:
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex_Number();
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex_Name();
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex_SubIndex();

    public:
        [[nodiscard]] std::expected<std::int32_t, FMTResult> GetFormatIndex();
        template <typename T>
        [[nodiscard]] std::expected<T, FMTResult> format_read_parameter(const T& default_value);

    protected:
        void formatdata_apply_next_override();

    protected:
        [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> parse_next_override_format_data();

        [[nodiscard]] std::expected<void, FMTResult> parse_format_data_base();
        [[nodiscard]] std::expected<void, FMTResult> parse_format_dataSpecial();
        [[nodiscard]] std::expected<void, FMTResult> parse_format_dataSpecial_ShiftType(const detail::ShiftInfo::ShiftType type);
        [[nodiscard]] std::expected<void, FMTResult> parse_format_dataCustom();
        [[nodiscard]] std::expected<void, FMTResult> parse_format_data();

        [[nodiscard]] std::expected<void, FMTResult> ParseVariable(std::int32_t formatIdx);
        [[nodiscard]] std::expected<void, FMTResult> parse();

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
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::run() {
        while (!buf::Access(fmtstream).is_end_of_string()) {
            const TChar* begin_continuous_string = fmtstream.current_pos;
            std::size_t  size_continuous_string  = 0;
            while (buf::Access(fmtstream).is_end_of_string() == false && buf::TestAccess(fmtstream).is_equal_to('{') == false) {
                ++size_continuous_string;
                SF_TRY(buf::Manip(fmtstream).forward());
            }
            SF_TRY(executor.exec_raw_string(std::basic_string_view<TChar>(begin_continuous_string, size_continuous_string)));

            if (buf::Access(fmtstream).is_end_of_string() == false && buf::TestAccess(fmtstream).is_equal_to('{')) {
                SF_TRY(parse());
            }
        }

        return {};
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
    [[nodiscard]] std::expected<T, FMTResult> BasicContext<TChar>::format_read_parameter(const T& default_value) {
        if (!buf::TestAccess(fmtstream).is_equal_to('{')) {
            T t;
            SF_TRY(buf::ReadManip(fmtstream).fast_read_integer(t));
            return t;
        }

        // SubIndex
        SF_TRY(buf::TestManip(fmtstream).skip_one_of('}'));
        std::int32_t formatIdx = SF_TRY(GetFormatIndex());
        if constexpr (std::is_convertible_v<T, int64_t>)
            return args_interface.get_int_at(formatIdx);
        else if constexpr (std::is_convertible_v<T, std::basic_string_view<TChar>>)
            return args_interface.get_string_at(formatIdx);

        return std::unexpected(FMTResult::Context_ArgumentIndexExpected);
    }
}  // namespace stream::fmt::context

#include "basic_context_parse_impl.hxx"
