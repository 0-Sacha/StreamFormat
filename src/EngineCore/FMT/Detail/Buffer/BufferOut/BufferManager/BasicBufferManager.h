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
            virtual std::size_t GetBufferSize() = 0;
        
        public:
            virtual bool Resize(const std::size_t count) = 0;

        public:
            operator std::basic_string_view<CharType>()
            {
                return std::basic_string_view<CharType>(GetBuffer());
            }
    };

}
