#pragma once

#include "FMT/Formatter.h"

namespace EngineCore::LoggerManager {

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

	struct LogBasic {};

    template<typename FormatStr>
	struct AddIndentInFormat
	{
		AddIndentInFormat(const FormatStr& format)
			: Format(format)
		{}
		const FormatStr& Format;
	};

 template<typename CharType>
	struct ConcateNameAndSinkName
	{
		ConcateNameAndSinkName(const std::basic_string<CharType>& loggerName, const std::basic_string<CharType>& sinkName)
			: LoggerName(loggerName)
			, SinkName(sinkName)
		{}
		const std::basic_string<CharType>& LoggerName;
		const std::basic_string<CharType>& SinkName;
	};

}

namespace EngineCore::FMT {
	template<typename FormatterContext>
	struct FormatterType<EngineCore::LoggerManager::LogSeverity, FormatterContext>
	{
		static void Write(const EngineCore::LoggerManager::LogSeverity t, FormatterContext& context) {
			switch (t)
			{
			case EngineCore::LoggerManager::LogSeverity::Trace:
				FormatterType<Detail::AnsiTextColorFG, FormatterContext>::Write(Detail::AnsiTextColorFG::BrightBlack, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Debug:
				FormatterType<Detail::AnsiTextColorFG, FormatterContext>::Write(Detail::AnsiTextColorFG::Blue, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Info:
				FormatterType<Detail::AnsiTextColorFG, FormatterContext>::Write(Detail::AnsiTextColorFG::Green, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Warn:
				FormatterType<Detail::AnsiTextColorFG, FormatterContext>::Write(Detail::AnsiTextColorFG::Yellow, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Error:
				FormatterType<Detail::AnsiTextColorFG, FormatterContext>::Write(Detail::AnsiTextColorFG::Red, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Fatal:
				FormatterType<Detail::AnsiTextColorFG, FormatterContext>::Write(Detail::AnsiTextColorFG::BrightMagenta, context);
				break;
			}
		}
	};

	template<typename FormatterContext>
	struct FormatterType<EngineCore::LoggerManager::LogStatus, FormatterContext>
	{
		static void Write(const EngineCore::LoggerManager::LogStatus status, FormatterContext& context) {
			if (status == EngineCore::LoggerManager::LogStatus::OK)			context.SubContext("[{:C:green}]", " OK ");
			else if (status == EngineCore::LoggerManager::LogStatus::FAIL)	context.SubContext("[{:C:red}]", "FAIL");
		}
	};

	template<typename FormatterContext>
	struct FormatterType<EngineCore::LoggerManager::LogBasic, FormatterContext>
	{
		static void Write(const EngineCore::LoggerManager::LogBasic, FormatterContext& context) {}
	};



	template<typename FormatterContext, typename FormatStr>
	struct FormatterType<EngineCore::LoggerManager::AddIndentInFormat<FormatStr>, FormatterContext>
	{
		static void Write(const EngineCore::LoggerManager::AddIndentInFormat<FormatStr>& format, FormatterContext& context) {
			context.Print("{K:indent}");
			context.RunType(format.Format);
		}
	};

	template<typename FormatterContext, typename CharType>
	struct FormatterType<EngineCore::LoggerManager::ConcateNameAndSinkName<CharType>, FormatterContext>
	{
		static void Write(const EngineCore::LoggerManager::ConcateNameAndSinkName<CharType>& names, FormatterContext& context) {
			auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(names.LoggerName, FORMAT_SV("sink", names.SinkName));
			context.Print(static_cast<std::basic_string_view<CharType>>(formatBuffer));
		}
	};
}
