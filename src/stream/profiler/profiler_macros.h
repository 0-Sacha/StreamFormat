#pragma once

#ifdef STREAMFORMAT_PROFILING_ENABLE

#define SFP_PROFILE_FUNCTION() stream::profiler::ScopeProfile profile##__LINE__(stream::profiler::Profiler::get_instance(), __FUNCSIG__, "Function")
#define SFP_PROFILE_FUNCTION_FMT(...)                                                                                   \
    stream::profiler::ScopeProfile profile##__LINE__(stream::profiler::Profiler::get_instance(), \
                                                                 stream::profiler::fmt::format_string(__VA_ARGS__), "Function")
#define SFP_SAVE_DEFAULT_PROFILER() stream::profiler::ProfilerFactory::to_json(stream::profiler::Profiler::get_instance())

#else  // STREAMFORMAT_PROFILING_ENABLE

#define SFP_PROFILE_FUNCTION()
#define SFP_PROFILE_FUNCTION_FMT(...)
#define SFP_SAVE_DEFAULT_PROFILER()

#endif  // STREAMFORMAT_PROFILING_ENABLE
