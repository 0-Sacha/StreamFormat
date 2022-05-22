#pragma once

#include "EngineCore/Core.h"

#include "../AnsiFormat/AnsiManager.h"

#include "Base.h"
#include "Exception.h"
#include "FormatTypes.h"
#include "GetBaseType.h"
#include "NumberDetail.h"
#include "IndentFunction.h"

// TODO :
//
//		TOKEN bufferIn
//		Auto bufferRestore
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
//		PackSave (foreshadowing for constexpr)
//


namespace EngineCore::Instrumentation::FMT {
	template<typename CharFormat = char, typename CharBuffer = CharFormat, typename ...ContextArgs>
	class BasicFormatContext;

	struct UnFormatContextError;

    template<typename CharFormat = char, typename CharBuffer = CharFormat, typename ...ContextArgs>
	class BasicUnFormatContext;
}


