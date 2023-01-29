#pragma once

#include "EngineCore/LoggerManager/LoggerManager.h"

namespace EngineCore::UnLOG
{
	struct LogBuffer
	{
		std::vector<std::string> Logs;
		void Clear() { Logs.clear(); }
	};

	template <typename Severity, typename CharType>
	class BasicUnLOGSink : public LoggerManager::Detail::BasicLoggerSink<Severity, CharType>
	{
	public:
		using Base = LoggerManager::Detail::BasicLoggerSink<Severity, CharType>;
		using typename Base::PatternType;
		using typename Base::NameType;
		using typename Base::BufferType;

	public:
		BasicUnLOGSink()
			: Base("UnLOG")
		{}

	public:
		LogBuffer& GetLogs() { return m_Logs; }
		const LogBuffer& GetLogs() const { return m_Logs; }

	private:
		LogBuffer m_Logs;

	protected:
		void WriteImpl(const BufferType& bufferToPrint) override
		{
			m_Logs.Logs.emplace_back(bufferToPrint.data(), bufferToPrint.size());
		}
	};

	using UnLOGSink = BasicUnLOGSink<LoggerManager::LogSeverity, char>;
}