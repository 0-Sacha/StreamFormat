#pragma once

#include "FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<typename FormatterContext::FormatSpecifierType, FormatterContext> {
		static void Write(const typename FormatterContext::FormatSpecifierType& specifier, FormatterContext& context) {
			if(specifier.ValueIsText)
				context.SubContext("{ '{}', '{}' }", specifier.Name, specifier.ValueAsText);
			else
				context.SubContext("{ '{}', '{}' }", specifier.Name, specifier.ValueAsNumber);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<typename FormatterContext::DataType, FormatterContext> {
		static void Write(const typename FormatterContext::DataType& t, FormatterContext& context) {
			context.SubContext("{:C:red}", "Missing '{' or '}' because currently the format data is used as a parameter");
		}
	};



	// Bool
	template<typename FormatterContext>
	struct FormatterType<bool, FormatterContext> {
		static void Write(const bool t, FormatterContext& context) {
			if (!context.GetFormatData().TrueValue) {
				if (t == true)	context.Print("True");
				else			context.Print("False");
			} else {
				if (t == true)	context.BufferOut().PushBack('1');
				else			context.BufferOut().PushBack('0');
			}
		}
	};

	// Int basic
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsInt<T>, FormatterContext> {
		static inline void Write(const T t, FormatterContext& context) {
			context.BufferOut().WriteIntFormatData(t, context.GetFormatData());
		}
	};

	// UInt basic
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsUInt<T>, FormatterContext> {
		static inline void Write(const T t, FormatterContext& context) {
			context.BufferOut().WriteUIntFormatData(t, context.GetFormatData());
		}
	};

	// Float basic
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsFloat<T>, FormatterContext> {
		static void Write(const T t, FormatterContext& context) {
			context.BufferOut().WriteFloatFormatData(t, context.GetFormatData());
		}
	};

	// Char type
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsChar<T>, FormatterContext> {
		inline static void Write(const T t, FormatterContext& context) {
			context.BufferOut().PushBack(t);
		}
	};

	template<typename T, std::size_t SIZE, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsCharArray<T, SIZE>, FormatterContext> {
		static void Write(const T(&t)[SIZE], FormatterContext& context) {
			const auto& data = context.GetFormatData();

			auto begin = context.GetFormatData().GetSpecifierAsNumber("begin", 0);
			auto size = context.GetFormatData().GetSpecifierAsNumber("size", SIZE - begin);

			if (data.TrueValue)	context.BufferOut().PushBack('\"');
			context.BufferOut().WriteCharPtr(t + begin, size);
			if (data.TrueValue)	context.BufferOut().PushBack('\"');
		}
	};

	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsCharPt<T>, FormatterContext> {
		static void Write(const T* t, FormatterContext& context) {
			if (t == nullptr)
				return context.Print(context.GetFormatData().GetSpecifierAsText("null", "[nullptr string]"));

			const auto& data = context.GetFormatData();

			if (data.TrueValue)										context.BufferOut().PushBack('\"');

			auto begin = data.GetSpecifierAsNumber("begin", 0);
			auto size = data.GetSpecifierAsNumber("size", Detail::FORMAT_DATA_NOT_SPECIFIED);

			if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)	context.Print(t + begin, size);
			else											context.PrintCharPtr(t + begin);

			if (data.TrueValue)										context.BufferOut().PushBack('\"');
		}
	};


	// Int basic
	template<typename FormatterContext>
	struct FormatterType<std::int8_t, FormatterContext> {
		static inline void Write(const std::int8_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsInt<std::int8_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<std::int16_t, FormatterContext> {
		static inline void Write(const std::int16_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsInt<std::int16_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<std::int32_t, FormatterContext> {
		static inline void Write(const std::int32_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsInt<std::int32_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<std::int64_t, FormatterContext> {
		static inline void Write(const std::int64_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsInt<std::int64_t>, FormatterContext>::Write(t, context);
		}
	};


	// UInt basic
	template<typename FormatterContext>
	struct FormatterType<std::uint8_t, FormatterContext> {
		static inline void Write(const std::uint8_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsUInt<std::uint8_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<std::uint16_t, FormatterContext> {
		static inline void Write(const std::uint16_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsUInt<std::uint16_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<std::uint32_t, FormatterContext> {
		static inline void Write(const std::uint32_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsUInt<std::uint32_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<std::uint64_t, FormatterContext> {
		static inline void Write(const std::uint64_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsUInt<std::uint64_t>, FormatterContext>::Write(t, context);
		}
	};


	// Float basic

	template<typename FormatterContext>
	struct FormatterType<float, FormatterContext> {
		static inline void Write(const float t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsFloat<float>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<double, FormatterContext> {
		static inline void Write(const double t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsFloat<double>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<long double, FormatterContext> {
		static inline void Write(const long double t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsFloat<long double>, FormatterContext>::Write(t, context);
		}
	};



	
	template<typename FormatterContext>
	struct FormatterType<char, FormatterContext> {
		inline static void Write(const char t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsChar<char>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<wchar_t, FormatterContext> {
		inline static void Write(const wchar_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsChar<wchar_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<char8_t, FormatterContext> {
		inline static void Write(const char8_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsChar<char8_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<char16_t, FormatterContext> {
		inline static void Write(const char16_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsChar<char16_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<char32_t, FormatterContext> {
		inline static void Write(const char32_t t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsChar<char32_t>, FormatterContext>::Write(t, context);
		}
	};

	template<std::size_t SIZE, typename FormatterContext>
	struct FormatterType<char [SIZE], FormatterContext> {
		static void Write(const char (&t)[SIZE], FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharArray<char, SIZE>, FormatterContext>::Write(t, context);
		}
	};
	template<std::size_t SIZE, typename FormatterContext>
	struct FormatterType<wchar_t[SIZE], FormatterContext> {
		static void Write(const wchar_t(&t)[SIZE], FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharArray<wchar_t, SIZE>, FormatterContext>::Write(t, context);
		}
	};
	template<std::size_t SIZE, typename FormatterContext>
	struct FormatterType<char8_t[SIZE], FormatterContext> {
		static void Write(const char8_t(&t)[SIZE], FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharArray<char8_t, SIZE>, FormatterContext>::Write(t, context);
		}
	};
	template<std::size_t SIZE, typename FormatterContext>
	struct FormatterType<char16_t[SIZE], FormatterContext> {
		static void Write(const char16_t(&t)[SIZE], FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharArray<char16_t, SIZE>, FormatterContext>::Write(t, context);
		}
	};
	template<std::size_t SIZE, typename FormatterContext>
	struct FormatterType<char32_t[SIZE], FormatterContext> {
		static void Write(const char32_t(&t)[SIZE], FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharArray<char32_t, SIZE>, FormatterContext>::Write(t, context);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<char*, FormatterContext> {
		static void Write(const char* const t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharPt<char>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<wchar_t*, FormatterContext> {
		static void Write(const wchar_t* const t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharPt<wchar_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<char8_t*, FormatterContext> {
		static void Write(const char8_t* const t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharPt<char8_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<char16_t*, FormatterContext> {
		static void Write(const char16_t* const t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharPt<char16_t>, FormatterContext>::Write(t, context);
		}
	};
	template<typename FormatterContext>
	struct FormatterType<char32_t*, FormatterContext> {
		static void Write(const char32_t* const t, FormatterContext& context) {
			FormatterType<Detail::ForwardAsCharPt<char32_t>, FormatterContext>::Write(t, context);
		}
	};



	//------------------ Pointer/Array of Type ------------------//

	template<typename FormatterContext>
	struct FormatterType<void*, FormatterContext>
	{
		static void Write(const void* const t, FormatterContext& context) {
			if (t == nullptr)	context.Print("nullptr");
			else				context.SubContext("{:X,=,U}", (std::size_t)t);
		}
	};

	template<typename T, typename FormatterContext>
	struct FormatterType<T*, FormatterContext>
	{
		static void Write(const T* const t, FormatterContext& context) {

			if (t == nullptr)
				return context.Print(context.GetFormatData().GetSpecifierAsText("null", "nullptr"));

			auto size = context.GetFormatData().GetSpecifierAsNumber("size", Detail::FORMAT_DATA_NOT_SPECIFIED);

			if(size == Detail::FORMAT_DATA_NOT_SPECIFIED) {
				if (context.GetFormatData().TrueValue)
					context.SubContext("{} -> {:{}}", (void*)t, *t, context.ForwardFormatData());
				else
					context.WriteType(*t);
				return;
			}

			context.BufferOut().WriteStringView(context.GetFormatData().GetSpecifierAsText("begin", STDEnumerableUtility::DefaultBegin));

			const auto& join = context.GetFormatData().GetSpecifierAsText("join", STDEnumerableUtility::DefaultJoin);

			auto beginValue = context.GetFormatData().GetSpecifierAsNumber("begin", 0);

			bool first = true;
			const T* begin	= t + beginValue;
			const T* end	= begin + size;

			while (begin < end) {
				if (first)	first = false;
				else		context.PrintIndent(join);
				context.WriteType(*begin++);
			}

			context.BufferOut().WriteStringView(context.GetFormatData().GetSpecifierAsText("end", STDEnumerableUtility::DefaultEnd));
		}
	};

	template<std::size_t SIZE, typename T, typename FormatterContext>
	struct FormatterType<T[SIZE], FormatterContext>
	{
		static void Write(T const (&t)[SIZE], FormatterContext& context) {

			context.BufferOut().WriteStringView(context.GetFormatData().GetSpecifierAsText("begin", STDEnumerableUtility::DefaultBegin));

			const auto& join = context.GetFormatData().GetSpecifierAsText("join", STDEnumerableUtility::DefaultJoin);

			bool first = true;
			std::size_t beginValue = context.GetFormatData().GetSpecifierAsNumber("begin", 0);
			const T* begin 	= t + beginValue;
			const T* end  	= begin + context.GetFormatData().GetSpecifierAsNumber("size", SIZE - beginValue);

			while(begin < end) {
				if (first)	first = false;
				else		context.PrintIndent(join);
				context.WriteType(*begin++);
			}

			context.BufferOut().WriteStringView(context.GetFormatData().GetSpecifierAsText("end", STDEnumerableUtility::DefaultEnd));
		}
	};
}