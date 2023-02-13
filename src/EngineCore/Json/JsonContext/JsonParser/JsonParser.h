#pragma once

#include "EngineCore/Json/Detail/Buffer/JsonMemoryBuffer.h"
#include "EngineCore/Json/Detail/Buffer/JsonBufferIn.h"

#include "EngineCore/Json/JsonContext/JsonObjects/JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    class JsonParser
    {
	public:
		explicit JsonParser() : m_BufferIn() {}

		template <std::size_t SIZE>
		explicit JsonParser(const char(&format)[SIZE])                                : m_BufferIn(format, SIZE) {}
		explicit JsonParser(const std::string_view& format)                           : m_BufferIn(format.data(), format.size()) {}
		explicit JsonParser(const char* const buffer, const std::size_t bufferSize)   : m_BufferIn(buffer, bufferSize) {}

	public:
        std::unique_ptr<Detail::JsonObject> LoadJsonObject();

    public:
        JsonBufferIn& BufferIn() { return m_BufferIn; }
        const JsonBufferIn& BufferIn() const { return m_BufferIn; }

    protected:
        JsonBufferIn m_BufferIn;
    };
}
