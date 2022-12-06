#pragma once

#include "Formatter/Formatter.h"

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

}

namespace EngineCore::FMT {
	template<typename FormatContext>
	struct FormatType<EngineCore::LoggerManager::LogSeverity, FormatContext>
	{
		static void Write(const EngineCore::LoggerManager::LogSeverity t, FormatContext& context) {
			switch (t)
			{
			case EngineCore::LoggerManager::LogSeverity::Trace:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::BrightBlack, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Debug:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Blue, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Info:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Green, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Warn:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Yellow, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Error:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::Red, context);
				break;
			case EngineCore::LoggerManager::LogSeverity::Fatal:
				FormatType<Detail::AnsiTextColorFG, FormatContext>::Write(Detail::AnsiTextColorFG::BrightMagenta, context);
				break;
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<EngineCore::LoggerManager::LogStatus, FormatContext>
	{
		static void Write(const EngineCore::LoggerManager::LogStatus status, FormatContext& context) {
			if (status == EngineCore::LoggerManager::LogStatus::OK)			context.LittleFormat("[{:C:green}]", " OK ");
			else if (status == EngineCore::LoggerManager::LogStatus::FAIL)	context.LittleFormat("[{:C:red}]", "FAIL");
		}
	};

	template<typename FormatContext>
	struct FormatType<EngineCore::LoggerManager::LogBasic, FormatContext>
	{
		static void Write(const EngineCore::LoggerManager::LogBasic, FormatContext& context) {}
	};

	template<typename FormatContext, typename FormatStr>
	struct FormatType<EngineCore::LoggerManager::AddIndentInFormat<FormatStr>, FormatContext>
	{
		static void Write(const EngineCore::LoggerManager::AddIndentInFormat<FormatStr>& format, FormatContext& context) {
			context.Print("{K:indent}");
			context.RunType(format.Format);
		}
	};
}
