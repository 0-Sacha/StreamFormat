#pragma once

#include <ostream>
#include <fstream>
#include <filesystem>

#include "LoggerManager/Detail/LoggerSink.h"

namespace EngineCore::LoggerManager::Sinks
{
    template <typename Severity, typename CharType>
    class BasicConsoleSink : public Detail::BasicLoggerSink<Severity, CharType>
    {
        public:
            using Base = Detail::BasicLoggerSink<Severity, CharType>;
            using typename Base::PatternType;
            using typename Base::NameType;
            using typename Base::BufferType;

        public:
            BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name)
                : Base(std::forward<NameType>(name))
                , m_Stream(stream)
            {}

            BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name, Detail::AsyncSink isAsync)
                : Base(std::forward<NameType>(name), isAsync)
                , m_Stream(stream)
            {}

        public:
            std::basic_ostream<CharType>& GetStream() { return m_Stream; }
        
        protected:
            void WriteImpl(const BufferType& bufferToPrint) override
            {
                m_Stream.write(bufferToPrint.data(), bufferToPrint.size());
                m_Stream.write("\n", 1);
                m_Stream.flush();
            }
            
        private:
            std::basic_ostream<CharType>& m_Stream;
    };

    template <typename Severity, typename CharType>
    class BasicFileSink : public Detail::BasicLoggerSink<Severity, CharType>
    {
        public:
            using Base = Detail::BasicLoggerSink<Severity, CharType>;
            using typename Base::PatternType;
            using typename Base::NameType;
            using typename Base::BufferType;

        public:
            BasicFileSink(const std::filesystem::path& filePath, NameType&& name, Detail::AsyncSink isAsync)
                : Base(std::forward<NameType>(name), isAsync)
                , m_Stream(filePath, std::ios::out)
            {}

        public:
            std::basic_ostream<CharType>& GetStream() { return m_Stream; }
        
        protected:
            void WriteImpl(const BufferType& bufferToPrint) override
            {
                m_Stream.write(bufferToPrint.data(), bufferToPrint.size());
                m_Stream.write("\n", 1);
                m_Stream.flush();
            }

        private:
            std::basic_ofstream<CharType> m_Stream;
    };
}

namespace EngineCore::LoggerManager::Sinks::Severity
{
    template<typename Severity>
    using ConsoleSink = BasicConsoleSink<Severity, char>;
    template<typename Severity>
    using FileSink = BasicFileSink<Severity, char>;
}
