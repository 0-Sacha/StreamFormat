#pragma once

#include "ProjectCore/FMT/Context/ParserContext/BasicParserContext.h"
#include "ParserForwarders.h"

namespace ProjectCore::FMT {

	template<typename ParserContext>
	struct ParserType<typename ParserContext::DataType, ParserContext> {
		static inline void Read(typename ParserContext::DataType&, ParserContext&) {
			// FIXME
		}
	};

	template<typename ParserContext>
	struct ParserType<bool, ParserContext> {
		static void Read(bool& t, ParserContext& context) {
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
				if (context.BufferIn().IsEqualToForward('0'))			{ t = false;	return; }
				else if (context.BufferIn().IsEqualToForward('1'))	{ t = true;		return; }
			}

			throw Detail::FMTParseError();
		}
	};

	// Int Types
	template<typename ParserContext>
	struct ParserType<std::int8_t, ParserContext> {
		static inline void Read(std::int8_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::int8_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<std::int16_t, ParserContext> {
		static inline void Read(std::int16_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::int16_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<std::int32_t, ParserContext> {
		static inline void Read(std::int32_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::int32_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<std::int64_t, ParserContext> {
		static inline void Read(std::int64_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::int64_t>, ParserContext>::Read(t, context);
		}
	};


	// UInt Types
	template<typename ParserContext>
	struct ParserType<std::uint8_t, ParserContext> {
		static inline void Read(std::uint8_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::uint8_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<std::uint16_t, ParserContext> {
		static inline void Read(std::uint16_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::uint16_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<std::uint32_t, ParserContext> {
		static inline void Read(std::uint32_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::uint32_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<std::uint64_t, ParserContext> {
		static inline void Read(std::uint64_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsInt<std::uint64_t>, ParserContext>::Read(t, context);
		}
	};


	// Float Types
	template<typename ParserContext>
	struct ParserType<float, ParserContext> {
		static inline void Read(float &t, ParserContext& context) {
			ParserType<Detail::ForwardAsFloat<float>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<double, ParserContext> {
		static inline void Read(double &t, ParserContext& context) {
			ParserType<Detail::ForwardAsFloat<double>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<long double, ParserContext> {
		static inline void Read(long double &t, ParserContext& context) {
			ParserType<Detail::ForwardAsFloat<long double>, ParserContext>::Read(t, context);
		}
	};


	// Char Types
	template<typename ParserContext>
	struct ParserType<char, ParserContext> {
		static inline void Read(char &t, ParserContext& context) {
			ParserType<Detail::ForwardAsChar<char>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<wchar_t, ParserContext> {
		static inline void Read(wchar_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsChar<wchar_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<char16_t, ParserContext> {
		static inline void Read(char16_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsChar<char16_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<char32_t, ParserContext> {
		static inline void Read(char32_t &t, ParserContext& context) {
			ParserType<Detail::ForwardAsChar<char32_t>, ParserContext>::Read(t, context);
		}
	};

	template<std::size_t SIZE, typename ParserContext>
	struct ParserType<char[SIZE], ParserContext> {
		static inline void Read(char(&t)[SIZE], ParserContext& context) {
			ParserType<Detail::ForwardAsCharArray<char, SIZE>, ParserContext>::Read(t, context);
		}
	};
	template<std::size_t SIZE, typename ParserContext>
	struct ParserType<wchar_t[SIZE], ParserContext> {
		static inline void Read(wchar_t(&t)[SIZE], ParserContext& context) {
			ParserType<Detail::ForwardAsCharArray<wchar_t, SIZE>, ParserContext>::Read(t, context);
		}
	};
	template<std::size_t SIZE, typename ParserContext>
	struct ParserType<char16_t[SIZE], ParserContext> {
		static inline void Read(char16_t(&t)[SIZE], ParserContext& context) {
			ParserType<Detail::ForwardAsCharArray<char16_t, SIZE>, ParserContext>::Read(t, context);
		}
	};
	template<std::size_t SIZE, typename ParserContext>
	struct ParserType<char32_t[SIZE], ParserContext> {
		static inline void Read(char32_t(&t)[SIZE], ParserContext& context) {
			ParserType<Detail::ForwardAsCharArray<char32_t, SIZE>, ParserContext>::Read(t, context);
		}
	};

	template<typename ParserContext>
	struct ParserType<char*, ParserContext> {
		static inline void Read(char* const t, ParserContext& context) {
			ParserType<Detail::ForwardAsCharPointer<char>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<wchar_t*, ParserContext> {
		static inline void Read(wchar_t* const t, ParserContext& context) {
			ParserType<Detail::ForwardAsCharPointer<wchar_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<char16_t*, ParserContext> {
		static inline void Read(char16_t* const t, ParserContext& context) {
			ParserType<Detail::ForwardAsCharPointer<char16_t>, ParserContext>::Read(t, context);
		}
	};
	template<typename ParserContext>
	struct ParserType<char32_t*, ParserContext> {
		static inline void Read(char32_t* const t, ParserContext& context) {
			ParserType<Detail::ForwardAsCharPointer<char32_t>, ParserContext>::Read(t, context);
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//------------------ Pointer/Array of Type ------------------//

	template<typename ParserContext>
	struct ParserType<void*, ParserContext> {
		static inline void Read(void*&, ParserContext&) {
			// FIXME
			// TODO
		}
	};

	template<typename T, typename ParserContext>
	struct ParserType<T*, ParserContext> {
		static inline void Read(T*&, ParserContext&) {
			// FIXME
			// TODO
		}
	};

	template<std::size_t SIZE, typename T, typename ParserContext>
	struct ParserType<T[SIZE], ParserContext> {
		static inline void Read(T (&)[SIZE], ParserContext&) {
			// FIXME
			// TODO		
		}
	};
}


