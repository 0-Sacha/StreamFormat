#pragma once

#include "LoggerManager/Detail/LoggerMultiSinks.h"

namespace EngineCore::LoggerManager::Detail {
    template <typename CharType>
	class BasicLoggerMultiSinkSafeImpl: public BasicLoggerMultiSinkImpl<CharType>
	{
	public:
		using BasicLoggerMultiSinkImpl<CharType>::SetName;
		using BasicLoggerMultiSinkImpl<CharType>::GetName;
		using BasicLoggerMultiSinkImpl<CharType>::GetSinks;
		using BasicLoggerMultiSinkImpl<CharType>::m_Name;
		using BasicLoggerMultiSinkImpl<CharType>::m_Sinks;
		using BasicLoggerMultiSinkImpl<CharType>::AddSink;

	public:
		BasicLoggerMultiSinkSafeImpl() : BasicLoggerMultiSinkImpl<CharType>() {}
		
		BasicLoggerMultiSinkSafeImpl(std::basic_string<CharType>&& name)
			: BasicLoggerMultiSinkImpl<CharType>(std::forward<std::basic_string<CharType>>(name))
		{}

	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(const Severity& severity, const Format& format, Args&& ...args) {
            // FIXME maybe add : name ; indent ???
            for (auto& sink : m_Sinks)
            {
				if (sink->NeedToLog(severity))
				{
					auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(std::string_view(sink->GetPattern(severity)), FORMAT_SV("name", m_Name), FORMAT_SV("data", LoggerManager::AddIndentInFormat(format)));
					auto formatFormatStr = FMT::Detail::FormatAndGetBufferOut(static_cast<std::string_view>(formatPatternStr), std::forward<Args>(args)..., FORMAT_SV("sink", sink->GetName()), FORMAT_SV("color", severity));
					sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(formatFormatStr));
				}
            }

			for (auto& sink : m_Sinks)
				if (sink->NeedToLog(severity))
	    			sink->WaitUnitlFinishedToWrite();
	    }

		template<typename Severity, typename T>
		void Log(const Severity& severity, T&& t) {
            for (auto& sink : m_Sinks)
            {
				if (sink->NeedToLog(severity))
				{
					auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(sink->GetPattern(severity)), FORMAT_SV("name", ConcateNameAndSinkName(m_Name, sink->GetName())), FORMAT_SV("data", t));
					sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(formatBuffer));
				}
            }
			
			for (auto& sink : m_Sinks)
				if (sink->NeedToLog(severity))
	    			sink->WaitUnitlFinishedToWrite();
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
