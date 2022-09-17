#pragma once

#include "EngineCore/Core/Core.h"

#include "Formatter/Core/AnsiFormat/AnsiHandler.h"

#include "Base.h"
#include "Exception.h"
#include "FormatTypes.h"
#include "GetBaseType.h"
#include "NumberDetail.h"
#include "IndentFunction.h"

// TODO :
//
// 		Reformat Profiler
//
// 		Check for escape char
//
//		/ same as # % 
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


