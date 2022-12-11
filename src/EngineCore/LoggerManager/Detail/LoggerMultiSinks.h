#pragma once

#include "Detail.h"
#include "LoggerSink.h"
#include "LoggerManager/Loggers/BasicLogger.h"

namespace EngineCore::LoggerManager::Detail {
    template <typename CharType>
	class BasicLoggerMultiSinkImpl {
	public:
		BasicLoggerMultiSinkImpl() : m_Name("Logger:{sink}") {}
		BasicLoggerMultiSinkImpl(std::basic_string<CharType>&& name) : m_Name(std::forward<std::basic_string<CharType>>(name)) {}

	public:
		void SetName(std::basic_string<CharType>&& name)	{ m_Name = std::forward<std::basic_string<CharType>>(name); }

		std::basic_string<CharType>& GetName()								{ return m_Name; }
		std::vector<std::shared_ptr<BasicLoggerSink<CharType>>>& GetSinks()	{ return m_Sinks; }

	protected:
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
	};
}
