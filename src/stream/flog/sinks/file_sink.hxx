#pragma once

#include "logger_sink.hxx"

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
        BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name) : Base(std::forward<NameType>(name)), stream_(stream) {}

        BasicConsoleSink(std::basic_ostream<CharType>& stream, NameType&& name, detail::AsyncSink isAsync) : Base(std::forward<NameType>(name), isAsync), stream_(stream) {}

        ~BasicConsoleSink() override = default;

    public:
        std::basic_ostream<CharType>& GetStream() {
            return stream_;
        }

    protected:
        void WriteImpl(const BufferType& bufferToPrint) override {
            stream_.write(bufferToPrint.data(), bufferToPrint.size());
            stream_.write("\n", 1);
            stream_.flush();
        }

    private:
        std::basic_ostream<CharType>& stream_;
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
            : Base(std::forward<NameType>(name), isAsync), stream_(filePath, std::ios::out) {}

        ~BasicFileSink() override = default;

    public:
        std::basic_ostream<CharType>& GetStream() {
            return stream_;
        }

    protected:
        void WriteImpl(const BufferType& bufferToPrint) override {
            stream_.write(bufferToPrint.data(), bufferToPrint.size());
            stream_.write("\n", 1);
            stream_.flush();
        }

    private:
        std::basic_ofstream<CharType> stream_;
    };
}  // namespace stream::flog::Sinks
