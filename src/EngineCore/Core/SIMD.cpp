
#include "EngineCorepch.h"
#include "SIMD.h"
#include "EngineCore/Core/Core.h"

#ifdef ENGINE_CORE_USE_CPPTOOLS_LOGGER
#define ENGINE_CORE_ISA_FEATURE_TEST(feature, isSupported) isSupported ? ENGINE_CORE_INFO("{} is supported", feature) : ENGINE_CORE_ERROR("{} is NOT suppported", feature)
#else
#define ENGINE_CORE_ISA_FEATURE_TEST(feature, isSupported)
#endif

namespace EngineCore::SIMD {
	void CheckISAFeature()
	{
		ENGINE_CORE_INFO("Vendor : {}", Core::InstructionSet::Vendor());
		ENGINE_CORE_INFO("Brand  : {}", Core::InstructionSet::Brand());

		ENGINE_CORE_ISA_FEATURE_TEST("SSE",			Core::InstructionSet::SSE());
		ENGINE_CORE_ISA_FEATURE_TEST("SSE2",		Core::InstructionSet::SSE2());
		ENGINE_CORE_ISA_FEATURE_TEST("SSE3",		Core::InstructionSet::SSE3());
		ENGINE_CORE_ISA_FEATURE_TEST("SSE4.1",		Core::InstructionSet::SSE41());
		ENGINE_CORE_ISA_FEATURE_TEST("SSE4.2",		Core::InstructionSet::SSE42());
		ENGINE_CORE_ISA_FEATURE_TEST("SSE4a",		Core::InstructionSet::SSE4a());
		ENGINE_CORE_ISA_FEATURE_TEST("SSSE3",		Core::InstructionSet::SSSE3());
		ENGINE_CORE_ISA_FEATURE_TEST("AVX",			Core::InstructionSet::AVX());
		ENGINE_CORE_ISA_FEATURE_TEST("AVX2",		Core::InstructionSet::AVX2());
		ENGINE_CORE_ISA_FEATURE_TEST("AVX512CD",	Core::InstructionSet::AVX512CD());
		ENGINE_CORE_ISA_FEATURE_TEST("AVX512ER",	Core::InstructionSet::AVX512ER());
		ENGINE_CORE_ISA_FEATURE_TEST("AVX512F",		Core::InstructionSet::AVX512F());
		ENGINE_CORE_ISA_FEATURE_TEST("AVX512PF",	Core::InstructionSet::AVX512PF());
		
		ENGINE_CORE_ISA_FEATURE_TEST("FMA",			Core::InstructionSet::FMA());

		ENGINE_CORE_ISA_FEATURE_TEST("3DNOW",		Core::InstructionSet::_3DNOW());
		ENGINE_CORE_ISA_FEATURE_TEST("3DNOWEXT",	Core::InstructionSet::_3DNOWEXT());
		ENGINE_CORE_ISA_FEATURE_TEST("ABM",			Core::InstructionSet::ABM());
		ENGINE_CORE_ISA_FEATURE_TEST("ADX",			Core::InstructionSet::ADX());
		ENGINE_CORE_ISA_FEATURE_TEST("AES",			Core::InstructionSet::AES());
		ENGINE_CORE_ISA_FEATURE_TEST("BMI1",		Core::InstructionSet::BMI1());
		ENGINE_CORE_ISA_FEATURE_TEST("BMI2",		Core::InstructionSet::BMI2());
		ENGINE_CORE_ISA_FEATURE_TEST("CLFSH",		Core::InstructionSet::CLFSH());
		ENGINE_CORE_ISA_FEATURE_TEST("CMPXCHG16B",	Core::InstructionSet::CMPXCHG16B());
		ENGINE_CORE_ISA_FEATURE_TEST("CX8",			Core::InstructionSet::CX8());
		ENGINE_CORE_ISA_FEATURE_TEST("ERMS",		Core::InstructionSet::ERMS());
		ENGINE_CORE_ISA_FEATURE_TEST("F16C",		Core::InstructionSet::F16C());
		ENGINE_CORE_ISA_FEATURE_TEST("FSGSBASE",	Core::InstructionSet::FSGSBASE());
		ENGINE_CORE_ISA_FEATURE_TEST("FXSR",		Core::InstructionSet::FXSR());
		ENGINE_CORE_ISA_FEATURE_TEST("HLE",			Core::InstructionSet::HLE());
		ENGINE_CORE_ISA_FEATURE_TEST("INVPCID",		Core::InstructionSet::INVPCID());
		ENGINE_CORE_ISA_FEATURE_TEST("LAHF",		Core::InstructionSet::LAHF());
		ENGINE_CORE_ISA_FEATURE_TEST("LZCNT",		Core::InstructionSet::LZCNT());
		ENGINE_CORE_ISA_FEATURE_TEST("MMX",			Core::InstructionSet::MMX());
		ENGINE_CORE_ISA_FEATURE_TEST("MMXEXT",		Core::InstructionSet::MMXEXT());
		ENGINE_CORE_ISA_FEATURE_TEST("MONITOR",		Core::InstructionSet::MONITOR());
		ENGINE_CORE_ISA_FEATURE_TEST("MOVBE",		Core::InstructionSet::MOVBE());
		ENGINE_CORE_ISA_FEATURE_TEST("MSR",			Core::InstructionSet::MSR());
		ENGINE_CORE_ISA_FEATURE_TEST("OSXSAVE",		Core::InstructionSet::OSXSAVE());
		ENGINE_CORE_ISA_FEATURE_TEST("PCLMULQDQ",	Core::InstructionSet::PCLMULQDQ());
		ENGINE_CORE_ISA_FEATURE_TEST("POPCNT",		Core::InstructionSet::POPCNT());
		ENGINE_CORE_ISA_FEATURE_TEST("PREFETCHWT1", Core::InstructionSet::PREFETCHWT1());
		ENGINE_CORE_ISA_FEATURE_TEST("RDRAND",		Core::InstructionSet::RDRAND());
		ENGINE_CORE_ISA_FEATURE_TEST("RDSEED",		Core::InstructionSet::RDSEED());
		ENGINE_CORE_ISA_FEATURE_TEST("RDTSCP",		Core::InstructionSet::RDTSCP());
		ENGINE_CORE_ISA_FEATURE_TEST("RTM",			Core::InstructionSet::RTM());
		ENGINE_CORE_ISA_FEATURE_TEST("SEP",			Core::InstructionSet::SEP());
		ENGINE_CORE_ISA_FEATURE_TEST("SHA",			Core::InstructionSet::SHA());
		ENGINE_CORE_ISA_FEATURE_TEST("SYSCALL",		Core::InstructionSet::SYSCALL());
		ENGINE_CORE_ISA_FEATURE_TEST("TBM",			Core::InstructionSet::TBM());
		ENGINE_CORE_ISA_FEATURE_TEST("XOP",			Core::InstructionSet::XOP());
		ENGINE_CORE_ISA_FEATURE_TEST("XSAVE",		Core::InstructionSet::XSAVE());
	}
}




namespace EngineCore::Intrinsic::Core {
	const InstructionSet::InstructionSet_Internal InstructionSet::CPU_Rep;
}