#pragma once

#include "Formatter/Formatter.h"

#ifndef ENGINECORE_BASE_LOGGER_NAME
	#define ENGINECORE_BASE_LOGGER_NAME "APP"
#endif

namespace EngineCore::LogManager {

		enum class LogSeverity : int {
			Trace,
			Debug,
			Info,
			Warn,
			Error,
			Fatal
		};

		enum class LogStatus : int {
			OK,
			FAIL
		};

		template<typename FormatStr>
		struct AddIndentInFormat
		{
			AddIndentInFormat(const FormatStr& format)
			 : Format(format)
			{}
			const FormatStr& Format;
		};

	class BasicLogger {
	public:

	public:
		BasicLogger() : m_Name("Logger"), m_SeverityMin(LogSeverity::Trace), m_Stream(std::cout) { ResetPattern(); }
		
		explicit BasicLogger(const std::string_view& name, LogSeverity severityMin = LogSeverity::Trace, std::ostream& stream = std::cout)
			: m_Name(name), m_SeverityMin(severityMin), m_Stream(stream)
		{
			ResetPattern();
		}
		explicit BasicLogger(const std::string_view& name, const std::string_view& format, LogSeverity severityMin = LogSeverity::Trace, std::ostream& stream = std::cout)
			: m_Name(name), m_SeverityMin(severityMin), m_Stream(stream)
		{
			SetPattern(format);
		}
		~BasicLogger() = default;

	public:
		static BasicLogger& GetCoreInstance()			{ static BasicLogger instance(ENGINECORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
		static BasicLogger& GetClientInstance()			{ static BasicLogger instance(ENGINECORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }

	public:
		void SetSeverity(LogSeverity severityMin)		{ m_SeverityMin = severityMin; }
		void SetName(const std::string& name)			{ m_Name = name; }
		void SetName(std::string&& name)				{ m_Name = std::move(name); }
		void SetPattern(std::string_view pattern)		{ m_Pattern = "{color:W}"; m_Pattern += pattern; }
		void ResetPattern()								{ SetPattern("[{T:pattern='%h:%m:%s:%ms'}] {name} >> {data}"); }

	public:
		/////---------- Logger Severity with array as format ----------/////
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogSeverity severity, const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Trace(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Debug(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Info(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Warn(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Error(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Fatal(const Format& format, Args&& ...args) const;

		/////---------- NO-FORMAT Logger Severity ----------/////
		template<typename T>
		void Log(LogSeverity severity, T&& t) const;
		template<typename T>
		inline void Trace(T&& t) const;
		template<typename T>
		inline void Debug(T&& t) const;
		template<typename T>
		inline void Info(T&& t) const;
		template<typename T>
		inline void Warn(T&& t) const;
		template<typename T>
		inline void Error(T&& t) const;
		template<typename T>
		inline void Fatal(T&& t) const;

	public:
		/////---------- Logger Status with array as format ----------/////
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogStatus status, const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Ok(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Fail(const Format& format, Args&& ...args) const;

		/////---------- NO-FORMAT Logger Status ----------/////
		template<typename T>
		void Log(LogStatus status, T&& t) const;
		template<typename T>
		inline void Ok(T&& t) const;
		template<typename T>
		inline void Fail(T&& t) const;

	public:
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void Basic(const Format& format, Args&& ...args) const;

		template<typename T>
		inline void Basic(T&& t) const;

	private:
		std::string m_Name;
		LogSeverity m_SeverityMin;
		std::ostream& m_Stream;

		std::string m_Pattern;
	};
		
}


namespace EngineCore::FMT {
	template<typename FormatContext>
	struct FormatType<EngineCore::LogManager::LogSeverity, FormatContext>
	{
		static void Write(const EngineCore::LogManager::LogSeverity t, FormatContext& context) {
			switch (t)
			{
			case EngineCore::LogManager::LogSeverity::Trace:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::BrightBlack, context);
				break;
			case EngineCore::LogManager::LogSeverity::Debug:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Blue, context);
				break;
			case EngineCore::LogManager::LogSeverity::Info:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Green, context);
				break;
			case EngineCore::LogManager::LogSeverity::Warn:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Yellow, context);
				break;
			case EngineCore::LogManager::LogSeverity::Error:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Red, context);
				break;
			case EngineCore::LogManager::LogSeverity::Fatal:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::BrightMagenta, context);
				break;
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<EngineCore::LogManager::LogStatus, FormatContext>
	{
		static void Write(const EngineCore::LogManager::LogStatus status, FormatContext& context) {
			if (status == EngineCore::LogManager::LogStatus::OK)			context.LittleFormat("[{:C:green}]", " OK ");
			else if (status == EngineCore::LogManager::LogStatus::FAIL)	context.LittleFormat("[{:C:red}]", "FAIL");
		}
	};

	template<typename FormatContext, typename FormatStr>
	struct FormatType<EngineCore::LogManager::AddIndentInFormat<FormatStr>, FormatContext>
	{
		static void Write(const EngineCore::LogManager::AddIndentInFormat<FormatStr>& format, FormatContext& context) {
			context.Print("{K:indent}");
			context.RunType(format.Format);
		}
	};
}



namespace EngineCore::LogManager {

	/////---------- Logger Severity with format ----------/////
	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	void BasicLogger::Log(LogSeverity severity, const Format& format, Args&& ...args) const {
		if (severity >= m_SeverityMin) {
			auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(m_Pattern), FORMAT_SV("name", m_Name), FORMAT_SV("data", LogManager::AddIndentInFormat(format)), FORMAT_SV("setindent", "{K:indent}"));
			FMT::FilePrintLn(m_Stream, static_cast<std::string_view>(formatBuffer), std::forward<Args>(args)..., FORMAT_SV("color", severity));
		}
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Trace(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Trace, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Debug(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Debug, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Info(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Info, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Warn(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Warn, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Error(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Error, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Fatal(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Fatal, format, std::forward<Args>(args)...);
	}

	/////---------- NO-FORMAT Logger Severity ----------/////
	template<typename T>
	void BasicLogger::Log(LogSeverity severity, T&& t) const {
		if (severity >= m_SeverityMin)
			FMT::FilePrintLn(m_Stream, m_Pattern, FORMAT_SV("data", t), FORMAT_SV("color", severity), FORMAT_SV("name", m_Name));
	}

	template<typename T>
	inline void BasicLogger::Trace(T&& t) const {
		Log(LogSeverity::Trace, std::forward<T>(t));
	}

	template<typename T>
	inline void BasicLogger::Debug(T&& t) const {
		Log(LogSeverity::Debug, std::forward<T>(t));
	}

	template<typename T>
	inline void BasicLogger::Info(T&& t) const {
		Log(LogSeverity::Info, std::forward<T>(t));
	}

	template<typename T>
	inline void BasicLogger::Warn(T&& t) const {
		Log(LogSeverity::Warn, std::forward<T>(t));
	}

	template<typename T>
	inline void BasicLogger::Error(T&& t) const {
		Log(LogSeverity::Error, std::forward<T>(t));
	}

	template<typename T>
	inline void BasicLogger::Fatal(T&& t) const {
		Log(LogSeverity::Fatal, std::forward<T>(t));
	}

}

namespace EngineCore::LogManager {

	/////---------- Logger Status with format ----------/////
	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	void BasicLogger::Log(LogStatus status, const Format& format, Args&& ...args) const {
		auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(m_Pattern, FORMAT_SV("name", m_Name), FORMAT_SV("data", format), FORMAT_SV("setindent", "{K:indent}"));
		FMT::FilePrintLn(m_Stream, (std::string_view)formatBuffer, std::forward<Args>(args)..., FORMAT_SV("color", status));
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Ok(const Format& format, Args&& ...args) const {
		Log(LogStatus::OK, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Fail(const Format& format, Args&& ...args) const {
		Log(LogStatus::FAIL, format, std::forward<Args>(args)...);
	}


	/////---------- NO-FORMAT Logger Status ----------/////
	template<typename T>
	void BasicLogger::Log(LogStatus status, T&& t) const {
		FMT::FilePrintLn(m_Stream, m_Pattern, FORMAT_SV("data", t), FORMAT_SV("color", status), FORMAT_SV("name", m_Name));
	}

	template<typename T>
	inline void BasicLogger::Ok(T&& t) const {
		Log(LogStatus::OK, std::forward<T>(t));
	}

	template<typename T>
	inline void BasicLogger::Fail(T&& t) const {
		Log(LogStatus::FAIL, std::forward<T>(t));
	}
}


namespace EngineCore::LogManager {

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void BasicLogger::Basic(const Format& format, Args&& ...args) const {
		auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(m_Pattern, FORMAT_SV("color", ""), FORMAT_SV("name", m_Name), FORMAT_SV("data", format));
		FMT::FilePrintLn(m_Stream, (std::string_view)formatBuffer, std::forward<Args>(args)...);
	}

	template<typename T>
	inline void BasicLogger::Basic(T&& t) const {
		FMT::FilePrintLn(m_Stream, m_Pattern, FORMAT_SV("color", ""), FORMAT_SV("data", t), FORMAT_SV("name", m_Name));
	}

}



// Logger define
#ifdef ENGINECORE_LOGGER_ENABLE
#define ENGINECORE_TRACE(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Trace(__VA_ARGS__)
#define ENGINECORE_INFO(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Info(__VA_ARGS__)
#define ENGINECORE_WARN(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Warn(__VA_ARGS__)
#define ENGINECORE_ERROR(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Error(__VA_ARGS__)
#define ENGINECORE_FATAL(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Fatal(__VA_ARGS__)

#define ENGINECORE_OK(...)		EngineCore::LogManager::BasicLogger::GetCoreInstance().Ok(__VA_ARGS__)
#define ENGINECORE_FAIL(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Fail(__VA_ARGS__)

#define ENGINECORE_BASIC(...)	EngineCore::LogManager::BasicLogger::GetCoreInstance().Basic(__VA_ARGS__)
#else
#define ENGINECORE_TRACE(...)
#define ENGINECORE_INFO(...)
#define ENGINECORE_WARN(...)
#define ENGINECORE_ERROR(...)
#define ENGINECORE_FATAL(...)

#define ENGINECORE_OK(...)
#define ENGINECORE_FAIL(...)

#define ENGINECORE_BASIC(...)
#endif