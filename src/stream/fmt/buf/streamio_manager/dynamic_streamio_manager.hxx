#pragma once

#include "basic_streamio_manager.hxx"

#include <cstring>
#include <iostream>
#include <memory>

namespace stream::fmt::buf {
    template <typename CharType>
    class DynamicStreamIOManager : public BasicStreamIOManager<CharType> {
    public:
        DynamicStreamIOManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE) : buffer_size_(beginSize) {}

        ~DynamicStreamIOManager() override                         = default;
        DynamicStreamIOManager(DynamicStreamIOManager&)            = delete;
        DynamicStreamIOManager& operator=(DynamicStreamIOManager&) = delete;

    public:
        static constexpr std::size_t DEFAULT_BEGIN_SIZE  = 128;
        static constexpr std::size_t GROW_UP_BUFFER_SIZE = 2;
        static constexpr bool        DEBUG_RESIZE        = false;

    public:
        CharType* get_buffer() override {
            return buffer_.get();
        }
        const CharType* get_buffer() const override {
            return buffer_.get();
        }
        std::size_t get_buffer_size() const override {
            if (buffer_ == nullptr) return 0;
            return buffer_size_;
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> begin_context_impl() final {
            if (buffer_ != nullptr) return {};

            CharType* alloc = new CharType[buffer_size_];
            if (alloc == nullptr) return std::unexpected(FMTResult::Manager_AllocationFailed);
            buffer_.reset(alloc);
            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> add_size(const std::size_t count) override {
            return resize(count + buffer_size_);
        }
        [[nodiscard]] std::expected<void, FMTResult> resize(const std::size_t target_buffer_size);

    protected:
        std::unique_ptr<CharType[]> buffer_      = nullptr;
        std::size_t                 buffer_size_ = 0;
    };

    template <typename CharType>
    class ShrinkDynamicStreamIOManager : public DynamicStreamIOManager<CharType> {
    public:
        using Base = DynamicStreamIOManager<CharType>;
        using Base::DEBUG_RESIZE;
        using Base::DEFAULT_BEGIN_SIZE;
        using Base::GROW_UP_BUFFER_SIZE;

        using Base::get_buffer;
        using Base::get_buffer_size;
        using Base::resize;

        using Base::buffer_;
        using Base::buffer_size_;

        static constexpr float MEAN_SIZE_OVERFLOW = 4.2f;
        static constexpr float MEAN_SIZE_RESIZE   = 1.4f;
        static constexpr float MEAN_CALCFACT_OLD  = 5;
        static constexpr float MEAN_CALCFACT_LAST = 1;

    public:
        ShrinkDynamicStreamIOManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE) : Base(beginSize), m_MeanGeneratedSize(beginSize) {}
        ~ShrinkDynamicStreamIOManager() override                               = default;
        ShrinkDynamicStreamIOManager(ShrinkDynamicStreamIOManager&)            = delete;
        ShrinkDynamicStreamIOManager& operator=(ShrinkDynamicStreamIOManager&) = delete;

    protected:
        void compute_generated_size_impl(std::size_t totalGeneratedLength) override {
            // WTF
            m_MeanGeneratedSize = (m_MeanGeneratedSize * MEAN_CALCFACT_OLD + totalGeneratedLength * MEAN_CALCFACT_LAST) / (MEAN_CALCFACT_OLD + MEAN_CALCFACT_LAST);
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> shrink_if_needed() {
            if (buffer_size_ > static_cast<std::size_t>(m_MeanGeneratedSize * MEAN_SIZE_OVERFLOW)) return resize(static_cast<std::size_t>(m_MeanGeneratedSize * MEAN_SIZE_RESIZE));
            return {};
        }

    private:
        std::size_t m_MeanGeneratedSize = 0;
    };

    template <typename CharType>
    [[nodiscard]] std::expected<void, FMTResult> DynamicStreamIOManager<CharType>::resize(const std::size_t target_buffer_size) {
        std::size_t new_buffer_size = target_buffer_size;

        if (buffer_size_ < target_buffer_size) {
            new_buffer_size = buffer_size_;
            while (new_buffer_size < target_buffer_size)
                new_buffer_size *= GROW_UP_BUFFER_SIZE;
        }

        CharType* newBuffer = new CharType[new_buffer_size];
        if (newBuffer == nullptr) return std::unexpected(FMTResult::Manager_AllocationFailed);

        std::memcpy(newBuffer, buffer_.get(), std::min(new_buffer_size, buffer_size_));

        if constexpr (DEBUG_RESIZE) std::cout << "resize from " << buffer_size_ << " to " << new_buffer_size << std::endl;

        buffer_.reset(newBuffer);
        buffer_size_ = new_buffer_size;

        return {};
    }
}  // namespace stream::fmt::buf
