#pragma once

#include "basic_streamio_manager.h"

namespace stream::fmt::buf {
    template <typename CharType>
    class GivenStreamIOManager : public BasicStreamIOManager<CharType> {
    public:
        template <std::size_t SIZE>
        GivenStreamIOManager(CharType (&buffer)[SIZE]) : buffer_(buffer), buffer_size_(SIZE) {}

        GivenStreamIOManager(CharType* buffer, std::size_t buffer_size) : buffer_(buffer), buffer_size_(buffer_size) {}

        ~GivenStreamIOManager() override = default;

        GivenStreamIOManager(GivenStreamIOManager&)            = delete;
        GivenStreamIOManager& operator=(GivenStreamIOManager&) = delete;

    public:
        CharType* get_buffer() override {
            return buffer_;
        }
        const CharType* get_buffer() const override {
            return buffer_;
        }
        std::size_t get_buffer_size() const override {
            return buffer_size_;
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> add_size(const std::size_t /* count */) override {
            return std::unexpected(FMTResult::Manager_StaticMemory);
        }

    private:
        CharType*   buffer_;
        std::size_t buffer_size_;
    };
}  // namespace stream::fmt::buf
