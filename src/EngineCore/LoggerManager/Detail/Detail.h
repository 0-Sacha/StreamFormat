#pragma once

#include "EngineCore/FMT/FMT.h"

namespace EngineCore::LoggerManager {

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
	template<typename FormatterContext, typename FormatStr>
	struct FormatterType<EngineCore::LoggerManager::AddIndentInFormat<FormatStr>, FormatterContext>
	{
		static void Format(const EngineCore::LoggerManager::AddIndentInFormat<FormatStr>& format, FormatterContext& context) {
			context.Print("{K:indent}");
			context.RunType(format.Format);
		}
	};

	template<typename FormatterContext, typename CharType>
	struct FormatterType<EngineCore::LoggerManager::ConcateNameAndSinkName<CharType>, FormatterContext>
	{
		static void Format(const EngineCore::LoggerManager::ConcateNameAndSinkName<CharType>& names, FormatterContext& context) {
			context.SubContext(names.LoggerName, FORMAT_SV("sink", names.SinkName));
		}
	};
}
