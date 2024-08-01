#pragma once

#ifdef STREAMFORMAT_PROFILING_ENABLE

#define PCP_PROFILE_FUNCTION() StreamFormat::ProfilerManager::ScopeProfile profile##__LINE__(StreamFormat::ProfilerManager::Profiler::GetInstance(), __FUNCSIG__, "Function")
#define PCP_PROFILE_FUNCTION_FMT(...)                                                                                   \
    StreamFormat::ProfilerManager::ScopeProfile profile##__LINE__(StreamFormat::ProfilerManager::Profiler::GetInstance(), \
                                                                 StreamFormat::ProfilerManager::FMT::FormatString(__VA_ARGS__), "Function")
#define PCP_SAVE_DEFAULT_PROFILER() StreamFormat::ProfilerManager::ProfilerFactory::ToJson(StreamFormat::ProfilerManager::Profiler::GetInstance())

#else  // STREAMFORMAT_PROFILING_ENABLE

#define PCP_PROFILE_FUNCTION()
#define PCP_PROFILE_FUNCTION_FMT(...)
#define PCP_SAVE_DEFAULT_PROFILER()

#endif  // STREAMFORMAT_PROFILING_ENABLE
