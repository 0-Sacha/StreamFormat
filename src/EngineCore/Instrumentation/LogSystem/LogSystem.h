#pragma once

#include "Formatter/Formatter.h"

#ifndef ENGINECORE_BASE_LOGGER_NAME
	#define ENGINECORE_BASE_LOGGER_NAME "APP"
#endif

namespace EngineCore {

	class LogSystem {
	public:
		enum class LogSeverity : int {
			Trace,
			Info,
			Warn,
			Error,
			Fatal
		};

		enum class LogStatus : int {
			OK,
			FAIL
		};

	public:
		LogSystem() : m_Name("Logger"), m_SeverityMin(LogSeverity::Trace), m_Stream(std::cout) { ResetFormat(); }
		
		explicit LogSystem(const std::string_view& name, LogSeverity severityMin = LogSeverity::Trace, std::ostream& stream = std::cout)
			: m_Name(name), m_SeverityMin(severityMin), m_Stream(stream)
		{
			ResetFormat();
		}
		explicit LogSystem(const std::string_view& name, const std::string_view& format, LogSeverity severityMin = LogSeverity::Trace, std::ostream& stream = std::cout)
			: m_Name(name), m_SeverityMin(severityMin), m_Stream(stream)
		{
			SetBaseFormat(format);
		}
		~LogSystem() = default;

	public:
		static LogSystem& GetCoreInstance()				{ static LogSystem instance(ENGINECORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
		static LogSystem& GetClientInstance()			{ static LogSystem instance(ENGINECORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }

	public:
		void SetSeverity(LogSeverity severityMin)		{ m_SeverityMin = severityMin; }
		void SetName(const std::string& name)			{ m_Name = name; }
		void SetName(std::string&& name)				{ m_Name = std::move(name); }
		void SetBaseFormat(std::string_view basetFmt)	{ m_FmtBuffer = "{color:W}"; m_FmtBuffer += basetFmt; }
		void ResetFormat()								{ SetBaseFormat("[{T:%h:%m:%s:%ms}] {name} >> {data}"); }

	public:
		/////---------- Logger Severity with array as format ----------/////
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogSeverity severity, const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogTrace(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogInfo(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogWarn(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogError(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogFatal(const Format& format, Args&& ...args) const;

		/////---------- NO-FORMAT Logger Severity ----------/////
		template<typename T>
		void Log(LogSeverity severity, T&& t) const;
		template<typename T>
		inline void LogTrace(T&& t) const;
		template<typename T>
		inline void LogInfo(T&& t) const;
		template<typename T>
		inline void LogWarn(T&& t) const;
		template<typename T>
		inline void LogError(T&& t) const;
		template<typename T>
		inline void LogFatal(T&& t) const;

	public:
		/////---------- Logger Status with array as format ----------/////
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(LogStatus status, const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogOk(const Format& format, Args&& ...args) const;
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogFail(const Format& format, Args&& ...args) const;

		/////---------- NO-FORMAT Logger Status ----------/////
		template<typename T>
		void Log(LogStatus status, T&& t) const;
		template<typename T>
		inline void LogOk(T&& t) const;
		template<typename T>
		inline void LogFail(T&& t) const;

	public:
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		inline void LogBasic(const Format& format, Args&& ...args) const;

		template<typename T>
		inline void LogBasic(T&& t) const;

	private:
		std::string m_Name;
		LogSeverity m_SeverityMin;
		std::ostream& m_Stream;

		std::string m_FmtBuffer;

	public:
		template<typename FormatStr>
		struct AddIndentInFormat
		{
			AddIndentInFormat(const FormatStr& format)
			 : Format(format)
			{}
			const FormatStr& Format;
		};
	};
}


namespace EngineCore::FMT {
	template<typename FormatContext>
	struct FormatType<LogSystem::LogSeverity, FormatContext>
	{
		static void Write(const LogSystem::LogSeverity t, FormatContext& context) {
			switch (t)
			{
			case LogSystem::LogSeverity::Trace:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::BrightBlack, context);
				break;
			case LogSystem::LogSeverity::Info:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Green, context);
				break;
			case LogSystem::LogSeverity::Warn:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Yellow, context);
				break;
			case LogSystem::LogSeverity::Error:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Red, context);
				break;
			case LogSystem::LogSeverity::Fatal:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::BrightMagenta, context);
				break;
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<LogSystem::LogStatus, FormatContext>
	{
		static void Write(const LogSystem::LogStatus status, FormatContext& context) {
			if (status == LogSystem::LogStatus::OK)			context.LittleFormat("[{:C:green}]", " OK ");
			else if (status == LogSystem::LogStatus::FAIL)	context.LittleFormat("[{:C:red}]", "FAIL");
		}
	};
template<typename FormatContext, typename FormatStr>
	struct FormatType<LogSystem::AddIndentInFormat<FormatStr>, FormatContext>
	{
		static void Write(const LogSystem::AddIndentInFormat<FormatStr>& format, FormatContext& context) {
			context.Print("{K:indent}");
			context.RunType(format.Format);
		}
	};
}



namespace EngineCore {

	/////---------- Logger Severity with format ----------/////
	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	void LogSystem::Log(LogSeverity severity, const Format& format, Args&& ...args) const {
		if (severity >= m_SeverityMin) {
			auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(m_FmtBuffer), FORMAT_SV("name", m_Name), FORMAT_SV("data", LogSystem::AddIndentInFormat(format)), FORMAT_SV("setindent", "{K:indent}"));
			FMT::FilePrintLn(m_Stream, static_cast<std::string_view>(formatBuffer), std::forward<Args>(args)..., FORMAT_SV("color", severity));
		}
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogTrace(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Trace, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogInfo(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Info, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogWarn(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Warn, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogError(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Error, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogFatal(const Format& format, Args&& ...args) const {
		Log(LogSeverity::Fatal, format, std::forward<Args>(args)...);
	}

	/////---------- NO-FORMAT Logger Severity ----------/////
	template<typename T>
	void LogSystem::Log(LogSeverity severity, T&& t) const {
		if (severity >= m_SeverityMin)
			FMT::FilePrintLn(m_Stream, m_FmtBuffer, FORMAT_SV("data", t), FORMAT_SV("color", severity), FORMAT_SV("name", m_Name));
	}

	template<typename T>
	inline void LogSystem::LogTrace(T&& t) const {
		Log(LogSeverity::Trace, std::forward<T>(t));
	}

	template<typename T>
	inline void LogSystem::LogInfo(T&& t) const {
		Log(LogSeverity::Info, std::forward<T>(t));
	}

	template<typename T>
	inline void LogSystem::LogWarn(T&& t) const {
		Log(LogSeverity::Warn, std::forward<T>(t));
	}

	template<typename T>
	inline void LogSystem::LogError(T&& t) const {
		Log(LogSeverity::Error, std::forward<T>(t));
	}

	template<typename T>
	inline void LogSystem::LogFatal(T&& t) const {
		Log(LogSeverity::Fatal, std::forward<T>(t));
	}

}

namespace EngineCore {

	/////---------- Logger Status with format ----------/////
	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	void LogSystem::Log(LogStatus status, const Format& format, Args&& ...args) const {
		auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(m_FmtBuffer, FORMAT_SV("name", m_Name), FORMAT_SV("data", format), FORMAT_SV("setindent", "{K:indent}"));
		FMT::FilePrintLn(m_Stream, (std::string_view)formatBuffer, std::forward<Args>(args)..., FORMAT_SV("color", status));
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogOk(const Format& format, Args&& ...args) const {
		Log(LogStatus::OK, format, std::forward<Args>(args)...);
	}

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogFail(const Format& format, Args&& ...args) const {
		Log(LogStatus::FAIL, format, std::forward<Args>(args)...);
	}


	/////---------- NO-FORMAT Logger Status ----------/////
	template<typename T>
	void LogSystem::Log(LogStatus status, T&& t) const {
		FMT::FilePrintLn(m_Stream, m_FmtBuffer, FORMAT_SV("data", t), FORMAT_SV("color", status), FORMAT_SV("name", m_Name));
	}

	template<typename T>
	inline void LogSystem::LogOk(T&& t) const {
		Log(LogStatus::OK, std::forward<T>(t));
	}

	template<typename T>
	inline void LogSystem::LogFail(T&& t) const {
		Log(LogStatus::FAIL, std::forward<T>(t));
	}
}


namespace EngineCore {

	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	inline void LogSystem::LogBasic(const Format& format, Args&& ...args) const {
		auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(m_FmtBuffer, FORMAT_SV("color", ""), FORMAT_SV("name", m_Name), FORMAT_SV("data", format));
		FMT::FilePrintLn(m_Stream, (std::string_view)formatBuffer, std::forward<Args>(args)...);
	}

	template<typename T>
	inline void LogSystem::LogBasic(T&& t) const {
		FMT::FilePrintLn(m_Stream, m_FmtBuffer, FORMAT_SV("color", ""), FORMAT_SV("data", t), FORMAT_SV("name", m_Name));
	}

}



// Logger define
#ifdef ENGINECORE_LOGGER_ENABLE
#define ENGINECORE_TRACE(...)	EngineCore::LogSystem::GetCoreInstance().LogTrace(__VA_ARGS__)
#define ENGINECORE_INFO(...)	EngineCore::LogSystem::GetCoreInstance().LogInfo(__VA_ARGS__)
#define ENGINECORE_WARN(...)	EngineCore::LogSystem::GetCoreInstance().LogWarn(__VA_ARGS__)
#define ENGINECORE_ERROR(...)	EngineCore::LogSystem::GetCoreInstance().LogError(__VA_ARGS__)
#define ENGINECORE_FATAL(...)	EngineCore::LogSystem::GetCoreInstance().LogFatal(__VA_ARGS__)

#define ENGINECORE_OK(...)		EngineCore::LogSystem::GetCoreInstance().LogOk(__VA_ARGS__)
#define ENGINECORE_FAIL(...)	EngineCore::LogSystem::GetCoreInstance().LogFail(__VA_ARGS__)

#define ENGINECORE_BASIC(...)	EngineCore::LogSystem::GetCoreInstance().LogBasic(__VA_ARGS__)
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