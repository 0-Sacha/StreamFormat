#pragma once

#include "logger_sink.h"

#include <filesystem>
#include <fstream>
#include <ostream>

namespace stream::flog::Sinks {
    template <typename Severity, typename CharType>
    class BasicConsoleSink : public detail::BasicLoggerSink<Severity, CharType> {
    public:
        using Base = detail::BasicLoggerSink<Severity, CharType>;
        using typename Base::BufferType;
        using typename Base::NameType;
        using typename Base::PatternType;

    public:
        BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name) : Base(std::forward<NameType>(name)), m_Stream(stream) {}

        BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name, detail::AsyncSink isAsync) : Base(std::forward<NameType>(name), isAsync), m_Stream(stream) {}

        ~BasicConsoleSink() override = default;

    public:
        std::basic_ostream<CharType>& GetStream() {
            return m_Stream;
        }

    protected:
        void WriteImpl(const BufferType& bufferToPrint) override {
            m_Stream.write(bufferToPrint.data(), bufferToPrint.size());
            m_Stream.write("\n", 1);
            m_Stream.flush();
        }

    private:
        std::basic_ostream<CharType>& m_Stream;
    };

    template <typename Severity, typename CharType>
    class BasicFileSink : public detail::BasicLoggerSink<Severity, CharType> {
    public:
        using Base = detail::BasicLoggerSink<Severity, CharType>;
        using typename Base::BufferType;
        using typename Base::NameType;
        using typename Base::PatternType;

    public:
        BasicFileSink(const std::filesystem::path& filePath, NameType&& name, detail::AsyncSink isAsync)
            : Base(std::forward<NameType>(name), isAsync), m_Stream(filePath, std::ios::out) {}

        ~BasicFileSink() override = default;

    public:
        std::basic_ostream<CharType>& GetStream() {
            return m_Stream;
        }

    protected:
        void WriteImpl(const BufferType& bufferToPrint) override {
            m_Stream.write(bufferToPrint.data(), bufferToPrint.size());
            m_Stream.write("\n", 1);
            m_Stream.flush();
        }

    private:
        std::basic_ofstream<CharType> m_Stream;
    };
}  // namespace stream::flog::Sinks
