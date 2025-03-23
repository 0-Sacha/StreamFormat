#pragma once

#include "basic_streamio_manager.h"

namespace stream::fmt::buf {
    template <typename CharType, std::size_t Count>
    class StaticStreamIOManager : public BasicStreamIOManager<CharType> {
    public:
        ~StaticStreamIOManager() override                        = default;
        StaticStreamIOManager(StaticStreamIOManager&)            = delete;
        StaticStreamIOManager& operator=(StaticStreamIOManager&) = delete;

    public:
        CharType* get_buffer() override {
            return buffer_;
        }
        const CharType* get_buffer() const override {
            return buffer_;
        }
        std::size_t get_buffer_size() const override {
            return Count;
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> add_size(const std::size_t) override {
            return std::unexpected(FMTResult::Manager_StaticMemory);
        }

    private:
        CharType buffer_[Count];
    };
}  // namespace stream::fmt::buf
