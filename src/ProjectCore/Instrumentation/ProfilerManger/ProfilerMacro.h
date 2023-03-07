#pragma once

#ifdef PROJECTCORE_PROFILING_ENABLE

#define PCP_PROFILE_FUNCTION()           ProjectCore::Instrumentation::ScopeProfile profile##__LINE__(ProjectCore::Instrumentation::Profiler::GetInstance(), __FUNCSIG__, "Function")
#define PCP_PROFILE_FUNCTION_FMT(...)    ProjectCore::Instrumentation::ScopeProfile profile##__LINE__(ProjectCore::Instrumentation::Profiler::GetInstance(), ProjectCore::Instrumentation::FMT::FormatString(__VA_ARGS__), "Function")
#define PCP_SAVE_DEFAULT_PROFILER()		ProjectCore::Instrumentation::ProfilerFactory::ToJson(ProjectCore::Instrumentation::Profiler::GetInstance())

#else // PROJECTCORE_PROFILING_ENABLE

#define PCP_PROFILE_FUNCTION()								
#define PCP_PROFILE_FUNCTION_FMT(...)								
#define PCP_SAVE_DEFAULT_PROFILER()

#endif // PROJECTCORE_PROFILING_ENABLE