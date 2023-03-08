#pragma once

#include "LoggerManager/Detail/Detail.h"
#include "LoggerManager/Loggers/BasicLogger.h"
#include "LoggerManager/Loggers/LoggerMultiSinkFast.h"
#include "LoggerManager/Loggers/LoggerMultiSinkSafe.h"
#include "LoggerManager/Sinks/FileSink.h"

namespace ProjectCore::LoggerManager {

	struct LogSeverity
	{
	public:
		enum class Value : int
		{
			Trace,
			Debug,
			Info,
			Warn,
			Error,
			Fatal,
			DefaultSeverity = Trace
		};

	public:
		static constexpr Value Trace	{Value::Trace};
		static constexpr Value Debug	{Value::Debug};
		static constexpr Value Info		{Value::Info};
		static constexpr Value Warn		{Value::Warn};
		static constexpr Value Error	{Value::Error};
		static constexpr Value Fatal	{Value::Fatal};
		static constexpr Value DefaultSeverity = Trace;

	public:
		class PatternOverride
		{
		public:
			std::basic_string<char> TracePattern = "";
			std::basic_string<char> DebugPattern = "";
			std::basic_string<char> InfoPattern = "";
			std::basic_string<char> WarnPattern = "";
			std::basic_string<char> ErrorPattern = "";
			std::basic_string<char> FatalPattern = "";

			std::basic_string_view<char> GetPattern(const Value& severity) const 
			{
				switch(severity)
				{
					case Value::Trace:    if (TracePattern.empty() == false) 	return TracePattern; 	break;
					case Value::Debug:    if (DebugPattern.empty() == false) 	return DebugPattern; 	break;
					case Value::Info:     if (InfoPattern.empty() == false) 	return InfoPattern; 	break;
					case Value::Warn:     if (WarnPattern.empty() == false) 	return WarnPattern; 	break;
					case Value::Error:    if (ErrorPattern.empty() == false) 	return ErrorPattern; 	break;
					case Value::Fatal:    if (FatalPattern.empty() == false) 	return FatalPattern; 	break;
				}
				return std::basic_string_view<char>{nullptr, 0};
			}
		};
	};
}

namespace ProjectCore::LoggerManager::Detail {
	template <typename Master>
	class XLogger : public Master
	{
	public:
		template <typename... Args>
		XLogger(Args&&... args)
			: Master(std::forward<Args>(args)...)
		{}

		~XLogger() override = default;

	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
			requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(Severity status, const Format& format, Args&& ...args) { Master::template Log(status, format, std::forward<Args>(args)...); }

		template<typename Severity, typename T>
		void Log(Severity status, T&& t) { Master::template Log(status, std::forward<T>(t)); }

	public:
		/////---------- Logger Severity with array as format ----------/////
		template<typename Format = std::string_view, typename ...Args>
			requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Trace(const Format& format, Args&& ...args) { return Log(LogSeverity::Trace, format, std::forward<Args>(args)...); }
		template<typename Format = std::string_view, typename ...Args>
			requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Debug(const Format& format, Args&& ...args) { return Log(LogSeverity::Debug, format, std::forward<Args>(args)...); }
		template<typename Format = std::string_view, typename ...Args>
			requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Info(const Format& format, Args&& ...args) { return Log(LogSeverity::Info, format, std::forward<Args>(args)...); }
		template<typename Format = std::string_view, typename ...Args>
			requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Warn(const Format& format, Args&& ...args) { return Log(LogSeverity::Warn, format, std::forward<Args>(args)...); }
		template<typename Format = std::string_view, typename ...Args>
			requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Error(const Format& format, Args&& ...args) { return Log(LogSeverity::Error, format, std::forward<Args>(args)...); }
		template<typename Format = std::string_view, typename ...Args>
			requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Fatal(const Format& format, Args&& ...args) { return Log(LogSeverity::Fatal, format, std::forward<Args>(args)...); }

		/////---------- NO-FORMAT Logger Severity ----------/////
		template<typename T>
		inline void Trace(T&& t) { return Log(LogSeverity::Trace, std::forward<T>(t)); }
		template<typename T>
		inline void Debug(T&& t) { return Log(LogSeverity::Debug, std::forward<T>(t)); }
		template<typename T>
		inline void Info(T&& t) { return Log(LogSeverity::Info, std::forward<T>(t)); }
		template<typename T>
		inline void Warn(T&& t) { return Log(LogSeverity::Warn, std::forward<T>(t)); }
		template<typename T>
		inline void Error(T&& t) { return Log(LogSeverity::Error, std::forward<T>(t)); }
		template<typename T>
		inline void Fatal(T&& t) { return Log(LogSeverity::Fatal, std::forward<T>(t)); }
	};
}

namespace ProjectCore::FMT {
	template<typename FormatterContext>
	struct FormatterType<ProjectCore::LoggerManager::LogSeverity::Value, FormatterContext>
	{
		static void Format(const ProjectCore::LoggerManager::LogSeverity::Value t, FormatterContext& context)
		{
			context.GetFormatData().KeepNewStyle = true;
			switch (t)
			{
			case ProjectCore::LoggerManager::LogSeverity::Trace:
				FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::BrightBlack, context);
				break;
			case ProjectCore::LoggerManager::LogSeverity::Debug:
				FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Blue, context);
				break;
			case ProjectCore::LoggerManager::LogSeverity::Info:
				FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Green, context);
				break;
			case ProjectCore::LoggerManager::LogSeverity::Warn:
				FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Yellow, context);
				break;
			case ProjectCore::LoggerManager::LogSeverity::Error:
				FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::Red, context);
				break;
			case ProjectCore::LoggerManager::LogSeverity::Fatal:
				FormatterType<Detail::TextProperties::TextColor::BasicColorFG, FormatterContext>::Format(Detail::TextProperties::TextColor::BasicColorFG::BrightMagenta, context);
				break;
			}
		}
	};
}

namespace ProjectCore::LoggerManager
{
    template <typename CharType>
	using BasicLoggerMultiSinkFast = Detail::XLogger<Detail::BasicLoggerMultiSinkFastImpl<LogSeverity, CharType>>;
    using LoggerMultiSinkFast = BasicLoggerMultiSinkFast<char>;

	template <typename CharType>
	using BasicLoggerMultiSinkSafe = Detail::XLogger<Detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, CharType>>;
    using LoggerMultiSinkSafe = BasicLoggerMultiSinkSafe<char>;

	using BasicLogger = Detail::XLogger<Detail::BasicLoggerImpl<LogSeverity>>;
}


namespace ProjectCore::LoggerManager::Sinks
{
    using ConsoleSink = Severity::ConsoleSink<LogSeverity>;
    using FileSink = Severity::FileSink<LogSeverity>;
}
