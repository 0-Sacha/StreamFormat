#pragma once

#include "EngineCore/Core/Core.h"
#include "LoggerManager/LoggerManager.h"

namespace EngineCore::Instrumentation
{
	class Profiler;
	class ProfileResult;

	class ProfileResult {
	public:
		ProfileResult(Profiler& link, const std::string& name);
		ProfileResult(Profiler& link, std::string&& name);
		~ProfileResult();

	public:
		void Stop();
		const std::string& GetName() const 	{ return m_Name; } 
		double GetStart() const				{ return m_Start; }
		double GetDuration() const			{ return m_End - m_Start; }
		std::size_t GetTID() const			{ return m_TID; }

	private:
		Profiler& m_Link;
		std::string m_Name;
		double m_Start, m_End;
		std::size_t m_TID;
		bool m_IsStoped = false;
	};

	class Profiler {
	public:
		explicit Profiler(const std::string& name);
		~Profiler();

	public:
		void WriteProfile(const ProfileResult* const result);
		void WriteProfile(const std::string& name, const double start, const double dur, const std::size_t tid);
		void EndSession();

		inline const EngineCore::LoggerManager::BasicLogger& GetLogger() const		{ return m_Logger; }

	public:
		static Profiler& GetInstance()		{ static Profiler profiler("Profiler"); return profiler; }
		static double GetMicroseconds();

	private:
		void WriteHeaderFile();
		void WriteFooter();

	private:
		std::string m_Name;
		std::ofstream m_File;
		EngineCore::LoggerManager::BasicLogger m_Logger;
		double m_Start;
		bool m_IsEnd;
		size_t m_ProfilesCount;
	};
}
