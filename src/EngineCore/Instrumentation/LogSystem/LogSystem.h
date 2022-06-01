#pragma once

#include "EngineCore/Instrumentation/Formatter/Formatter.h"

#ifndef ENGINECORE_BASE_LOGGER_NAME
	#define ENGINECORE_BASE_LOGGER_NAME "APP"
#endif

namespace EngineCore::Instrumentation {

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
			SetFormat(format);
		}
		~LogSystem() = default;

	public:
		static LogSystem& GetCoreInstance()				{ static LogSystem instance(ENGINECORE_BASE_LOGGER_NAME "-Core", LogSeverity::Trace); return instance; }
		static LogSystem& GetClientInstance()			{ static LogSystem instance(ENGINECORE_BASE_LOGGER_NAME "-Client", LogSeverity::Trace); return instance; }

	public:
		void SetSeverity(LogSeverity severityMin)		{ m_SeverityMin = severityMin; }
		void SetName(const std::string& name)			{ m_Name = name; }
		void SetName(std::string&& name)				{ m_Name = std::move(name); }
		void SetBaseFormat(std::string_view basetFmt)	{ FMT::FormatInChar(m_FmtBuffer, "{color}{}", basetFmt); ComputeBufferInstant(); }
		// You need to put {color} flag to have color ; use SetBaseColor instead
		void SetFormat(std::string_view basetFmt)		{ FMT::FormatInChar(m_FmtBuffer, basetFmt); ComputeBufferInstant(); }
		void ResetFormat()								{ SetBaseFormat("[{T:%h:%m:%s:%ms}] {name} >> {setindent}{data}"); }

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
		inline void ComputeBufferInstant()
		{
			FMT::FormatInChar(m_FmtBufferInstant, m_FmtBuffer, FORMAT_SV("setindent", "{K:indent}"));
		}

	private:
		std::string m_Name;
		LogSeverity m_SeverityMin;
		std::ostream& m_Stream;

		char m_FmtBuffer[64];
		char m_FmtBufferInstant[64];
	};
}


namespace EngineCore::Instrumentation::FMT {
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
}


namespace EngineCore::Instrumentation {

	/////---------- Logger Severity with format ----------/////
	template<typename Format, typename ...Args>
	requires FMT::Detail::IsFmtConvertible<Format>::Value
	void LogSystem::Log(LogSeverity severity, const Format& format, Args&& ...args) const {
		if (severity >= m_SeverityMin) {
			auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(m_FmtBuffer), FORMAT_SV("name", m_Name), FORMAT_SV("data", format), FORMAT_SV("setindent", "{K:indent}"));
			FMT::FilePrintLn(m_Stream, (std::string_view)formatBuffer, std::forward<Args>(args)..., FORMAT_SV("color", severity));
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
			FMT::FilePrintLn(m_Stream, m_FmtBufferInstant, FORMAT_SV("data", t), FORMAT_SV("color", severity), FORMAT_SV("name", m_Name));
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

namespace EngineCore::Instrumentation {

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
		FMT::FilePrintLn(m_Stream, m_FmtBufferInstant, FORMAT_SV("data", t), FORMAT_SV("color", status), FORMAT_SV("name", m_Name));
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


namespace EngineCore::Instrumentation {

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
#ifdef ENGINE_CORE_LOGGER_ENABLE
#define ENGINE_CORE_TRACE(...)	EngineCore::LogSystem::GetCoreInstance().LogTrace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)	EngineCore::LogSystem::GetCoreInstance().LogInfo(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)	EngineCore::LogSystem::GetCoreInstance().LogWarn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)	EngineCore::LogSystem::GetCoreInstance().LogError(__VA_ARGS__)
#define ENGINE_CORE_FATAL(...)	EngineCore::LogSystem::GetCoreInstance().LogFatal(__VA_ARGS__)

#define ENGINE_CORE_OK(...)		EngineCore::LogSystem::GetCoreInstance().LogOk(__VA_ARGS__)
#define ENGINE_CORE_FAIL(...)	EngineCore::LogSystem::GetCoreInstance().LogFail(__VA_ARGS__)

#define ENGINE_CORE_BASIC(...)	EngineCore::LogSystem::GetCoreInstance().LogBasic(__VA_ARGS__)
#else
#define ENGINE_CORE_TRACE(...)
#define ENGINE_CORE_INFO(...)
#define ENGINE_CORE_WARN(...)
#define ENGINE_CORE_ERROR(...)
#define ENGINE_CORE_FATAL(...)

#define ENGINE_CORE_OK(...)
#define ENGINE_CORE_FAIL(...)

#define ENGINE_CORE_BASIC(...)
#endif