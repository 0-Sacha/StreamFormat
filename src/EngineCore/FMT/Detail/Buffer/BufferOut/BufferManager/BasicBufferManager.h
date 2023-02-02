#pragma once

#include "FMT/Detail/Detail.h"

namespace EngineCore::FMT::Detail {

    template <typename CharType>
    class BasicBufferManager
    {
        public:
            virtual void BeginContext() = 0;
            virtual void EndContext() = 0;

        public:
            virtual CharType* GetBuffer() = 0;
            virtual const CharType* GetBuffer() const = 0;
            virtual std::size_t GetBufferSize() const = 0;
        
        public:
            virtual bool Resize(const std::size_t count) = 0;

        public:
            std::basic_string_view<CharType> GetLastGeneratedString() const { return std::basic_string_view<CharType>(GetBuffer(), m_LastGeneratedDataSize); }
            operator std::basic_string_view<CharType>() const
            {
                return GetLastGeneratedString();
            }

        public:
            std::size_t GetLastGeneratedDataSize() const { return m_LastGeneratedDataSize; }
            void SetLastGeneratedDataSize(const std::size_t size) { m_LastGeneratedDataSize = size; }

        protected:
            std::size_t m_LastGeneratedDataSize;
    };

}
