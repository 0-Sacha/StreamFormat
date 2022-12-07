#pragma once

#include "LoggerManager/Detail/Detail.h"
#include "LoggerManager/Detail/LoggerSink.h"
#include "BasicLogger.h"

namespace EngineCore::LoggerManager::Detail {
    template <typename CharType>
	class BasicLoggerMultiSinkFastImpl {
	public:
		BasicLoggerMultiSinkFastImpl() : m_Name("Logger:{sink}") {}
		BasicLoggerMultiSinkFastImpl(std::basic_string<CharType>&& name) : m_Name(std::forward<std::basic_string<CharType>>(name)) {}

	public:
		void SetName(std::basic_string<CharType>&& name)	{ m_Name = std::forward<std::basic_string<CharType>>(name); }

		std::basic_string<CharType>& GetName()								{ return m_Name; }
		std::vector<std::shared_ptr<BasicLoggerSink<CharType>>>& GetSinks()	{ return m_Sinks; }

	private:
		std::basic_string<CharType> m_Name;
        std::vector<std::shared_ptr<BasicLoggerSink<CharType>>> m_Sinks;

	public:
		void AddSink(std::shared_ptr<BasicLoggerSink<CharType>>& sink)
		{
			m_Sinks.push_back(sink);
		}

		template<typename T, typename... Args>
		void AddSink(Args&&... args)
		{
			std::shared_ptr<BasicLoggerSink<CharType>> sink(static_cast<BasicLoggerSink<CharType>*>(new T(std::forward<Args>(args)...)));
			AddSink(sink);
		}

	public:
		template<typename Severity, typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(const Severity& severity, const Format& format, Args&& ...args) {
            auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(format, std::forward<Args>(args)...);
            for (auto& sink : m_Sinks)
				if (sink->NeedToLog(severity))
					sink->FormatAndPrintToSink(sink->GetPattern(severity), m_Name, static_cast<std::basic_string_view<CharType>>(formatBuffer));
	    }

		template<typename Severity, typename T>
		void Log(const Severity& severity, T&& t) {
            auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::forward<T>(t));
            for (auto& sink : m_Sinks)
				if (sink->NeedToLog(severity))
					sink->FormatAndPrintToSink(sink->GetPattern(severity), m_Name, static_cast<std::basic_string_view<CharType>>(formatBuffer));
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
