#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- Vector3 -------------//
	template<typename T>
	struct Vector<3, T, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType = T;
		
		union {
			std::array<ValueType, 3> data;
			struct { ValueType x, y, z; };
		};

		inline constexpr static size_t Length()	{ return 3; }
		inline constexpr static size_t Count()	{ return 3; }
		inline constexpr static size_t Size()	{ return 3; }

		inline constexpr T& Data(uint8_t idx)				{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const T& Data(uint8_t idx) const	{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }

		inline constexpr T& operator[](uint8_t idx)				{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const T& operator[](uint8_t idx) const { ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		constexpr Vector(const T scalar);
		constexpr Vector(const T x, const T y, const T z);
		constexpr Vector(const Vector<3, T, EngineCompute::EngineComputeBasic>& vec);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//

		template<typename K> constexpr Vector(const K scalar);
		template<typename K1, typename K2, typename K3> constexpr Vector(const K1 x, const K2 y, const K3 z);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector(const Vector<3, K, ComputeAlgoritmClient>& vec);

		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//


		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template<typename K, typename ComputeAlgoritmClient> constexpr bool operator==(const Vector<3, K, ComputeAlgoritmClient>& rhs);
		template<typename K, typename ComputeAlgoritmClient> constexpr bool operator!=(const Vector<3, K, ComputeAlgoritmClient>& rhs);

		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator&&(const Vector<3, K, ComputeAlgoritmClient>& rhs);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator||(const Vector<3, K, ComputeAlgoritmClient>& rhs);

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<3, T, EngineCompute::EngineComputeBasic>  operator+();
		// operator -I
		constexpr Vector<3, T, EngineCompute::EngineComputeBasic>  operator-();
		// operator ~I
		constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator~();

		// operator ++I
		constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<3, T, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<3, T, EngineCompute::EngineComputeBasic>  operator--(int);

		// operator =
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator +=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator+=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator+=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator -=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator-=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator-=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator *=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator*=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator*=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator /=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator/=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator/=(const Vector<3, K, ComputeAlgoritmClient>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator %=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator%=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator%=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator &=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator&=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator&=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator |=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator|=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator|=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator ^=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator^=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator^=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator <<=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator<<=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator<<=(const Vector<3, K, ComputeAlgoritmClient>& vec);

		// operator >>=
		template<typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator>>=(K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& operator>>=(const Vector<3, K, ComputeAlgoritmClient>& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator+(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator+(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator+(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator -
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator-(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator-(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator-(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator *
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator*(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator*(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator*(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator /
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator/(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator/(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator/(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator%(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator%(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator%(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator &
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator&(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator&(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator&(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator |
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator|(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator|(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator|(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator ^
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator^(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator^(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator^(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator <<
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator<<(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

	// operator >>
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator>>(K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgoritmClient> constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs);

}





