#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferIn/BasicBufferIn.h"

#include "JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    class JsonParser
    {
    public:
        using JsonBufferIn = EngineCore::FMT::Detail::BasicBufferIn<char>;

	public:
		explicit JsonParser() : m_BufferIn() {}

		template <std::size_t SIZE>
		explicit JsonParser(const char(&format)[SIZE])                                : m_BufferIn(format, SIZE) {}
		explicit JsonParser(const std::string_view& format)                           : m_BufferIn(format.data(), format.size()) {}
		explicit JsonParser(const char* const buffer, const std::size_t bufferSize)   : m_BufferIn(buffer, bufferSize) {}

    public:
        inline bool IsJsonStringBegin() const		{ return m_BufferIn.IsEqualTo('"'); }
        inline bool IsJsonNumberBegin() const		{ return m_BufferIn.IsADigit() || m_BufferIn.IsEqualTo('.'); }
        inline bool IsJsonBooleanBegin() const		{ return m_BufferIn.IsEqualTo('t', 'f'); }
        inline bool IsJsonStructBegin() const		{ return m_BufferIn.IsEqualTo('{'); }
        inline bool IsJsonArrayBegin() const		{ return m_BufferIn.IsEqualTo('['); }
        inline bool IsJsonNullBegin() const			{ return m_BufferIn.IsEqualTo('n'); }

    public:
        JsonBufferIn& BufferIn() { return m_BufferIn; }
        const JsonBufferIn& BufferIn() const { return m_BufferIn; }

    protected:
        JsonBufferIn m_BufferIn;
    };
}
