#pragma once


#define ENGINE_CORE_SIMD_CHECK() EngineCore::Intrinsic::CheckISAFeature();

namespace EngineCore::Intrinsic {
	void CheckISAFeature();
}

// From Microsoft Docs : https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-160&viewFallbackFrom=vs-2019

namespace EngineCore::SIMD::Core {

	class InstructionSet
	{
		// forward declarations
		class InstructionSet_Internal;

	public:
		// getters
		inline static std::string Vendor(void)		{ return CPU_Rep.vendor_; }
		inline static std::string Brand(void)		{ return CPU_Rep.brand_; }

		inline static bool SSE(void)				{ return CPU_Rep.f_1_EDX_[25]; }
		inline static bool SSE2(void)				{ return CPU_Rep.f_1_EDX_[26]; }
		inline static bool SSE3(void)				{ return CPU_Rep.f_1_ECX_[0]; }
		inline static bool SSSE3(void)				{ return CPU_Rep.f_1_ECX_[9]; }
		inline static bool SSE41(void)				{ return CPU_Rep.f_1_ECX_[19]; }
		inline static bool SSE42(void)				{ return CPU_Rep.f_1_ECX_[20]; }
		inline static bool AVX(void)				{ return CPU_Rep.f_1_ECX_[28]; }
		inline static bool AVX2(void)				{ return CPU_Rep.f_7_EBX_[5]; }
		inline static bool AVX512F(void)			{ return CPU_Rep.f_7_EBX_[16]; }
		inline static bool AVX512PF(void)			{ return CPU_Rep.f_7_EBX_[26]; }
		inline static bool AVX512ER(void)			{ return CPU_Rep.f_7_EBX_[27]; }
		inline static bool AVX512CD(void)			{ return CPU_Rep.f_7_EBX_[28]; }

		inline static bool FMA(void)				{ return CPU_Rep.f_1_ECX_[12]; }

		inline static bool PCLMULQDQ(void)			{ return CPU_Rep.f_1_ECX_[1]; }
		inline static bool MONITOR(void)			{ return CPU_Rep.f_1_ECX_[3]; }
		inline static bool CMPXCHG16B(void)			{ return CPU_Rep.f_1_ECX_[13]; }
		inline static bool MOVBE(void)				{ return CPU_Rep.f_1_ECX_[22]; }
		inline static bool POPCNT(void)				{ return CPU_Rep.f_1_ECX_[23]; }
		inline static bool AES(void)				{ return CPU_Rep.f_1_ECX_[25]; }
		inline static bool XSAVE(void)				{ return CPU_Rep.f_1_ECX_[26]; }
		inline static bool OSXSAVE(void)			{ return CPU_Rep.f_1_ECX_[27]; }
		inline static bool F16C(void)				{ return CPU_Rep.f_1_ECX_[29]; }
		inline static bool RDRAND(void)				{ return CPU_Rep.f_1_ECX_[30]; }

		inline static bool MSR(void)				{ return CPU_Rep.f_1_EDX_[5]; }
		inline static bool CX8(void)				{ return CPU_Rep.f_1_EDX_[8]; }
		inline static bool SEP(void)				{ return CPU_Rep.f_1_EDX_[11]; }
		inline static bool CMOV(void)				{ return CPU_Rep.f_1_EDX_[15]; }
		inline static bool CLFSH(void)				{ return CPU_Rep.f_1_EDX_[19]; }
		inline static bool MMX(void)				{ return CPU_Rep.f_1_EDX_[23]; }
		inline static bool FXSR(void)				{ return CPU_Rep.f_1_EDX_[24]; }

		inline static bool FSGSBASE(void)			{ return CPU_Rep.f_7_EBX_[0]; }
		inline static bool BMI1(void)				{ return CPU_Rep.f_7_EBX_[3]; }
		inline static bool HLE(void)				{ return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[4]; }
		inline static bool BMI2(void)				{ return CPU_Rep.f_7_EBX_[8]; }
		inline static bool ERMS(void)				{ return CPU_Rep.f_7_EBX_[9]; }
		inline static bool INVPCID(void)			{ return CPU_Rep.f_7_EBX_[10]; }
		inline static bool RTM(void)				{ return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }
		inline static bool RDSEED(void)				{ return CPU_Rep.f_7_EBX_[18]; }
		inline static bool ADX(void)				{ return CPU_Rep.f_7_EBX_[19]; }
		inline static bool SHA(void)				{ return CPU_Rep.f_7_EBX_[29]; }

		inline static bool PREFETCHWT1(void)		{ return CPU_Rep.f_7_ECX_[0]; }

		inline static bool LAHF(void)				{ return CPU_Rep.f_81_ECX_[0]; }
		inline static bool LZCNT(void)				{ return CPU_Rep.isIntel_ && CPU_Rep.f_81_ECX_[5]; }
		inline static bool ABM(void)				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[5]; }
		inline static bool SSE4a(void)				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }
		inline static bool XOP(void)				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[11]; }
		inline static bool TBM(void)				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[21]; }
		
		inline static bool SYSCALL(void)			{ return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
		inline static bool MMXEXT(void)				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }
		inline static bool RDTSCP(void)				{ return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
		inline static bool _3DNOWEXT(void)			{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
		inline static bool _3DNOW(void)				{ return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

	private:
		static const InstructionSet_Internal CPU_Rep;

		class InstructionSet_Internal
		{
		public:
			InstructionSet_Internal()
				: nIds_{ 0 },
				nExIds_{ 0 },
				isIntel_{ false },
				isAMD_{ false },
				f_1_ECX_{ 0 },
				f_1_EDX_{ 0 },
				f_7_EBX_{ 0 },
				f_7_ECX_{ 0 },
				f_81_ECX_{ 0 },
				f_81_EDX_{ 0 },
				data_{},
				extdata_{}
			{
				//int cpuInfo[4] = {-1};
				std::array<int, 4> cpui;

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

			int nIds_;
			int nExIds_;
			std::string vendor_;
			std::string brand_;
			bool isIntel_;
			bool isAMD_;
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