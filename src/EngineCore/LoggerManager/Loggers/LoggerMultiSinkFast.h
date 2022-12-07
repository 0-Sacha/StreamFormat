#pragma once

#include "LoggerManager/Detail/Detail.h"
#include "LoggerManager/Detail/LoggerSink.h"
#include "BasicLogger.h"

namespace EngineCore::LoggerManager::Detail {
    template <typename CharType>
	class BasicLoggerMultiSinkFastImpl {
	public:
		BasicLoggerMultiSinkFastImpl() : m_Name("Logger") {}
		BasicLoggerMultiSinkFastImpl(std::basic_string_view<CharType>&& name) : m_Name(std::forward<std::basic_string_view<CharType>>(name)) {}

	public:
		void SetName(std::basic_string_view<CharType>&& name)	{ m_Name = std::forward<std::basic_string_view<CharType>>(name); }

		std::basic_string_view<CharType>& GetName()						{ return m_Name; }
		std::vector<std::shared_ptr<BasicLoggerSink<CharType>>>& GetSinks()	{ return m_Sinks; }

	private:
		std::basic_string_view<CharType> m_Name;
        std::vector<std::shared_ptr<BasicLoggerSink<CharType>>> m_Sinks;

	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(const Severity& severity, const Format& format, Args&& ...args) const {
            auto formatFormatStr = FMT::Detail::FormatAndGetBufferOut(format, std::forward<Args>(args)...);
            for (auto& sink : m_Sinks)
			{
				if (sink.NeedToLog(severity))
				{
					auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(sink.GetPattern(severity),
																			   FORMAT_SV("name", ConcateNameAndSinkName(m_Name, sink.GetName())),
																			   FORMAT_SV("data", static_cast<std::basic_string_view<CharType>>(formatFormatStr)));
	                sink.PrintToSink(formatPatternStr);
				}
			}
	    }

		template<typename Severity, typename T>
		void Log(const Severity& severity, T&& t) const {
            auto formatType = FMT::Detail::FormatAndGetBufferOut(std::forward<T>(t));
            for (auto& sink : m_Sinks)
			{
				auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(sink.GetPattern(severity),
																		   FORMAT_SV("name", ConcateNameAndSinkName(m_Name, sink.GetName())),
																		   FORMAT_SV("data", static_cast<std::basic_string_view<CharType>>(formatType)));
	            sink.PrintToSink(formatPatternStr);
			}
	    }
	};
}

#include "LoggerManager/Detail/XLogger.h"

namespace EngineCore::LoggerManager
{
    template <typename CharType>
	using BasicLoggerMultiSinkFast = Detail::XLogger<Detail::BasicLoggerMultiSinkFastImpl<CharType>>;
    using LoggerMultiSinkFast = BasicLoggerMultiSinkFast<char>;
}
