#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"
#include "ProjectCore/Tools/MapMacro.h"

#define PROJECTCORE_FORMATTER_DECLARED
namespace ProjectCore::FMT
{
    template<typename T, typename FormatterContext = Context::BasicFormatterContext<char, char>>
    struct FormatterType
    {
        static inline void Format(const T&, FormatterContext& context) {
#ifdef UNKOWN_TYPE_MESSAGE
            context.SubContextArrayFMT("({C:red}FMT unknow type: {})", typeid(T).name());
#endif
#ifdef UNKOWN_TYPE_THROW
            throw Detail::FMTShouldNotEndHere{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            throw Detail::FMTShouldNotEndHere{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
           PROJECTCORE_DEBUGBREAK();
#endif
        }
    };
}

#define PROJECTCORE_INTERNAL_ADDVALUE(x) value.x
#define PROJECTCORE_AUTO_FORMATTER_X(Type, fmt, ...)    template<typename FormatterContext>\
                                                        struct ProjectCore::FMT::FormatterType<Type, FormatterContext> {\
                                                            static void Format(const Type& value, FormatterContext& context) {\
                                                                context.SubContextArrayFMT(fmt, FOR_EACH(PROJECTCORE_INTERNAL_ADDVALUE, __VA_ARGS__));\
                                                            }\
                                                        };

#define PROJECTCORE_AUTO_FORMATTER(Type, fmt, ...)  template<typename FormatterContext>\
                                                    struct ProjectCore::FMT::FormatterType<Type, FormatterContext> {\
                                                        static void Format(const Type& value, FormatterContext& context) {\
                                                            context.SubContextArrayFMT(fmt, __VA_ARGS__);\
                                                        }\
                                                    };

#define PROJECTCORE_AUTO_FORMATTER_T(Type, fmt, ...)    template<typename FormatterContext>\
                                                        struct ProjectCore::FMT::FormatterType<Type, FormatterContext> {\
                                                            static void Format(const Type&, FormatterContext& context) {\
                                                                context.SubContextArrayFMT(fmt, __VA_ARGS__);\
                                                            }\
                                                        };

