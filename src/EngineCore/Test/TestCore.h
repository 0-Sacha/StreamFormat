#pragma once

#include "EngineCore/Core/Core.h"
#include "LoggerManager/LoggerManager.h"

namespace EngineCore::Test {

	struct CompilerDataPack
	{
		CompilerDataPack(std::string_view fileName,
						 int fileLine = 0,
						 std::string_view functionName = "",
						 std::string_view functionSignature = "",
						 std::string_view functionAssemblyName = "")
			: FileName(fileName)
			, FileLine(fileLine)
			, FunctionName(functionName)
			, FunctionSignature(functionSignature)
			, FunctionAssemblyName(functionAssemblyName)
		{}

		std::string_view FileName;				// __FILE__
		int FileLine;							// __LINE__
		std::string_view FunctionName;			// __FUNCTION__
		std::string_view FunctionSignature; 	// __FUNCSIG__ -- __PRETTY_FUNCTION__
		std::string_view FunctionAssemblyName;	// __FUNCDNAME__
	};

}

#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

#ifndef __FUNCDNAME__
#define __FUNCDNAME__ __PRETTY_FUNCTION__
#endif

#define ENGINECORE_GET_COMPILER_DATA() EngineCore::Test::CompilerDataPack(__FILE__, __LINE__, __FUNCTION__, __FUNCSIG__, __FUNCDNAME__)

#define ENGINECORE_FUNC() ENGINECORE_INFO("function : {:C:+black} @ {C:+black}{}:{}{C}", __FUNCSIG__, __FILE__, __LINE__)
#define ENGINECORE_FILE() ENGINECORE_INFO("{C:+black}{}:{}{C}", __FILE__, __LINE__)


