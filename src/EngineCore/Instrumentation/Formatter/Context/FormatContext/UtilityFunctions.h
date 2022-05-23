#pragma once


#include "BasicFormatContextParseImpl.h"

namespace EngineCore::Instrumentation::FMT {

	/////---------- Impl with as Format ----------//////

	namespace Detail {
		template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
		requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
		Detail::BasicFormatterMemoryBufferOutCopy<CharBuffer> FormatAndGetBufferOut(const Format& format, Args&& ...args) {
			BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(true, format, std::forward<Args>(args)...);
			context.SafeRun();
			context.BufferOut().PushEndChar();
			return context.BufferOut();
		}
	}


	template<typename Format = std::string_view, typename CharBuffer, std::size_t BUFFER_SIZE, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], const Format& format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(format, buffer, BUFFER_SIZE, std::forward<Args>(args)...);
		context.SafeRun();
		context.BufferOut().PushEndChar();
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer const buffer, const std::size_t bufferSize, const Format& format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(format, buffer, bufferSize, std::forward<Args>(args)...);
		context.SafeRun();
		context.BufferOut().PushEndChar();
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void CFilePrint(FILE* stream, const Format& format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(true, format, std::forward<Args>(args)...);
		context.SafeRun();

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void CFilePrintLn(FILE* stream, const Format& format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(true, format, std::forward<Args>(args)...);
		context.SafeRun();
		context.BufferOut().PushBack('\n');

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FilePrint(std::basic_ostream<CharBuffer>& stream, const Format format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(true, format, std::forward<Args>(args)...);
		context.SafeRun();

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, const Format& format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(true, format, std::forward<Args>(args)...);
		context.SafeRun();
		context.BufferOut().PushBack('\n');

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FormatInString(std::basic_string<CharBuffer>& str, const Format& format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(true, format, std::forward<Args>(args)...);
		context.SafeRun();
		context.BufferOut().PushEndChar();
		str = context.BufferOut().GetBuffer();
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	inline std::basic_string<CharBuffer> Formating(const Format& format, Args&& ...args) {
		BasicFormatContext<typename Detail::GetFmtBaseType<Format>::Type, CharBuffer, Args...> context(true, format, std::forward<Args>(args)...);
		context.SafeRun();
		context.BufferOut().PushEndChar();
		return context.BufferOut().GetBuffer();
	}


	/////---------- NO-FORMAT Impl except for string which are formatted for avoid {} ----------//////

	template<typename CharBuffer, size_t BUFFER_SIZE, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], T&& t) {
		BasicFormatContext<char, CharBuffer> context(std::basic_string_view<char>(nullptr, 0), buffer, BUFFER_SIZE);
		context.WriteType(t);
		context.BufferOut().PushEndChar();
	}

	template<typename CharBuffer, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer* const buffer, const std::size_t bufferSize, T&& t) {
		BasicFormatContext<char, CharBuffer> context(std::basic_string_view<char>(nullptr, 0), buffer, bufferSize);
		context.WriteType(t);
		context.BufferOut().PushEndChar();
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void CFilePrint(FILE* stream, T&& t) {
		BasicFormatContext<char, CharBuffer> context(true, std::basic_string_view<char>(nullptr, 0));
		context.WriteType(t);

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void CFilePrintLn(FILE* stream, T&& t) {
		BasicFormatContext<char, CharBuffer> context(true, std::basic_string_view<char>(nullptr, 0));
		context.WriteType(t);
		context.BufferOut().PushBack('\n');

		std::fwrite(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FilePrint(std::basic_ostream<CharBuffer>& stream, T&& t) {
		BasicFormatContext<char, CharBuffer> context(true, std::basic_string_view<char>(nullptr, 0));
		context.WriteType(t);

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, T&& t) {
		BasicFormatContext<char, CharBuffer> context(true, std::basic_string_view<char>(nullptr, 0));
		context.WriteType(t);
		context.BufferOut().PushBack('\n');

		stream.write(context.BufferOut().GetBuffer(), context.BufferOut().GetBufferCurrentSize());
		stream.flush();
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInString(std::basic_string<CharBuffer>& str, T&& t) {
		BasicFormatContext<char, CharBuffer> context(true, std::basic_string_view<char>(nullptr, 0));
		context.WriteType(t);
		context.BufferOut().PushEndChar();
		str = context.BufferOut().GetBuffer();
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	inline std::basic_string<CharBuffer> Formating(T&& t) {
		BasicFormatContext<char, CharBuffer> context(true, std::basic_string_view<char>(nullptr, 0));
		context.WriteType(t);
		context.BufferOut().PushEndChar();
		return context.BufferOut().GetBuffer();
	}

}