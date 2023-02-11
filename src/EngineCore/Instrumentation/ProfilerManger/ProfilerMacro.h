#pragma once

#ifdef ENGINECORE_PROFILING_ENABLE

#define EC_PROFILE_FUNCTION()           EngineCore::Instrumentation::ScopeProfile profile##__LINE__(EngineCore::Instrumentation::Profiler::GetInstance(), __FUNCSIG__, "Function")
#define EC_PROFILE_FUNCTION_FMT(...)    EngineCore::Instrumentation::ScopeProfile profile##__LINE__(EngineCore::Instrumentation::Profiler::GetInstance(), EngineCore::Instrumentation::FMT::FormatString(__VA_ARGS__), "Function")
#define EC_SAVE_DEFAULT_PROFILER()		EngineCore::Instrumentation::ProfilerFactory::ToJson(EngineCore::Instrumentation::Profiler::GetInstance())

#else // ENGINECORE_PROFILING_ENABLE

#define EC_PROFILE_FUNCTION()								
#define EC_PROFILE_FUNCTION_FMT(...)								

#endif // ENGINECORE_PROFILING_ENABLE