#pragma once

<<<<<<< HEAD:src/EngineCore/FMT/Context/UnFormatContext/Utils/UnFormatType.h
#include "FMT/Core/Detail/Detail.h"
=======
#include "FMT/Detail/Detail.h"
>>>>>>> 040fab10b4777918832b29a04b07add2d411d3ab:src/EngineCore/Instrumentation/Formatter/Context/UnFormatContext/Utils/UnFormatType.h

#define ENGINECORE_UNFORMAT_DECLARED
namespace EngineCore::FMT {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	class BasicUnFormatContext;

	template<typename T, typename UnFormatContext = BasicUnFormatContext<char, char>>
	struct UnFormatType {
		template<class K = T>
		static inline auto Read(K& t, UnFormatContext& context) {
			// ENGINECORE_IF_MSVC(static_assert(false, __FUNCSIG__));
			return false;
		}
	};

}

#define ENGINECORE_AUTO_UNFORMAT(Type, fmt, ...)	template<typename UnFormatContext>\
													struct EngineCore::FMT::UnFormatType<Type, UnFormatContext> {\
														static bool Read(Type& value, UnFormatContext& context) {\
															return context.LittleUnFormat(fmt, __VA_ARGS__);\
														}\
													};








