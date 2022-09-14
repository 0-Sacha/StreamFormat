#pragma once

#include "Formatter/Context/FormatContext/BasicFormatContext.h"

#include <string>
#include <string_view>
#include <sstream>

namespace EngineCore::FMT {

	//------------------------------------------//
	//----------------- String -----------------//
	//------------------------------------------//

	template<typename FormatContext, typename Char>
	struct FormatType<std::basic_string<Char>, FormatContext> {
		inline static void Write(const std::basic_string<Char>& t, FormatContext& context) {
			context.BufferOut().WriteCharPt(t.data(), t.size());
		}
	};

	template<typename FormatContext, typename Char>
	struct FormatType<std::basic_string_view<Char>, FormatContext> {
		inline static void Write(const std::basic_string_view<Char>& t, FormatContext& context) {
			context.BufferOut().WriteCharPt(t.data(), t.size());
		}
	};


	template<typename FormatContext, typename Char>
	struct FormatType<std::basic_stringstream<Char>, FormatContext> {
		inline static void Write(const std::basic_stringstream<Char>& t, FormatContext& context) {
			context.BufferOut().WriteCharPt(t.str(), t.size());
		}
	};

	//------------------------------------------//
	//----------------- Memory -----------------//
	//------------------------------------------//

	// UniquePtr
	template <typename T, typename FormatContext>
	struct FormatType<std::unique_ptr<T>, FormatContext> {
		inline static void Write(const std::unique_ptr<T>& t, FormatContext& context) {
			if (context.GetFormatData().BaseValue)	FormatType<T*, FormatContext>::Write(t.get(), context);
			else									FormatType<T, FormatContext>::Write(*t, context);
		}
	};

	// SharedPtr
	template <typename T, typename FormatContext>
	struct FormatType<std::shared_ptr<T>, FormatContext> {
		inline static void Write(const std::shared_ptr<T>& t, FormatContext& context) {
			if (context.GetFormatData().BaseValue)	FormatType<T*, FormatContext>::Write(t.get(), context);
			else									FormatType<T, FormatContext>::Write(*t, context);
		}
	};

	// WeakPtr
	template <typename T, typename FormatContext>
	struct FormatType<std::weak_ptr<T>, FormatContext> {
		inline static void Write(const std::weak_ptr<T>& t, FormatContext& context) {
			FormatType<std::shared_ptr<T>, FormatContext>::Write(t.lock(), context);
		}
	};
}