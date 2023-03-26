#pragma once

#include "BasicFormatterContext.h"
#include "BasicFormatterContextCoreImpl.h"
#include "BasicFormatterContextParseImpl.h"

#include "ProjectCore/FMT/Detail/Buffer/BufferOutManager/DynamicBufferOutManager.h"
#include "ProjectCore/FMT/Detail/Buffer/BufferOutManager/GivenBufferOutManager.h"
#include "ProjectCore/FMT/Detail/Buffer/BufferOutManager/StaticBufferOutManager.h"

#include <memory>

namespace ProjectCore::FMT {

	/////---------- Impl with as Format ----------//////

	namespace Detail {
		template<typename CharFormat = char, typename CharBuffer = CharFormat, typename ...Args>
		requires (IsCharType<CharFormat>::Value && IsCharType<CharBuffer>::Value)
		void FormatInBufferOutManager(Detail::BasicBufferOutManager<CharBuffer>& bufferOutManager, const Detail::BufferInProperties<CharFormat>& bufferInProperties, bool newline, Args&& ...args)
		{
			using ContextType = Context::BasicFormatterContext<CharFormat, CharBuffer>;
			Detail::FormatterANSITextPropertiesExecutor<typename ContextType::BufferOutType> textPropertiesExecutor;
			ContextType context(bufferOutManager, textPropertiesExecutor);

			auto contextArgsInterface = Detail::FormatterContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
			Detail::FMTFormatBuffer<CharFormat> format(bufferInProperties);
			context.Run(format, &contextArgsInterface);
			if (newline)
				context.BufferOut().PushBack('\n');
			context.Terminate();
		}

		template<typename CharBuffer = char, typename T>
		void FormatInBufferOutManager(Detail::BasicBufferOutManager<CharBuffer>& bufferOutManager, bool newline, T&& t)
		{
			using ContextType = Context::BasicFormatterContext<char, CharBuffer>;
			Detail::FormatterANSITextPropertiesExecutor<typename ContextType::BufferOutType> textPropertiesExecutor;
			ContextType context(bufferOutManager, textPropertiesExecutor);
			context.WriteType(t);
			if (newline)
				context.BufferOut().PushBack('\n');
			context.Terminate();
		}

		template<typename CharFormat = char, typename CharBuffer = CharFormat, typename ...Args>
		requires (IsCharType<CharFormat>::Value && IsCharType<CharBuffer>::Value)
		std::shared_ptr<Detail::BasicBufferOutManager<CharBuffer>> FormatAndGetBufferOut(Detail::BufferInProperties<CharFormat>& bufferInProperties, Args&& ...args)
		{
			std::shared_ptr<Detail::BasicBufferOutManager<CharBuffer>> bufferOutManager = std::make_shared<Detail::DynamicBufferOutManager<CharBuffer>>(128);
			FormatInBufferOutManager(*bufferOutManager, bufferInProperties, false, std::forward<Args>(args)...);
			return bufferOutManager;
		}

		template<typename CharBuffer = char, typename T>
		std::shared_ptr<Detail::BasicBufferOutManager<CharBuffer>> FormatAndGetBufferOut(T&& t)
		{
			std::shared_ptr<Detail::BasicBufferOutManager<CharBuffer>> bufferOutManager = std::make_shared<Detail::DynamicBufferOutManager<CharBuffer>>(128);
			FormatInBufferOutManager(*bufferOutManager, false, std::forward<T>(t));
			return bufferOutManager;
		}
	}


	template<typename Format = std::string_view, typename CharBuffer, std::size_t BUFFER_SIZE, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], const Format& format, Args&& ...args) {
		Detail::GivenBufferOutManager<CharBuffer> bufferOutManager(buffer);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, false, std::forward<Args>(args)...);
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	void FormatInChar(CharBuffer const buffer, const std::size_t bufferSize, const Format& format, Args&& ...args) {
		Detail::GivenBufferOutManager<CharBuffer> bufferOutManager(buffer, bufferSize);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, false, std::forward<Args>(args)...);
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::FMTCharTypeFromBuffer<Format>::Type, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	void CFilePrint(FILE* stream, const Format& format, Args&& ...args) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(256);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, false, std::forward<Args>(args)...);

		std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::FMTCharTypeFromBuffer<Format>::Type, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	void CFilePrintLn(FILE* stream, const Format& format, Args&& ...args) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(256);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, true, std::forward<Args>(args)...);

		std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::FMTCharTypeFromBuffer<Format>::Type, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	void FilePrint(std::basic_ostream<CharBuffer>& stream, const Format format, Args&& ...args) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(256);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, false, std::forward<Args>(args)...);

		stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
		stream.flush();
	}

	template<typename Format = std::string_view, typename CharBuffer = typename Detail::FMTCharTypeFromBuffer<Format>::Type, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, const Format& format, Args&& ...args) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(256);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, true, std::forward<Args>(args)...);

		stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
		stream.flush();
	}


	template<typename Format = std::string_view, typename CharBuffer, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	void FormatInString(std::basic_string<CharBuffer>& str, const Format& format, Args&& ...args) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(256);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, false, std::forward<Args>(args)...);
		str = bufferOutManager.GetLastGeneratedString();
	}


	template<typename Format = std::string_view, typename CharBuffer = typename Detail::FMTCharTypeFromBuffer<Format>::Type, typename ...Args>
	requires (Detail::CanBeUseForFMTBufferIn<Format> && Detail::IsCharType<CharBuffer>::Value)
	inline std::basic_string<CharBuffer> FormatString(const Format& format, Args&& ...args) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(256);
		Detail::BufferInProperties bufferInProperties(format);
		Detail::FormatInBufferOutManager(bufferOutManager, bufferInProperties, false, std::forward<Args>(args)...);
		return bufferOutManager.GetLastGeneratedString();
	}


	/////---------- NO-FORMAT Impl except for string which are formatted for avoid {} ----------//////

	template<typename CharBuffer, size_t BUFFER_SIZE, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	void FormatInChar(CharBuffer(&buffer)[BUFFER_SIZE], T&& t) {
		Detail::GivenBufferOutManager<CharBuffer> bufferOutManager(buffer, BUFFER_SIZE);
		Detail::FormatInBufferOutManager(bufferOutManager, false, std::forward<T>(t));
	}

	template<typename CharBuffer, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	void FormatInChar(CharBuffer* const buffer, const std::size_t bufferSize, T&& t) {
		Detail::GivenBufferOutManager<CharBuffer> bufferOutManager(buffer, bufferSize);
		Detail::FormatInBufferOutManager(bufferOutManager, false, std::forward<T>(t));
	}


	template<typename CharBuffer = char, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	void CFilePrint(FILE* stream, T&& t) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(32);
		Detail::FormatInBufferOutManager(bufferOutManager, false, std::forward<T>(t));

		std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}

	template<typename CharBuffer = char, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	void CFilePrintLn(FILE* stream, T&& t) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(32);
		Detail::FormatInBufferOutManager(bufferOutManager, true, std::forward<T>(t));

		std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
		std::fflush(stream);
	}


	template<typename CharBuffer = char, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	void FilePrint(std::basic_ostream<CharBuffer>& stream, T&& t) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(32);
		Detail::FormatInBufferOutManager(bufferOutManager, false, std::forward<T>(t));

		stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
		stream.flush();
	}

	template<typename CharBuffer = char, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	void FilePrintLn(std::basic_ostream<CharBuffer>& stream, T&& t) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(32);
		Detail::FormatInBufferOutManager(bufferOutManager, true, std::forward<T>(t));

		stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
		stream.flush();
	}


	template<typename CharBuffer = char, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	void FormatInString(std::basic_string<CharBuffer>& str, T&& t) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(32);
		Detail::FormatInBufferOutManager(bufferOutManager, false, std::forward<T>(t));
		str = bufferOutManager.GetLastGeneratedString();
	}

	template<typename CharBuffer = char, typename T>
	requires (Detail::IsCharType<CharBuffer>::Value)
	inline std::basic_string<CharBuffer> FormatString(T&& t) {
		Detail::DynamicBufferOutManager<CharBuffer> bufferOutManager(32);
		Detail::FormatInBufferOutManager(bufferOutManager, false, std::forward<T>(t));
		return bufferOutManager.GetLastGeneratedString();
	}
}
