#pragma once

namespace EngineCore::EngineCompute::Detail::EngineComputeType {

	struct EngineComputeBasic {};

	struct EngineComputeSSE4 {};
	struct EngineComputeAVX {};
	struct EngineComputeAVX2 {};
	struct EngineComputeAVX512 {};

	using EngineComputeDefault = EngineComputeBasic;
}
