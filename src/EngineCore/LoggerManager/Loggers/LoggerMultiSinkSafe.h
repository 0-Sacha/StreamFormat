#pragma once

#include "LoggerManager/Detail/Detail.h"
#include "LoggerManager/Detail/LoggerSink.h"
#include "BasicLogger.h"

namespace EngineCore::LoggerManager::Detail {
    template <typename CharType>
	class BasicLoggerMultiSinkSafeImpl {
	public:
		BasicLoggerMultiSinkSafeImpl() : m_Name("Logger") {}
		BasicLoggerMultiSinkSafeImpl(std::basic_string_view<CharType>&& name) : m_Name(std::forward<std::basic_string_view<CharType>>(name)) {}

	public:
		void SetName(std::basic_string_view<CharType>&& name)	{ m_Name = std::forward<std::basic_string_view<CharType>>(name); }

		std::basic_string_view<CharType>& GetName() 					{ return m_Name; }
		std::vector<std::shared_ptr<BasicLoggerSink<CharType>>>& GetSinks()	{ return m_Sinks; }

	private:
		std::basic_string_view<CharType> m_Name;
        std::vector<std::shared_ptr<BasicLoggerSink<CharType>>> m_Sinks;

	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(const Severity& severity, const Format& format, Args&& ...args) {
            // FIXME maybe add : name ; indent ???
            for (auto& sink : m_Sinks)
            {
				if (sink.NeedToLog(severity))
				{
					auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(std::string_view(sink.GetPattern(severity)), FORMAT_SV("name", m_Name), FORMAT_SV("data", LoggerManager::AddIndentInFormat(format)));
					auto formatFormatStr = FMT::Detail::FormatAndGetBufferOut(static_cast<std::string_view>(formatPatternStr), std::forward<Args>(args)..., FORMAT_SV("sink", sink.GetName()), FORMAT_SV("color", severity));
					sink.PrintToSink(severity, formatFormatStr);
				}
            }
	    }

		template<typename Severity, typename T>
		void Log(const Severity& severity, T&& t) {
            for (auto& sink : m_Sinks)
            {
				if (sink.NeedToLog(severity))
				{
					auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(sink.GetPattern(severity)), FORMAT_SV("name", ConcateNameAndSinkName(m_Name, sink.GetName())), FORMAT_SV("data", t));
					sink.PrintToSink(formatBuffer);
				}
            }
	    }
	};
}

#include "LoggerManager/Detail/XLogger.h"

namespace EngineCore::LoggerManager
{
    template <typename CharType>
	using BasicLoggerMultiSinkSafe = Detail::XLogger<Detail::BasicLoggerMultiSinkSafeImpl<CharType>>;
    using LoggerMultiSinkSafe = BasicLoggerMultiSinkSafe<char>;
}
