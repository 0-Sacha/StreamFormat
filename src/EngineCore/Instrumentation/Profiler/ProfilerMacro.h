#pragma once

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