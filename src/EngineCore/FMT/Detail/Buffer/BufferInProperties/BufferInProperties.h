#pragma once

#include "EngineCore/FMT/Detail/Detail.h"

namespace EngineCore::FMT::Detail {

	template <typename CharType>
    class BufferInProperties
    {
	public:
		template <std::size_t SIZE>
		BufferInProperties(const CharType (&format)[SIZE]) 								: m_Buffer(format), m_BufferSize(SIZE) {}
		BufferInProperties(const std::basic_string_view<CharType>& format) 				: m_Buffer(format.data()), m_BufferSize(format.size()) {}
		BufferInProperties(const std::basic_string<CharType>& format) 					: m_Buffer(format.data()), m_BufferSize(format.size()) {}
 		BufferInProperties(const CharType* const buffer, const std::size_t bufferSize) 	: m_Buffer(buffer), m_BufferSize(bufferSize) {}

	public:
		const CharType* GetBuffer() const { return m_Buffer; }
		std::size_t GetBufferSize() const { return m_BufferSize; }
	
	public:
		const CharType* const m_Buffer;
		const std::size_t m_BufferSize;
    };

}
