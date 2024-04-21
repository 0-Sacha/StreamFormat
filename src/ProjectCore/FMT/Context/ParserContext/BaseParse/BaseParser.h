#pragma once

#include "ProjectCore/FMT/Context/ParserContext/BasicParserContext.h"
#include "ParserForwarders.h"

namespace ProjectCore::FMT
{
    template<typename ParserContext>
    struct ParserType<typename ParserContext::DataType, ParserContext> {
        static inline void Parse(typename ParserContext::DataType&, ParserContext&) {
            throw Detail::FMTShouldNotEndHere{};
        }
    };

    template<typename ParserContext>
    struct ParserType<bool, ParserContext> {
        static void Parse(bool& t, ParserContext& context) {
            const auto& data = context.GetFormatData();

            if (!data.TrueValue) {
                switch (context.BufferIn().Get())
                {
                case 'T':
                case 't':
                    if (context.BufferIn().IsSameForward("True"))
                        t = true;
                
                case 'F':
                case 'f':
                    if (context.BufferIn().IsSameForward("False"))
                        t = false;
                
                default:
                    throw Detail::FMTParseError();
                }
                return;
            } else {
                if (context.BufferIn().IsEqualToForward('0'))            { t = false;    return; }
                else if (context.BufferIn().IsEqualToForward('1'))    { t = true;        return; }
            }

            throw Detail::FMTParseError();
        }
    };

    // Int Types
#ifdef FMT_USE_STD_INTEGER
    template<typename ParserContext>
    struct ParserType<std::int8_t, ParserContext> {
        static inline void Parse(std::int8_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::int8_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<std::int16_t, ParserContext> {
        static inline void Parse(std::int16_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::int16_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<std::int32_t, ParserContext> {
        static inline void Parse(std::int32_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::int32_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<std::int64_t, ParserContext> {
        static inline void Parse(std::int64_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::int64_t>, ParserContext>::Parse(t, context);
        }
    };
#else
    template<typename ParserContext>
    struct ParserType<signed char, ParserContext> {
        static inline void Parse(signed char& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<signed char>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<short, ParserContext> {
        static inline void Parse(short& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<short>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<int, ParserContext> {
        static inline void Parse(int& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<int>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<long, ParserContext> {
        static inline void Parse(long& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<long>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<long long, ParserContext> {
        static inline void Parse(long long& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<long long>, ParserContext>::Parse(t, context);
        }
    };
#endif

    // UInt Types
#ifdef FMT_USE_STD_INTEGER
    template<typename ParserContext>
    struct ParserType<std::uint8_t, ParserContext> {
        static inline void Parse(std::uint8_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::uint8_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<std::uint16_t, ParserContext> {
        static inline void Parse(std::uint16_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::uint16_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<std::uint32_t, ParserContext> {
        static inline void Parse(std::uint32_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::uint32_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<std::uint64_t, ParserContext> {
        static inline void Parse(std::uint64_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<std::uint64_t>, ParserContext>::Parse(t, context);
        }
    };
#else
    template<typename ParserContext>
    struct ParserType<unsigned char, ParserContext> {
        static inline void Parse(unsigned char& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<unsigned char>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<unsigned short, ParserContext> {
        static inline void Parse(unsigned short& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<unsigned short>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<unsigned int, ParserContext> {
        static inline void Parse(unsigned int& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<unsigned int>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<unsigned long, ParserContext> {
        static inline void Parse(unsigned long& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<unsigned long>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<unsigned long long, ParserContext> {
        static inline void Parse(unsigned long long& t, ParserContext& context) {
            ParserType<Detail::ForwardAsInt<unsigned long long>, ParserContext>::Parse(t, context);
        }
    };
#endif

    // Float Types
    template<typename ParserContext>
    struct ParserType<float, ParserContext> {
        static inline void Parse(float& t, ParserContext& context) {
            ParserType<Detail::ForwardAsFloat<float>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<double, ParserContext> {
        static inline void Parse(double& t, ParserContext& context) {
            ParserType<Detail::ForwardAsFloat<double>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<long double, ParserContext> {
        static inline void Parse(long double& t, ParserContext& context) {
            ParserType<Detail::ForwardAsFloat<long double>, ParserContext>::Parse(t, context);
        }
    };


    // Char Types
    template<typename ParserContext>
    struct ParserType<char, ParserContext> {
        static inline void Parse(char& t, ParserContext& context) {
            ParserType<Detail::ForwardAsChar<char>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<wchar_t, ParserContext> {
        static inline void Parse(wchar_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsChar<wchar_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<char8_t, ParserContext> {
        static inline void Parse(char8_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsChar<char8_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<char16_t, ParserContext> {
        static inline void Parse(char16_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsChar<char16_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<char32_t, ParserContext> {
        static inline void Parse(char32_t& t, ParserContext& context) {
            ParserType<Detail::ForwardAsChar<char32_t>, ParserContext>::Parse(t, context);
        }
    };

    template<std::size_t SIZE, typename ParserContext>
    struct ParserType<char[SIZE], ParserContext> {
        static inline void Parse(char(&t)[SIZE], ParserContext& context) {
            ParserType<Detail::ForwardAsCharArray<char, SIZE>, ParserContext>::Parse(t, context);
        }
    };
    template<std::size_t SIZE, typename ParserContext>
    struct ParserType<wchar_t[SIZE], ParserContext> {
        static inline void Parse(wchar_t(&t)[SIZE], ParserContext& context) {
            ParserType<Detail::ForwardAsCharArray<wchar_t, SIZE>, ParserContext>::Parse(t, context);
        }
    };
    template<std::size_t SIZE, typename ParserContext>
    struct ParserType<char8_t[SIZE], ParserContext> {
        static inline void Parse(char8_t(&t)[SIZE], ParserContext& context) {
            ParserType<Detail::ForwardAsCharArray<char8_t, SIZE>, ParserContext>::Parse(t, context);
        }
    };
    template<std::size_t SIZE, typename ParserContext>
    struct ParserType<char16_t[SIZE], ParserContext> {
        static inline void Parse(char16_t(&t)[SIZE], ParserContext& context) {
            ParserType<Detail::ForwardAsCharArray<char16_t, SIZE>, ParserContext>::Parse(t, context);
        }
    };
    template<std::size_t SIZE, typename ParserContext>
    struct ParserType<char32_t[SIZE], ParserContext> {
        static inline void Parse(char32_t(&t)[SIZE], ParserContext& context) {
            ParserType<Detail::ForwardAsCharArray<char32_t, SIZE>, ParserContext>::Parse(t, context);
        }
    };

    template<typename ParserContext>
    struct ParserType<char*, ParserContext> {
        static inline void Parse(char* const t, ParserContext& context) {
            ParserType<Detail::ForwardAsCharPointer<char>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<wchar_t*, ParserContext> {
        static inline void Parse(wchar_t* const t, ParserContext& context) {
            ParserType<Detail::ForwardAsCharPointer<wchar_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<char8_t*, ParserContext> {
        static inline void Parse(char8_t* const t, ParserContext& context) {
            ParserType<Detail::ForwardAsCharPointer<char8_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<char16_t*, ParserContext> {
        static inline void Parse(char16_t* const t, ParserContext& context) {
            ParserType<Detail::ForwardAsCharPointer<char16_t>, ParserContext>::Parse(t, context);
        }
    };
    template<typename ParserContext>
    struct ParserType<char32_t*, ParserContext> {
        static inline void Parse(char32_t* const t, ParserContext& context) {
            ParserType<Detail::ForwardAsCharPointer<char32_t>, ParserContext>::Parse(t, context);
        }
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //------------------ Pointer/Array of Type ------------------//

    template<typename ParserContext>
    struct ParserType<void*, ParserContext> {
        static inline void Parse(void*&, ParserContext&) {
            // FIXME
            // TODO
        }
    };

    template<typename T, typename ParserContext>
    struct ParserType<T*, ParserContext> {
        static inline void Parse(T*&, ParserContext&) {
            // FIXME
            // TODO
        }
    };

    template<std::size_t SIZE, typename T, typename ParserContext>
    struct ParserType<T[SIZE], ParserContext> {
        static inline void Parse(T (&)[SIZE], ParserContext&) {
            // FIXME
            // TODO        
        }
    };
}


