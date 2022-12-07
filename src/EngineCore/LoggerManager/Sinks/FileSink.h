#pragma once

#include <ostream>
#include <filesystem>

#include "LoggerManager/Detail/LoggerSink.h"

namespace EngineCore::LoggerManager::Sinks
{
    template <typename CharType>
    class BasicConsoleSink : Detail::BasicLoggerSink<CharType>
    {
        public:
            BasicConsoleSink(std::basic_ostream<CharType>& stream)
                : m_Stream(stream)
            {}

        public:
            std::basic_ostream<CharType>& GetStream() { return m_Stream; }
        
        public:
            void PrintToSink(const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint) override
            {
                m_Stream.write(static_cast<std::basic_string_view<CharType>>(bufferToPrint));
                m_Stream.write("\n");
            }

        private:
            std::basic_ostream<CharType>& m_Stream;
    };

    template <typename CharType>
    class BasicFileSink : Detail::BasicLoggerSink<CharType>
    {
        public:
            BasicFileSink(const std::filesystem::path& filePath)
                : m_Stream(filePath)
            {}

        public:
            std::basic_ostream<CharType>& GetStream() { return m_Stream; }
        
        public:
            void PrintToSink(const FMT::Detail::BasicFormatterMemoryBufferOutCopy<CharType>& bufferToPrint) override
            {
                m_Stream.write(static_cast<std::basic_string_view<CharType>>(bufferToPrint));
                m_Stream.write("\n");
            }

        private:
            std::basic_ostream<CharType> m_Stream;
    };
}

namespace EngineCore::LoggerManager::Sinks
{
    using ConsoleSink = BasicConsoleSink<char>;
    using FileSink = BasicFileSink<char>;
}
