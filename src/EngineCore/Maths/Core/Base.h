#pragma once

#include "EngineCore/Core/Core.h"
#include "EngineCore/Core/SIMD.h"


namespace EngineCore::EngineCompute {

	struct EngineComputeClassic {};

	struct EngineComputeSSE4	{};
	struct EngineComputeAVX		{};
	struct EngineComputeAVX2	{};
	struct EngineComputeAVX512	{};

}