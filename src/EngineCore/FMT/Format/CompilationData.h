#pragma once

#include "EngineCore/Core/Core.h"
#include "LoggerManager/LoggerManager.h"

namespace EngineCore::FMT::Detail
{
	struct FileLocation
	{
		FileLocation(std::string_view fileName,
					 int fileLine = 0)
			: FileName(fileName)
			, FileLine(fileLine)
		{}

		std::string_view FileName;				// __FILE__
		int FileLine;							// __LINE__
	};

	struct FunctionProperties
	{
		FunctionProperties(std::string_view fileName,
						   int fileLine = 0,
						   std::string_view functionName = "",
						   std::string_view functionSignature = "",
						   std::string_view functionAssemblyName = "")
			: Location(fileName, fileLine)
			, FunctionName(functionName)
			, FunctionSignature(functionSignature)
			, FunctionAssemblyName(functionAssemblyName)
		{}

		FunctionProperties(FileLocation location,
						   std::string_view functionName = "",
						   std::string_view functionSignature = "",
						   std::string_view functionAssemblyName = "")
			: Location(location)
			, FunctionName(functionName)
			, FunctionSignature(functionSignature)
			, FunctionAssemblyName(functionAssemblyName)
		{}

		FileLocation 	 Location;
		std::string_view FunctionName;			// __FUNCTION__
		std::string_view FunctionSignature; 	// __FUNCSIG__ -- __PRETTY_FUNCTION__
		std::string_view FunctionAssemblyName;	// __FUNCDNAME__
	};
}

#define ENGINECORE_FMT_FILE_LOCATION() 			EngineCore::FMT::Detail::FileLocation(__FILE__, __LINE__)
#define ENGINECORE_FMT_FUNCTION_PROPERTIES() 	EngineCore::FMT::Detail::FunctionProperties(ENGINECORE_FMT_FILE_LOCATION(), __FUNCTION__, __FUNCSIG__, __FUNCDNAME__)

namespace EngineCore::FMT
{

	template<typename FormatterContext>
	struct FormatterType<Detail::FileLocation, FormatterContext>
	{
		static void Write(const Detail::FileLocation& t, FormatterContext& context)
		{
			context.RunType(t.FileName);
			context.BufferOut().PushBack(':');
			context.RunType(t.FileLine);
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::FunctionProperties, FormatterContext>
	{
		static void Write(const Detail::FunctionProperties& t, FormatterContext& context)
		{
			context.RunType(t.Location);
			context.BufferOut().WriteCharArray(" @ ");
			context.RunType(t.FunctionName);
		}
	};

}
