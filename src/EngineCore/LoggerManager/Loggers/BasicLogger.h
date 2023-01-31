#pragma once

#include "LoggerManager/Detail/Detail.h"

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
		{
			ResetPattern();
		}
		explicit BasicLoggerImpl(const std::string_view& name, const std::string_view& format, typename Severity::Value severity = Severity::Value::DefaultSeverity, std::ostream& stream = std::cout)
			: m_Name(name), m_Severity(severity), m_Stream(stream)
		{
			SetPattern(format);
		}

	public:
		void SetSeverity(const SeverityValueType& severity)	{ m_Severity = severity; }
		void SetName(const std::string& name)				{ m_Name = name; }
		void SetName(std::string&& name)					{ m_Name = std::move(name); }
		void SetPattern(std::string_view pattern)			{ m_Pattern = "{color:W}"; m_Pattern += pattern; }
		void ResetPattern()									{ SetPattern("[{T:pattern='%h:%m:%s:%ms'}] {name} >> {data}"); }

	private:
		std::string m_Name;
		SeverityValueType m_Severity;
		std::ostream& m_Stream;

		std::string m_Pattern;

	public:
		template<typename Format = std::string_view, typename ...Args>
		requires FMT::Detail::IsFmtConvertible<Format>::Value
		void Log(const SeverityValueType& severity, const Format& format, Args&& ...args)
		{
			if (severity < m_Severity)
				return;
			
			auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(m_Pattern), FORMAT_SV("name", m_Name), FORMAT_SV("data", LoggerManager::AddIndentInFormat(format)));
			FMT::FilePrintLn(m_Stream, static_cast<std::string_view>(*formatBuffer), std::forward<Args>(args)..., FORMAT_SV("color", severity));
		}

		template<typename T>
		void Log(const SeverityValueType& severity, T&& t) const
		{
			if (severity < m_Severity)
				return;

			FMT::FilePrintLn(m_Stream, m_Pattern, FORMAT_SV("data", t), FORMAT_SV("color", severity), FORMAT_SV("name", m_Name));
		}
	};
}
