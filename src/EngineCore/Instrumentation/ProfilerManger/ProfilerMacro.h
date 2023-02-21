#pragma once

#ifdef ENGINECORE_PROFILING_ENABLE

#define ECP_PROFILE_FUNCTION()           EngineCore::Instrumentation::ScopeProfile profile##__LINE__(EngineCore::Instrumentation::Profiler::GetInstance(), __FUNCSIG__, "Function")
#define ECP_PROFILE_FUNCTION_FMT(...)    EngineCore::Instrumentation::ScopeProfile profile##__LINE__(EngineCore::Instrumentation::Profiler::GetInstance(), EngineCore::Instrumentation::FMT::FormatString(__VA_ARGS__), "Function")
#define ECP_SAVE_DEFAULT_PROFILER()		EngineCore::Instrumentation::ProfilerFactory::ToJson(EngineCore::Instrumentation::Profiler::GetInstance())

#else // ENGINECORE_PROFILING_ENABLE

#define ECP_PROFILE_FUNCTION()								
#define ECP_PROFILE_FUNCTION_FMT(...)								
#define ECP_SAVE_DEFAULT_PROFILER()

#endif // ENGINECORE_PROFILING_ENABLE