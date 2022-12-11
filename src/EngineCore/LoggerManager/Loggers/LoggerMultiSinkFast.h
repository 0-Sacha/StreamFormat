#pragma once

#include "LoggerManager/Detail/LoggerMultiSinks.h"

namespace EngineCore::LoggerManager::Detail {
    template <typename CharType>
	class BasicLoggerMultiSinkFastImpl : public BasicLoggerMultiSinkImpl<CharType>
	{
	public:
		using BasicLoggerMultiSinkImpl<CharType>::SetName;
		using BasicLoggerMultiSinkImpl<CharType>::GetName;
		using BasicLoggerMultiSinkImpl<CharType>::GetSinks;
		using BasicLoggerMultiSinkImpl<CharType>::m_Name;
		using BasicLoggerMultiSinkImpl<CharType>::m_Sinks;
		using BasicLoggerMultiSinkImpl<CharType>::AddSink;

	public:
		BasicLoggerMultiSinkFastImpl() : BasicLoggerMultiSinkImpl<CharType>() {}
		
		BasicLoggerMultiSinkFastImpl(std::basic_string<CharType>&& name)
			: BasicLoggerMultiSinkImpl<CharType>(std::forward<std::basic_string<CharType>>(name))
		{}

	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(const Severity& severity, const Format& format, Args&& ...args) {
            auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(format, std::forward<Args>(args)...);
            for (auto& sink : m_Sinks)
				if (sink->NeedToLog(severity))
					sink->FormatAndWriteToSink(sink->GetPattern(severity), m_Name, static_cast<std::basic_string_view<CharType>>(formatBuffer));

			for (auto& sink : m_Sinks)
				if (sink->NeedToLog(severity))
	    			sink->WaitUnitlFinishedToWrite();
		}

		template<typename Severity, typename T>
		void Log(const Severity& severity, T&& t) {
            auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::forward<T>(t));
            for (auto& sink : m_Sinks)
				if (sink->NeedToLog(severity))
					sink->FormatAndWriteToSink(sink->GetPattern(severity), m_Name, static_cast<std::basic_string_view<CharType>>(formatBuffer));
		
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
	using BasicLoggerMultiSinkFast = Detail::XLogger<Detail::BasicLoggerMultiSinkFastImpl<CharType>>;
    using LoggerMultiSinkFast = BasicLoggerMultiSinkFast<char>;
}
