#pragma once

#include "BasicFormatterContext.h"
#include "BasicFormatterContextCoreImpl.h"
#include "BasicFormatterContextParseImpl.h"

#include "FMT/Detail/Buffer/BasicBufferOut.h"

namespace EngineCore::FMT {

	/////---------- Impl with as Format ----------//////

	namespace Detail {
		template<typename Format = std::string_view, typename CharBuffer = typename GetFmtBaseType<Format>::Type, typename ...Args>
		requires IsFmtConvertible<Format>::Value && IsCharType<CharBuffer>::Value
		BasicFormatterMemoryBufferOutCopy<CharBuffer> FormatAndGetBufferOut(const Format& format, Args&& ...args) {
			using ContextType = Context::BasicFormatterContext<typename GetFmtBaseType<Format>::Type, CharBuffer>;
			auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
			ContextType context(format, nullptr, 256, &contextArgsInterface);
			context.SafeRun();
			context.BufferOut().PushEndChar();
			return context.BufferOut();
		}

		template<typename CharBuffer = char, typename T>
		Detail::BasicFormatterMemoryBufferOutCopy<CharBuffer> FormatAndGetBufferOut(T&& t) {
			Context::BasicFormatterContext<char, CharBuffer> context(std::basic_string_view<char>(nullptr, 0), nullptr, 0);
			context.WriteType(t);
			context.BufferOut().PushEndChar();
			return context.BufferOut();
		}
	}


	template<typename Format = std::string_view, typename CharBuffer, std::size_t BUFFER_SIZE, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value && Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], const Format& format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, buffer, BUFFER_SIZE, &contextArgsInterface);
		context.SafeRun();
		context.BufferOut().PushEndChar();
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer const buffer, const std::size_t bufferSize, const Format& format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, buffer, bufferSize, &contextArgsInterface);
		context.SafeRun();
		context.BufferOut().PushEndChar();
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void CFilePrint(FILE* stream, const Format& format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, nullptr, 256, &contextArgsInterface);
		context.SafeRun(); 

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void CFilePrintLn(FILE* stream, const Format& format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, nullptr, 256, &contextArgsInterface);
		context.SafeRun();
		context.BufferOut().PushBack('\n');

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FilePrint(std::basic_ostream<CharBuffer>& stream, const Format format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, nullptr, 256, &contextArgsInterface);
		context.SafeRun();

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, const Format& format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, nullptr, 256, &contextArgsInterface);
		context.SafeRun();
		context.BufferOut().PushBack('\n');

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FormatInString(std::basic_string<CharBuffer>& str, const Format& format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, nullptr, 256, &contextArgsInterface);
		context.SafeRun();
		context.BufferOut().PushEndChar();
		str = context.BufferOut().GetBuffer();
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	inline std::basic_string<CharBuffer> FormatString(const Format& format, Args&& ...args) {
		using ContextType = Context::BasicFormatterContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer>;
		auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		ContextType context(format, nullptr, 256, &contextArgsInterface);
		context.SafeRun();
		context.BufferOut().PushEndChar();
		return context.BufferOut().GetBuffer();
	}


	/////---------- NO-FORMAT Impl except for string which are formatted for avoid {} ----------//////

	template<typename CharBuffer, size_t BUFFER_SIZE, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], T&& t) {
		Context::BasicFormatterContext<char, CharBuffer> context(std::basic_string_view<char>(nullptr, 0), buffer, BUFFER_SIZE);
		context.WriteType(t);
		context.BufferOut().PushEndChar();
	}

	template<typename CharBuffer, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer* const buffer, const std::size_t bufferSize, T&& t) {
		Context::BasicFormatterContext<char, CharBuffer> context(std::basic_string_view<char>(nullptr, 0), buffer, bufferSize);
		context.WriteType(t);
		context.BufferOut().PushEndChar();
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void CFilePrint(FILE* stream, T&& t) {
		using ContextType = Context::BasicFormatterContext<char, CharBuffer>;
		Detail::EmptyContextArgsTupleInterface<ContextType> contextArgsInterface;
		ContextType context(std::basic_string_view<char>(nullptr, 0), nullptr, 0, &contextArgsInterface);
		context.WriteType(t);

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void CFilePrintLn(FILE* stream, T&& t) {
		using ContextType = Context::BasicFormatterContext<char, CharBuffer>;
		Detail::EmptyContextArgsTupleInterface<ContextType> contextArgsInterface;
		ContextType context(std::basic_string_view<char>(nullptr, 0), nullptr, 0, &contextArgsInterface);
		context.WriteType(t);
		context.BufferOut().PushBack('\n');

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FilePrint(std::basic_ostream<CharBuffer>& stream, T&& t) {
		using ContextType = Context::BasicFormatterContext<char, CharBuffer>;
		Detail::EmptyContextArgsTupleInterface<ContextType> contextArgsInterface;
		ContextType context(std::basic_string_view<char>(nullptr, 0), nullptr, 0, &contextArgsInterface);
		context.WriteType(t);

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, T&& t) {
		using ContextType = Context::BasicFormatterContext<char, CharBuffer>;
		Detail::EmptyContextArgsTupleInterface<ContextType> contextArgsInterface;
		ContextType context(std::basic_string_view<char>(nullptr, 0), nullptr, 0, &contextArgsInterface);
		context.WriteType(t);
		context.BufferOut().PushBack('\n');

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInString(std::basic_string<CharBuffer>& str, T&& t) {
		using ContextType = Context::BasicFormatterContext<char, CharBuffer>;
		Detail::EmptyContextArgsTupleInterface<ContextType> contextArgsInterface;
		ContextType context(std::basic_string_view<char>(nullptr, 0), nullptr, 0, &contextArgsInterface);
		context.WriteType(t);
		context.BufferOut().PushEndChar();
		str = context.BufferOut().GetBuffer();
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	inline std::basic_string<CharBuffer> FormatString(T&& t) {
		using ContextType = Context::BasicFormatterContext<char, CharBuffer>;
		Detail::EmptyContextArgsTupleInterface<ContextType> contextArgsInterface;
		ContextType context(std::basic_string_view<char>(nullptr, 0), nullptr, 0, &contextArgsInterface);
		context.WriteType(t);
		context.BufferOut().PushEndChar();
		return context.BufferOut().GetBuffer();
	}
}
