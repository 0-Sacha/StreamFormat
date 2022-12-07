#pragma once

#include "EngineCore/Core/Core.h"
#include "EngineCore/Detail/Detail.h"

<<<<<<<< HEAD:src/EngineCore/FMT/Core/Detail/Detail.h
#include "FMT/Core/AnsiFormat/AnsiHandler.h"
========
#include "Types/Types.h"
#include "Types/TypesInfo.h"
#include "Types/TypesTraits.h"
>>>>>>>> 040fab10b4777918832b29a04b07add2d411d3ab:src/FMT/Detail/Detail.h

#include "Exception.h"
#include "Specifiers.h"
#include "IndentHandler.h"
#include "UtilsContextsFunctions.h"

#include "AnsiFormat/AnsiHandler.h"

// TODO :
//
// 		Reformat Profiler / LoggerManager
//
//		/ same as # % 
//
// 		Check for escape char
//
//		Macro PackSave ; PackSave (foreshadowing for constexpr)
//
//		-- NOT POSSIBLE -- => FAST compile
// 
//		TOKEN bufferIn
//
//		JSON
// 
//		GLOBBER
// 
//		REGEX		
//			{I:REGEX}
//			{:regex=REGEX} (string / char array)
//			{}
//
//		End writing all writer and reader (string / char pt)
//		

namespace EngineCore::FMT {
	template<typename CharFormat = char, typename CharBuffer = CharFormat, typename ...ContextArgs>
	class BasicFormatContext;

	struct UnFormatContextError;

    template<typename CharFormat = char, typename CharBuffer = CharFormat, typename ...ContextArgs>
	class BasicUnFormatContext;
}


