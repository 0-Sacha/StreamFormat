#pragma once

#include "EngineCore/Core.h"
#include "EngineCore/Instrumentation/LogSystem/LogSystem.h"

namespace EngineCore::Instrumentation {

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

		inline const EngineCore::Instrumentation::LogSystem& GetLogger() const		{ return m_Logger; }

	public:
		static Profiler& GetInstance()		{ static Profiler profiler("Profiler"); return profiler; }
		static double GetMicroseconds();

	private:
		void WriteHeaderFile();
		void WriteFooter();

	private:
		std::string m_Name;
		std::ofstream m_File;
		EngineCore::Instrumentation::LogSystem m_Logger;
		double m_Start;
		bool m_IsEnd;
		size_t m_ProfilesCount;
	};
}


#ifdef ENGINECORE_PROFILING_ENABLE

#define PROFILER_FUNCSIG_AUTO(profiler)								EngineCore::Instrumentation::ProfileResult profile##__LINE__(profiler, __FUNCSIG__)
#define PROFILER_DEFAULT_FUNCSIG_AUTO()								PROFILER_FUNCSIG_AUTO(EngineCore::Instrumentation::Profiler::GetInstance())

#define PROFILER_FUNC_AUTO(profiler)								EngineCore::Instrumentation::ProfileResult profile##__LINE__(profiler, __FUNCTION__)
#define PROFILER_DEFAULT_FUNC_AUTO()								PROFILER_FUNC_AUTO(EngineCore::Instrumentation::Profiler::GetInstance())

#define PROFILER_FUNC_FMT(profile, profiler, ...)					PROFILER_FUNC_NAME(EngineCore::Instrumentation::FMT::FormatString(__VA_ARGS__), profile, profiler);
#define PROFILER_DEFAULT_FUNC_FMT(profile, ...)						PROFILER_FUNC_FMT(profile, EngineCore::Instrumentation::Profiler::GetInstance(), __VA_ARGS__);

// ----------- CTools ----------- //

#define PROFILER_FUNC_NAME(name, profile, profiler)					EngineCore::Instrumentation::ProfileResult profile(profiler, name)
#define PROFILER_FUNC(profile, profiler)							PROFILER_FUNC_NAME(#profile, profile, profiler)

#define PROFILER_DEFAULT_FUNC_NAME(name, profile)					PROFILER_FUNC_NAME(name, profile, EngineCore::Instrumentation::Profiler::GetInstance())
#define PROFILER_DEFAULT_FUNC(profile)								PROFILER_DEFAULT_FUNC_NAME(#profile, profile)

#define PROFILER_CONSTRUCT(profiler)								EngineCore::Instrumentation::Profiler profiler(#profiler);
#define PROFILER_END(profiler)										profiler.EndSession()

#else // PROFILING_ENABLE

#define PROFILER_FUNC_AUTO(profiler)								
#define PROFILER_FUNC_AUTO(profiler)								
#define PROFILER_DEFAULT_FUNC_AUTO()								

#define PROFILER_FUNC_FMT(profile, profiler, fmt, ...)				
#define PROFILER_DEFAULT_FUNC_FMT(profile, fmt, ...)				

// ----------- CTools ----------- //

#define PROFILER_FUNC_NAME(name, profile, profiler)					
#define PROFILER_FUNC(profile, profiler)							

#define PROFILER_DEFAULT_FUNC_NAME(name, profile)					
#define PROFILER_DEFAULT_FUNC(profile)								

#define PROFILER_CONSTRUCT(profiler)	
#define PROFILER_END(profiler)										

#endif // PROFILING_ENABLE