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

    template <typename CharType>
    class ContextExecutor {
    public:
        using TChar = CharType;

    public:
        ContextExecutor(detail::ITextPropertiesExecutor& text_properties_executor) : data{}, text_manager{text_properties_executor} {}
        virtual ~ContextExecutor() = default;

    public:
        virtual void exec_settings()                                = 0;
        virtual void exec_raw_string(std::basic_string_view<TChar>) = 0;

        BasicContext<TChar>& get_context() { return *reinterpret_cast<BasicContext<TChar>*>(context); }

    public:
        detail::FormatData<TChar>            data;
        detail::TextPropertiesManager<TChar> text_manager;

        void* context = nullptr;
    };

    template <typename CharType>
    class BasicContext {
    public:
        using TChar = CharType;

    public:
        BasicContext(ContextExecutor<TChar>& executor, buf::StreamView<TChar> fmtstream, detail::BasicArgsInterface<TChar>& args_interface);
        virtual ~BasicContext();

    public:
        ContextExecutor<TChar>& executor;

        buf::StreamView<TChar>             fmtstream;
        detail::BasicArgsInterface<TChar>& args_interface;
        std::int32_t                       values_index;

    private:
        void* old_context_attached = nullptr;

    public:
        void run();

    protected:
        void parse_variable(std::int32_t format_idx);
        void parse();
    };
}  // namespace stream::fmt::context

namespace stream::fmt::context {
    template <typename TChar>
    BasicContext<TChar>::BasicContext(ContextExecutor<TChar>& executor, buf::StreamView<TChar> format, detail::BasicArgsInterface<TChar>& args_interface)
        : executor(executor), fmtstream{format}, args_interface{args_interface}, values_index{0} {
            old_context_attached = executor.context;
            executor.context = this;
        }

    template <typename TChar>
    BasicContext<TChar>::~BasicContext()
    {
        executor.context = old_context_attached;
    }

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
}  // namespace stream::fmt::context

#include "basic_context_parse_impl.hxx"
