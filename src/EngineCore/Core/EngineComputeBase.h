#pragma once

#include "EngineCore/Core/Core.h"


namespace EngineCore::EngineCompute {

	struct EngineComputeBasic {};

	struct EngineComputeSSE4 {};
	struct EngineComputeAVX {};
	struct EngineComputeAVX2 {};
	struct EngineComputeAVX512 {};

	using EngineComputeDefault = EngineComputeBasic;
}
