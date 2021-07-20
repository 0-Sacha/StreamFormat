#pragma once

#ifdef ENGINE_CORE_COMPILER_MSVC

#define ENGINE_CORE_SIMD_CHECK() EngineCore::SIMD::CheckISAFeature();

namespace EngineCore::SIMD {
	void CheckISAFeature();
} // namespace EngineCore::SIMD

// From Microsoft Docs : https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-160&viewFallbackFrom=vs-2019

namespace EngineCore::SIMD::Core {

	class InstructionSet
	{
		// forward declarations
		class InstructionSet_Internal;

	public:
		// getters
		inline static auto Vendor() -> std::string		{ return CPU_Rep.vendor_; }
		inline static auto Brand() -> std::string		{ return CPU_Rep.brand_; }

		inline static auto SSE() -> bool				{ return CPU_Rep.f_1_EDX_[25]; }
		inline static auto SSE2() -> bool				{ return CPU_Rep.f_1_EDX_[26]; }
		inline static auto SSE3() -> bool				{ return CPU_Rep.f_1_ECX_[0]; }
		inline static auto SSSE3() -> bool				{ return CPU_Rep.f_1_ECX_[9]; }
		inline static auto SSE41() -> bool				{ return CPU_Rep.f_1_ECX_[19]; }
		inline static auto SSE42() -> bool				{ return CPU_Rep.f_1_ECX_[20]; }
		inline static auto AVX() -> bool				{ return CPU_Rep.f_1_ECX_[28]; }
		inline static auto AVX2() -> bool				{ return CPU_Rep.f_7_EBX_[5]; }
		inline static auto AVX512F() -> bool			{ return CPU_Rep.f_7_EBX_[16]; }
		inline static auto AVX512PF() -> bool			{ return CPU_Rep.f_7_EBX_[26]; }
		inline static auto AVX512ER() -> bool			{ return CPU_Rep.f_7_EBX_[27]; }
		inline static auto AVX512CD() -> bool			{ return CPU_Rep.f_7_EBX_[28]; }

		inline static auto FMA() -> bool				{ return CPU_Rep.f_1_ECX_[12]; }

		inline static auto PCLMULQDQ() -> bool			{ return CPU_Rep.f_1_ECX_[1]; }
		inline static auto MONITOR() -> bool			{ return CPU_Rep.f_1_ECX_[3]; }
		inline static auto CMPXCHG16B() -> bool			{ return CPU_Rep.f_1_ECX_[13]; }
		inline static auto MOVBE() -> bool				{ return CPU_Rep.f_1_ECX_[22]; }
		inline static auto POPCNT() -> bool				{ return CPU_Rep.f_1_ECX_[23]; }
		inline static auto AES() -> bool				{ return CPU_Rep.f_1_ECX_[25]; }
		inline static auto XSAVE() -> bool				{ return CPU_Rep.f_1_ECX_[26]; }
		inline static auto OSXSAVE() -> bool			{ return CPU_Rep.f_1_ECX_[27]; }
		inline static auto F16C() -> bool				{ return CPU_Rep.f_1_ECX_[29]; }
		inline static auto RDRAND() -> bool				{ return CPU_Rep.f_1_ECX_[30]; }

		inline static auto MSR() -> bool				{ return CPU_Rep.f_1_EDX_[5]; }
		inline static auto CX8() -> bool				{ return CPU_Rep.f_1_EDX_[8]; }
		inline static auto SEP() -> bool				{ return CPU_Rep.f_1_EDX_[11]; }
		inline static auto CMOV() -> bool				{ return CPU_Rep.f_1_EDX_[15]; }
		inline static auto CLFSH() -> bool				{ return CPU_Rep.f_1_EDX_[19]; }
		inline static auto MMX() -> bool				{ return CPU_Rep.f_1_EDX_[23]; }
		inline static auto FXSR() -> bool				{ return CPU_Rep.f_1_EDX_[24]; }

		inline static auto FSGSBASE() -> bool			{ return CPU_Rep.f_7_EBX_[0]; }
		inline static auto BMI1() -> bool				{ return CPU_Rep.f_7_EBX_[3]; }
		inline static auto HLE() -> bool				{ return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[4]; }
		inline static auto BMI2() -> bool				{ return CPU_Rep.f_7_EBX_[8]; }
		inline static auto ERMS() -> bool				{ return CPU_Rep.f_7_EBX_[9]; }
		inline static auto INVPCID() -> bool			{ return CPU_Rep.f_7_EBX_[10]; }
		inline static auto RTM() -> bool				{ return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }
		inline static auto RDSEED() -> bool				{ return CPU_Rep.f_7_EBX_[18]; }
		inline static auto ADX() -> bool				{ return CPU_Rep.f_7_EBX_[19]; }
		inline static auto SHA() -> bool				{ return CPU_Rep.f_7_EBX_[29]; }

		inline static auto PREFETCHWT1() -> bool		{ return CPU_Rep.f_7_ECX_[0]; }

		inline static auto LAHF() -> bool				{ return CPU_Rep.f_81_ECX_[0]; }
		inline static auto LZCNT() -> bool				{ return CPU_Rep.isIntel_ && CPU_Rep.f_81_ECX_[5]; }
		inline static auto ABM() -> bool				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[5]; }
		inline static auto SSE4a() -> bool				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }
		inline static auto XOP() -> bool				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[11]; }
		inline static auto TBM() -> bool				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[21]; }
		
		inline static auto SYSCALL() -> bool			{ return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
		inline static auto MMXEXT() -> bool				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }
		inline static auto RDTSCP() -> bool				{ return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
		inline static auto _3DNOWEXT() -> bool			{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
		inline static auto _3DNOW() -> bool				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

	private:
		static const InstructionSet_Internal CPU_Rep;

		class InstructionSet_Internal
		{
		public:
			InstructionSet_Internal()
				: 
				f_1_ECX_{ 0 },
				f_1_EDX_{ 0 },
				f_7_EBX_{ 0 },
				f_7_ECX_{ 0 },
				f_81_ECX_{ 0 },
				f_81_EDX_{ 0 }
				
			{
				//int cpuInfo[4] = {-1};
				std::array<int, 4> cpui{};

				// Calling __cpuid with 0x0 as the function_id argument
				// gets the number of the highest valid function ID.
				__cpuid(cpui.data(), 0);
				nIds_ = cpui[0];

				for (int i = 0; i <= nIds_; ++i)
				{
					__cpuidex(cpui.data(), i, 0);
					data_.push_back(cpui);
				}

				// Capture vendor string
				char vendor[0x20];
				memset(vendor, 0, sizeof(vendor));
				*reinterpret_cast<int*>(vendor) = data_[0][1];
				*reinterpret_cast<int*>(vendor + 4) = data_[0][3];
				*reinterpret_cast<int*>(vendor + 8) = data_[0][2];
				vendor_ = vendor;
				if (vendor_ == "GenuineIntel")
				{
					isIntel_ = true;
				}
				else if (vendor_ == "AuthenticAMD")
				{
					isAMD_ = true;
				}

				// load bitset with flags for function 0x00000001
				if (nIds_ >= 1)
				{
					f_1_ECX_ = data_[1][2];
					f_1_EDX_ = data_[1][3];
				}

				// load bitset with flags for function 0x00000007
				if (nIds_ >= 7)
				{
					f_7_EBX_ = data_[7][1];
					f_7_ECX_ = data_[7][2];
				}

				// Calling __cpuid with 0x80000000 as the function_id argument
				// gets the number of the highest valid extended ID.
				__cpuid(cpui.data(), 0x80000000);
				nExIds_ = cpui[0];

				char brand[0x40];
				memset(brand, 0, sizeof(brand));

				for (int i = 0x80000000; i <= nExIds_; ++i)
				{
					__cpuidex(cpui.data(), i, 0);
					extdata_.push_back(cpui);
				}

				// load bitset with flags for function 0x80000001
				if (nExIds_ >= 0x80000001)
				{
					f_81_ECX_ = extdata_[1][2];
					f_81_EDX_ = extdata_[1][3];
				}

				// Interpret CPU brand string if reported
				if (nExIds_ >= 0x80000004)
				{
					memcpy(brand, extdata_[2].data(), sizeof(cpui));
					memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
					memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
					brand_ = brand;
				}
			};

			int nIds_{ 0 };
			int nExIds_{ 0 };
			std::string vendor_;
			std::string brand_;
			bool isIntel_{ false };
			bool isAMD_{ false };
			std::bitset<32> f_1_ECX_;
			std::bitset<32> f_1_EDX_;
			std::bitset<32> f_7_EBX_;
			std::bitset<32> f_7_ECX_;
			std::bitset<32> f_81_ECX_;
			std::bitset<32> f_81_EDX_;
			std::vector<std::array<int, 4>> data_;
			std::vector<std::array<int, 4>> extdata_;
		};
	};

}

#endif