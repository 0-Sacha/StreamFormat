#pragma once

#include "stream/fmt/detail/prelude.hxx"
#include "stream/fmt/buf/stream.hxx"

namespace stream::fmt::buf {
    template <typename CharType>
    class BasicStreamIOManager {
    public:
        BasicStreamIOManager()                                 = default;
        virtual ~BasicStreamIOManager()                        = default;
        BasicStreamIOManager(BasicStreamIOManager&)            = delete;
        BasicStreamIOManager& operator=(BasicStreamIOManager&) = delete;

    protected:
        [[nodiscard]] virtual std::expected<void, FMTResult> begin_context_impl() {
            return {};
        }
        virtual void compute_generated_size_impl(const std::size_t /* totalGeneratedLength */) {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> BeginContext() {
            return begin_context_impl();
        }
        void compute_generated_size(std::size_t totalGeneratedLength) {
            compute_generated_size_impl(totalGeneratedLength);
            set_last_generated_data_size(totalGeneratedLength);
        }

    public:
        virtual CharType*       get_buffer()            = 0;
        virtual const CharType* get_buffer() const      = 0;
        virtual std::size_t     get_buffer_size() const = 0;

    public:
        [[nodiscard]] virtual std::expected<void, FMTResult> add_size(const std::size_t count) = 0;

    public:
        StreamView<CharType> get_last_generated_buffer_info_view() const {
            return StreamView<CharType>(get_buffer(), m_LastGeneratedDataSize);
        }
        operator StreamView<CharType>() const {
            return get_last_generated_buffer_info_view();
        }
        std::basic_string_view<CharType> get_last_generated_string_view() const {
            return std::basic_string_view<CharType>(get_buffer(), m_LastGeneratedDataSize);
        }
        operator std::basic_string_view<CharType>() const {
            return get_last_generated_string_view();
        }

    public:
        std::size_t get_last_generated_data_size() const {
            return m_LastGeneratedDataSize;
        }

    private:
        void set_last_generated_data_size(const std::size_t size) {
            m_LastGeneratedDataSize = size;
        }

    protected:
        std::size_t m_LastGeneratedDataSize{0};
    };
}  // namespace stream::fmt::buf
