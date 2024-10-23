#pragma once

#include "StreamFormat/FMT/Detail/Detail.h"
#include "StreamFormat/FMT/Buffer/BufferInfo.h"

namespace StreamFormat::FMT::Detail
{
    template <typename CharType>
    class BasicBufferOutManager
    {
    public:
        virtual ~BasicBufferOutManager() = default;

    protected:
        virtual void BeginContextImpl() {}
        virtual void ComputeGeneratedSizeImpl(const std::size_t /* totalGeneratedLength */) {}

    public:
        void BeginContext() { BeginContextImpl(); }
        void ComputeGeneratedSize(std::size_t totalGeneratedLength)
        {
            ComputeGeneratedSizeImpl(totalGeneratedLength);
            SetLastGeneratedDataSize(totalGeneratedLength);
        }

    public:
        virtual CharType*       GetBuffer()           = 0;
        virtual const CharType* GetBuffer() const     = 0;
        virtual std::size_t     GetBufferSize() const = 0;

    public:
        virtual bool AddSize(const std::size_t count) = 0;

    public:
        BufferInfoView<CharType> GetLastGeneratedBufferInfoView() const { return BufferInfoView<CharType>(GetBuffer(), m_LastGeneratedDataSize); }
        operator BufferInfoView<CharType>() const { return GetLastGeneratedBufferInfoView(); }

        std::basic_string_view<CharType> GetLastGeneratedStringView() const { return std::basic_string_view<CharType>(GetBuffer(), m_LastGeneratedDataSize); }
        operator std::basic_string_view<CharType>() const { return GetLastGeneratedStringView(); }
        std::basic_string<CharType> GetLastGeneratedString() const { return std::basic_string<CharType>(GetBuffer(), m_LastGeneratedDataSize); }
        operator std::basic_string<CharType>() const { return GetLastGeneratedString(); }

    public:
        std::size_t GetLastGeneratedDataSize() const { return m_LastGeneratedDataSize; }

    private:
        void SetLastGeneratedDataSize(const std::size_t size) { m_LastGeneratedDataSize = size; }

    protected:
        std::size_t m_LastGeneratedDataSize{0};
    };
}
