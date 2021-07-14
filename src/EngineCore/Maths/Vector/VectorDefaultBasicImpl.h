#pragma once

#include "Vector.h"


namespace EngineCore {

	template<std::size_t COUNT, typename T>
	struct Vector<COUNT, T, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType = T;

		std::array<ValueType, COUNT> data;

		inline constexpr static size_t Length() { return COUNT; }
		inline constexpr static size_t Count()	{ return COUNT; }
		inline constexpr static size_t Size()	{ return COUNT; }

		inline constexpr T& Data(uint8_t idx)				{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const T& Data(uint8_t idx) const	{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }

		inline constexpr T& operator[](uint8_t idx)				{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const T& operator[](uint8_t idx) const { ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }

		//--------------------------------------------//
		//------------- Basic Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		template<typename ...K> constexpr Vector(const K ...values);
		constexpr Vector(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& vec);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//

		template<typename K> constexpr Vector(const K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector(const Vector<COUNT, K, ComputeAlgoritmClient>& vec);


		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template<typename K, typename ComputeAlgoritmClient> constexpr bool operator==(const Vector<COUNT, K, ComputeAlgoritmClient>& rhs);
		template<typename K, typename ComputeAlgoritmClient> constexpr bool operator!=(const Vector<COUNT, K, ComputeAlgoritmClient>& rhs);

		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator&&(const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator||(const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);


		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>  operator+();
		// operator -I
		constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>  operator-();
		// operator ~I
		constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator~();

		// operator ++I
		constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>  operator--(int);

		// operator =
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator +=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator+=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator+=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator -=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator-=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator-=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator *=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator*=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator*=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator /=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator/=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator/=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator %=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator%=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator%=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator &=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator&=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator&=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator |=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator|=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator|=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator ^=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator^=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator^=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator <<=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator<<=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator<<=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);

		// operator >>=
		template<typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator>>=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& operator>>=(const Vector<COUNT, K, ComputeAlgorithmClient>& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	
	// operator +
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator+(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator+(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator+(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator -
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator-(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator-(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator-(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator *
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator*(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator*(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator*(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator /
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator/(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator/(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator/(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator%(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator%(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator%(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator &
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator&(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator&(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator&(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator |
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator|(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator|(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator|(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator ^
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator^(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator^(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator^(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator <<
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator<<(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

	// operator >>
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<std::size_t COUNT, typename T, typename K> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator>>(K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs);
	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgorithmClient>& rhs);

}



