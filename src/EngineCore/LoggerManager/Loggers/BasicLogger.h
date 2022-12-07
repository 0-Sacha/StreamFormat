#pragma once

#include "LoggerManager/Detail/Detail.h"

namespace EngineCore::LoggerManager::Detail {
	class BasicLoggerImpl {
	public:
		BasicLoggerImpl() : m_Name("Logger"), m_SeverityMin(LogSeverity::Trace), m_Stream(std::cout) { ResetPattern(); }
		
		explicit BasicLoggerImpl(const std::string_view& name, LogSeverity severityMin = LogSeverity::Trace, std::ostream& stream = std::cout)
			: m_Name(name), m_SeverityMin(severityMin), m_Stream(stream)
		{
			ResetPattern();
		}
		explicit BasicLoggerImpl(const std::string_view& name, const std::string_view& format, LogSeverity severityMin = LogSeverity::Trace, std::ostream& stream = std::cout)
			: m_Name(name), m_SeverityMin(severityMin), m_Stream(stream)
		{
			SetPattern(format);
		}

	public:
		void SetSeverity(LogSeverity severityMin)		{ m_SeverityMin = severityMin; }
		void SetName(const std::string& name)			{ m_Name = name; }
		void SetName(std::string&& name)				{ m_Name = std::move(name); }
		void SetPattern(std::string_view pattern)		{ m_Pattern = "{color:W}"; m_Pattern += pattern; }
		void ResetPattern()								{ SetPattern("[{T:pattern='%h:%m:%s:%ms'}] {name} >> {data}"); }

	private:
		std::string m_Name;
		LogSeverity m_SeverityMin;
		std::ostream& m_Stream;

		std::string m_Pattern;


	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void LogImpl(Severity severity, const Format& format, Args&& ...args) const {
			auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(m_Pattern), FORMAT_SV("name", m_Name), FORMAT_SV("data", LoggerManager::AddIndentInFormat(format)));
			FMT::FilePrintLn(m_Stream, static_cast<std::string_view>(formatBuffer), std::forward<Args>(args)..., FORMAT_SV("color", severity));
		}
		template<typename Severity, typename T>
		void LogImpl(Severity severity, T&& t) const {
			FMT::FilePrintLn(m_Stream, m_Pattern, FORMAT_SV("data", t), FORMAT_SV("color", severity), FORMAT_SV("name", m_Name));
		}

	public:
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogSeverity severity, const Format& format, Args&& ...args) const 	{ if (severity < m_SeverityMin) return; return LogImpl(severity, format, std::forward<Args>(args)...); }
		template<typename T>
		void Log(LogSeverity severity, T&& t) const 								{ if (severity < m_SeverityMin) return; return LogImpl(severity, std::forward<T>(t)); }

	public:
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogStatus status, const Format& format, Args&& ...args) const 	{ return LogImpl(status, format, std::forward<Args>(args)...); }
		template<typename T>
		void Log(LogStatus status, T&& t) const 								{ return LogImpl(status, std::forward<T>(t)); }

	public:
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogBasic basic, const Format& format, Args&& ...args) const 	{ return LogImpl(basic, format, std::forward<Args>(args)...); }
		template<typename T>
		void Log(LogBasic basic, T&& t) const 									{ return LogImpl(basic, std::forward<T>(t)); }
	};
}

#include "LoggerManager/Detail/XLogger.h"

namespace EngineCore::LoggerManager
{
	using BasicLogger = Detail::XLogger<Detail::BasicLoggerImpl>;
}
