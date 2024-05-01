#pragma once

#ifdef PROJECTCORE_PROFILING_ENABLE

#define PCP_PROFILE_FUNCTION()          ProjectCore::ProfilerManager::ScopeProfile profile##__LINE__(ProjectCore::ProfilerManager::Profiler::GetInstance(), __FUNCSIG__, "Function")
#define PCP_PROFILE_FUNCTION_FMT(...)   ProjectCore::ProfilerManager::ScopeProfile profile##__LINE__(ProjectCore::ProfilerManager::Profiler::GetInstance(), ProjectCore::ProfilerManager::FMT::FormatString(__VA_ARGS__), "Function")
#define PCP_SAVE_DEFAULT_PROFILER()     ProjectCore::ProfilerManager::ProfilerFactory::ToJson(ProjectCore::ProfilerManager::Profiler::GetInstance())

#else // PROJECTCORE_PROFILING_ENABLE

#define PCP_PROFILE_FUNCTION()
#define PCP_PROFILE_FUNCTION_FMT(...)
#define PCP_SAVE_DEFAULT_PROFILER()

#endif // PROJECTCORE_PROFILING_ENABLE
