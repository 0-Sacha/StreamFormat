#pragma once

#ifdef STREAMFORMAT_PROFILING_ENABLE

#define SFP_PROFILE_FUNCTION() stream::ProfilerManager::ScopeProfile profile##__LINE__(stream::ProfilerManager::Profiler::GetInstance(), __FUNCSIG__, "Function")
#define SFP_PROFILE_FUNCTION_FMT(...)                                                                                   \
    stream::ProfilerManager::ScopeProfile profile##__LINE__(stream::ProfilerManager::Profiler::GetInstance(), \
                                                                 stream::ProfilerManager::fmt::FormatString(__VA_ARGS__), "Function")
#define SFP_SAVE_DEFAULT_PROFILER() stream::ProfilerManager::ProfilerFactory::ToJson(stream::ProfilerManager::Profiler::GetInstance())

#else  // STREAMFORMAT_PROFILING_ENABLE

#define SFP_PROFILE_FUNCTION()
#define SFP_PROFILE_FUNCTION_FMT(...)
#define SFP_SAVE_DEFAULT_PROFILER()

#endif  // STREAMFORMAT_PROFILING_ENABLE
