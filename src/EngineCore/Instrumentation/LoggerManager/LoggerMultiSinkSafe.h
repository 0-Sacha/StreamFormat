#pragma once

#include "BasicLogger.h"
#include "Detail/Detail.h"
#include "Detail/LoggerSink.h"

namespace EngineCore::LoggerManager::Detail {
    template <typename CharType>
	class BasicLoggerMultiSinkSafeImpl {
	public:
		BasicLoggerMultiSinkSafeImpl() : m_Name("Logger") {}

	public:
		void SetName(const std::string& name)	{ m_Name = name; }
		void SetName(std::string&& name)		{ m_Name = std::move(name); }

		std::string& GetName()				                    { return m_Name; }
		std::vector<Detail::LoggerSink<CharType>>& GetSinks()	{ return m_Sinks; }

	private:
		std::string m_Name;
        std::vector<Detail::LoggerSink<CharType>> m_Sinks;

	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogSeverity severity, const Format& format, Args&& ...args) const {
            // FIXME maybe add : name ; indent ???
            for (auto& sink : m_Sinks)
            {
                auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(format, FORMAT_SV("name", m_Name), std::forward<Args>(args)...);
                sink.FormatAndPrintToSink(severity, formatBuffer);
            }
	    }

		template<typename Severity, typename T>
		void Log(LogSeverity severity, T&& t) const {
            for (auto& sink : m_Sinks)
            {
                auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(format, FORMAT_SV("name", m_Name), std::forward<T>(t));
                sink.FormatAndPrintToSink(severity, formatBuffer);
            }
	    }
	};
}

#include "Detail/XLogger.h"

namespace EngineCore::LoggerManager
{
    template <typename CharType>
	using BasicLoggerMultiSinkSafe = Detail::XLogger<Detail::BasicLoggerMultiSinkSafeImpl<CharType>>;
    using LoggerMultiSinkSafe = BasicLoggerMultiSinkSafe<char>;
}
