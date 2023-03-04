#pragma once

#include "LoggerManager/Detail/Detail.h"

#include <iostream>

namespace EngineCore::LoggerManager::Detail {

	template <typename Severity>
	class BasicLoggerImpl
	{
	public:
		using SeverityValueType = typename Severity::Value;

	public:
		BasicLoggerImpl() : m_Name("Logger"), m_Severity(Severity::Value::DefaultSeverity), m_Stream(std::cout) { ResetPattern(); }
		
		explicit BasicLoggerImpl(const std::string_view& name, typename Severity::Value severity = Severity::Value::DefaultSeverity, std::ostream& stream = std::cout)
			: m_Name(name), m_Severity(severity), m_Stream(stream)
			, preFormatBufferOutManager(64)
			, fullFormatBufferOutManager(64)
		{
			ResetPattern();
		}
		explicit BasicLoggerImpl(const std::string_view& name, const std::string_view& format, typename Severity::Value severity = Severity::Value::DefaultSeverity, std::ostream& stream = std::cout)
			: m_Name(name), m_Severity(severity), m_Stream(stream)
			, preFormatBufferOutManager(64)
			, fullFormatBufferOutManager(64)
		{
			SetPattern(format);
		}

	public:
		void SetSeverity(const SeverityValueType& severity)	{ m_Severity = severity; }
		void SetName(const std::string& name)				{ m_Name = name; }
		void SetName(std::string&& name)					{ m_Name = std::move(name); }
		void SetRealPattern(std::string_view pattern)		{ m_Pattern = pattern; }
		void SetRealPatternStrmv(std::string&& pattern)		{ m_Pattern = std::move(pattern); }
		void SetPattern(std::string_view pattern)			{ m_Pattern = "{color}"; m_Pattern += pattern; }
		void ResetPattern()									{ SetPattern("[{T:pattern='%h:%m:%s:%ms'}] {name} >> {data}"); }

	private:
		std::string m_Name;
		SeverityValueType m_Severity;
		std::ostream& m_Stream;
		std::string m_Pattern;
		FMT::Detail::DynamicBufferOutManager<char> preFormatBufferOutManager;
		FMT::Detail::DynamicBufferOutManager<char> fullFormatBufferOutManager;

	public:
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(const SeverityValueType& severity, const Format& format, Args&& ...args)
		{
			if (severity < m_Severity)
				return;

			FMT::Detail::BufferInProperties<char> preFormatBufferInProperties(m_Pattern);
			FMT::Detail::FormatInBufferOutManager(preFormatBufferOutManager, preFormatBufferInProperties, false, FORMAT_SV("name", m_Name), FORMAT_SV("data", LoggerManager::AddIndentInFormat(format)));
			FMT::Detail::BufferInProperties<char> fullFormatBufferInProperties(preFormatBufferOutManager.GetLastGeneratedStringView());
			FMT::Detail::FormatInBufferOutManager(fullFormatBufferOutManager, fullFormatBufferInProperties, true, std::forward<Args>(args)..., FORMAT_SV("color", severity));
			m_Stream.write(fullFormatBufferOutManager.GetBuffer(), fullFormatBufferOutManager.GetLastGeneratedDataSize());
			m_Stream.flush();
		}

		template<typename T>
		void Log(const SeverityValueType& severity, T&& t)
		{
			if (severity < m_Severity)
				return;

			FMT::Detail::BufferInProperties<char> fullFormatBufferInProperties(m_Pattern);
			FMT::Detail::FormatInBufferOutManager(fullFormatBufferOutManager, fullFormatBufferInProperties, true, FORMAT_SV("data", t), FORMAT_SV("color", severity), FORMAT_SV("name", m_Name));
			m_Stream.write(fullFormatBufferOutManager.GetBuffer(), fullFormatBufferOutManager.GetLastGeneratedDataSize());
			m_Stream.flush();
		}
	};
}
