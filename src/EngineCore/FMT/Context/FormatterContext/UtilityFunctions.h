#pragma once

#include "BasicFormatterContext.h"
#include "BasicFormatterContextCoreImpl.h"
#include "BasicFormatterContextParseImpl.h"

namespace EngineCore::FMT {

	/////---------- Impl with as Format ----------//////

	namespace Detail {
		template<typename Format = std::string_view, typename CharBuffer = typename GetFmtBaseType<Format>::Type, typename ...Args>
		requires IsFmtConvertible<Format>::Value && IsCharType<CharBuffer>::Value
		void FormatInBufferManager(Detail::BasicBufferManager<CharBuffer>& bufferManager, bool newline, const Format& formatData, Args&& ...args)
		{
			using ContextType = Context::BasicFormatterContext<typename GetFmtBaseType<Format>::Type, CharBuffer>;
			ContextType context(bufferManager);

			auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
			Detail::FMTFormatBuffer<typename GetFmtBaseType<Format>::Type> format(formatData);
			context.Run(format, &contextArgsInterface);
			if (newline)
				context.BufferOut().PushBack('\n');
		}

		template<typename CharBuffer = char, typename T>
		void FormatInBufferManager(Detail::BasicBufferManager<CharBuffer>& bufferManager, bool newline, T&& t)
		{
			Context::BasicFormatterContext<char, CharBuffer> context(bufferManager);
			context.WriteType(t);
			if (newline)
				context.BufferOut().PushBack('\n');
		}

		template<typename Format = std::string_view, typename CharBuffer = typename GetFmtBaseType<Format>::Type, typename ...Args>
		requires IsFmtConvertible<Format>::Value && IsCharType<CharBuffer>::Value
		std::shared_ptr<Detail::BasicBufferManager<typename GetFmtBaseType<Format>::Type>> FormatAndGetBufferOut(const Format& format, Args&& ...args)
		{
			std::shared_ptr<Detail::BasicBufferManager<typename GetFmtBaseType<Format>::Type>> bufferManager = std::make_shared<Detail::DynamicBufferManager<typename GetFmtBaseType<Format>::Type>>(128);
			FormatInBufferManager(*bufferManager, false, format, std::forward<Args>(args)...);
			return bufferManager;
		}

		template<typename CharBuffer = char, typename T>
		std::shared_ptr<Detail::BasicBufferManager<CharBuffer>> FormatAndGetBufferOut(T&& t)
		{
			std::shared_ptr<Detail::BasicBufferManager<CharBuffer>> bufferManager = std::make_shared<Detail::DynamicBufferManager<CharBuffer>>(128);
			FormatInBufferManager(*bufferManager, false, std::forward<T>(t));
			return bufferManager;
		}
	}


	template<typename Format = std::string_view, typename CharBuffer, std::size_t BUFFER_SIZE, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value && Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], const Format& format, Args&& ...args) {
		Detail::GivenBufferManager<CharBuffer> bufferManager(buffer, BUFFER_SIZE);
		Detail::FormatInBufferManager(bufferManager, false, format, std::forward<Args>(args)...);
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer const buffer, const std::size_t bufferSize, const Format& format, Args&& ...args) {
		Detail::GivenBufferManager<CharBuffer> bufferManager(buffer, bufferSize);
		Detail::FormatInBufferManager(bufferManager, false, format, std::forward<Args>(args)...);
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void CFilePrint(FILE* stream, const Format& format, Args&& ...args) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(256);
		Detail::FormatInBufferManager(bufferManager, false, format, std::forward<Args>(args)...);

		std::fwrite(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void CFilePrintLn(FILE* stream, const Format& format, Args&& ...args) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(256);
		Detail::FormatInBufferManager(bufferManager, true, format, std::forward<Args>(args)...);

		std::fwrite(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FilePrint(std::basic_ostream<CharBuffer>& stream, const Format format, Args&& ...args) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(256);
		Detail::FormatInBufferManager(bufferManager, false, format, std::forward<Args>(args)...);

		stream.write(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
		stream.flush();
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, const Format& format, Args&& ...args) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(256);
		Detail::FormatInBufferManager(bufferManager, true, format, std::forward<Args>(args)...);

		stream.write(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
		stream.flush();
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	void FormatInString(std::basic_string<CharBuffer>& str, const Format& format, Args&& ...args) {
		// TODO : optimization
		Detail::DynamicBufferManager<CharBuffer> bufferManager(256);
		Detail::FormatInBufferManager(bufferManager, false, format, std::forward<Args>(args)...);
		str = std::string(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::GetFmtBaseType<Format>::Type, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsCharType<CharBuffer>::Value
	inline std::basic_string<CharBuffer> FormatString(const Format& format, Args&& ...args) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(256);
		Detail::FormatInBufferManager(bufferManager, false, format, std::forward<Args>(args)...);
		return std::string(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
	}


	/////---------- NO-FORMAT Impl except for string which are formatted for avoid {} ----------//////

	template<typename CharBuffer, size_t BUFFER_SIZE, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], T&& t) {
		Detail::GivenBufferManager<CharBuffer> bufferManager(buffer, BUFFER_SIZE);
		Detail::FormatInBufferManager(bufferManager, false, std::forward<T>(t));
	}

	template<typename CharBuffer, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInChar(CharBuffer* const buffer, const std::size_t bufferSize, T&& t) {
		Detail::GivenBufferManager<CharBuffer> bufferManager(buffer, bufferSize);
		Detail::FormatInBufferManager(bufferManager, false, std::forward<T>(t));
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void CFilePrint(FILE* stream, T&& t) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(32);
		Detail::FormatInBufferManager(bufferManager, false, std::forward<T>(t));

		std::fwrite(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void CFilePrintLn(FILE* stream, T&& t) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(32);
		Detail::FormatInBufferManager(bufferManager, true, std::forward<T>(t));

		std::fwrite(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FilePrint(std::basic_ostream<CharBuffer>& stream, T&& t) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(32);
		Detail::FormatInBufferManager(bufferManager, false, std::forward<T>(t));

		stream.write(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
		stream.flush();
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, T&& t) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(32);
		Detail::FormatInBufferManager(bufferManager, true, std::forward<T>(t));

		stream.write(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
		stream.flush();
	}


	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	void FormatInString(std::basic_string<CharBuffer>& str, T&& t) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(32);
		Detail::FormatInBufferManager(bufferManager, false, std::forward<T>(t));
		str = std::string(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
	}

	template<typename CharBuffer = char, typename T>
	requires Detail::IsCharType<CharBuffer>::Value
	inline std::basic_string<CharBuffer> FormatString(T&& t) {
		Detail::DynamicBufferManager<CharBuffer> bufferManager(32);
		Detail::FormatInBufferManager(bufferManager, false, std::forward<T>(t));
		return std::string(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
	}
}
