#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- Vector1 -------------//
	template<typename T>
	struct Vector<1, T, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType = T;

		union {
			std::array<ValueType, 1> data;
			ValueType x;
		};

		inline constexpr static size_t Length() { return 1; }
		inline constexpr static size_t Count()	{ return 1; }
		inline constexpr static size_t Size()	{ return 1; }

		inline constexpr		T& Data()		{ return x; };
		inline constexpr const	T& Data() const { return x; };

		//--------------------------------------------//
		//------------- Basic Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		constexpr Vector(const T scalar);
		constexpr Vector(const Vector<1, T, EngineCompute::EngineComputeBasic>& vec);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//

		template<typename K> constexpr Vector(const K scalar);
		template<typename K, typename ComputeAlgoritmClient> constexpr Vector(const Vector<1, K, ComputeAlgoritmClient>& vec);


		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template<typename K, typename ComputeAlgoritmClient> constexpr bool operator==(const Vector<1, K, ComputeAlgoritmClient>& rhs);
		template<typename K, typename ComputeAlgoritmClient> constexpr bool operator!=(const Vector<1, K, ComputeAlgoritmClient>& rhs);

		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator&&(const Vector<1, K, ComputeAlgorithmClient>& rhs);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator||(const Vector<1, K, ComputeAlgorithmClient>& rhs);


		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<1, T, EngineCompute::EngineComputeBasic>  operator+();
		// operator -I
		constexpr Vector<1, T, EngineCompute::EngineComputeBasic>  operator-();
		// operator ~I
		constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator~();

		// operator ++I
		constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<1, T, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<1, T, EngineCompute::EngineComputeBasic>  operator--(int);

		// operator =
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator +=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator+=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator+=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator -=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator-=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator-=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator *=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator*=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator*=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator /=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator/=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator/=(const Vector<1, K, ComputeAlgorithmClient>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator %=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator%=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator%=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator &=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator&=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator&=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator |=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator|=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator|=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator ^=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator^=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator^=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator <<=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator<<=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator<<=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator >>=
		template<typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator>>=(K scalar);
		template<typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& operator>>=(const Vector<1, K, ComputeAlgorithmClient>& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	
	// operator +
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator+(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator+(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator+(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator -
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator-(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator-(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator-(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator *
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator*(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator*(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator*(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator /
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator/(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator/(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator/(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator%(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator%(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator%(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator &
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator&(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator&(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator&(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator |
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator|(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator|(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator|(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator ^
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator^(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator^(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator^(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator <<
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator<<(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator >>
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, K rhs);
	template<typename T, typename K> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator>>(K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs);
	template<typename T, typename K, typename ComputeAlgorithmClient> constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);
}









