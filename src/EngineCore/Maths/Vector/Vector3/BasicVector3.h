#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- BasicVector3 -------------//
	template<typename T>
	struct BasicVector<3, T>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		union {
			T data[2];
			struct { T x, y, z; };
		};

		inline constexpr static size_t Length()	{ return 2; }
		inline constexpr static size_t Count()	{ return 2; }
		inline constexpr static size_t Size()	{ return 2; }

		constexpr		T& Data(uint8_t idx);
		constexpr const T& Data(uint8_t idx) const;

		constexpr		T& operator[](uint8_t idx);
		constexpr const T& operator[](uint8_t idx) const;

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr BasicVector();
		template<typename K> constexpr explicit BasicVector(K scalar);
		template<typename K1, typename K2, typename K3> constexpr BasicVector(K1 x, K2 y, K3 z);
		template<typename K> constexpr explicit BasicVector(const BasicVector<3, K>& vec);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template<typename K> constexpr bool operator==(const BasicVector<3, K>& rhs);
		template<typename K> constexpr bool operator!=(const BasicVector<3, K>& rhs);



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr BasicVector<3, T>  operator+();
		// operator -I
		constexpr BasicVector<3, T>  operator-();
		// operator ++I
		constexpr BasicVector<3, T>& operator++();
		// operator --I
		constexpr BasicVector<3, T>& operator--();
		// operator I++
		constexpr BasicVector<3, T>  operator++(int);
		// operator I--
		constexpr BasicVector<3, T>  operator--(int);

		// operator =
		template<typename K>	constexpr BasicVector<3, T>& operator=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator=(const BasicVector<3, K>& vec);

		// operator +=
		template<typename K>	constexpr BasicVector<3, T>& operator+=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator+=(const BasicVector<3, K>& vec);

		// operator -=
		template<typename K>	constexpr BasicVector<3, T>& operator-=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator-=(const BasicVector<3, K>& vec);

		// operator *=
		template<typename K>	constexpr BasicVector<3, T>& operator*=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator*=(const BasicVector<3, K>& vec);

		// operator /=
		template<typename K>	constexpr BasicVector<3, T>& operator/=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator/=(const BasicVector<3, K>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// binary condition
		template<typename K>	constexpr BasicVector<3, T> operator&&(const BasicVector<3, K>& rhs);
		template<typename K>	constexpr BasicVector<3, T> operator||(const BasicVector<3, K>& rhs);

		// operator ~I
		constexpr BasicVector<3, T> operator~();

		// operator %=
		template<typename K>	constexpr BasicVector<3, T>& operator%=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator%=(const BasicVector<3, K>& vec);

		// operator &=
		template<typename K>	constexpr BasicVector<3, T>& operator&=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator&=(const BasicVector<3, K>& vec);

		// operator |=
		template<typename K>	constexpr BasicVector<3, T>& operator|=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator|=(const BasicVector<3, K>& vec);

		// operator ^=
		template<typename K>	constexpr BasicVector<3, T>& operator^=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator^=(const BasicVector<3, K>& vec);

		// operator <<=
		template<typename K>	constexpr BasicVector<3, T>& operator<<=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator<<=(const BasicVector<3, K>& vec);

		// operator >>=
		template<typename K>	constexpr BasicVector<3, T>& operator>>=(K scalar);
		template<typename K>	constexpr BasicVector<3, T>& operator>>=(const BasicVector<3, K>& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>	constexpr BasicVector<3, T> operator+(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator+(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator+(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator -
	template<typename T, typename K>	constexpr BasicVector<3, T> operator-(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator-(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator-(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator *
	template<typename T, typename K>	constexpr BasicVector<3, T> operator*(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator*(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator*(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator /
	template<typename T, typename K>	constexpr BasicVector<3, T> operator/(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator/(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator/(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>	constexpr BasicVector<3, T> operator%(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator%(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator%(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator &
	template<typename T, typename K>	constexpr BasicVector<3, T> operator&(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator&(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator&(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator |
	template<typename T, typename K>	constexpr BasicVector<3, T> operator|(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator|(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator|(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator ^
	template<typename T, typename K>	constexpr BasicVector<3, T> operator^(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator^(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator^(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator <<
	template<typename T, typename K>	constexpr BasicVector<3, T> operator<<(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator<<(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator<<(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);

	// operator >>
	template<typename T, typename K>	constexpr BasicVector<3, T> operator>>(const BasicVector<3, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator>>(K lhs, const BasicVector<3, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<3, T> operator>>(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs);


	//------------- Vector3 -------------//
	template <typename T>
	struct Vector<3, T, EngineCompute::EngineComputeBasic> : public BasicVector<3, T> {

		inline constexpr Vector()																					: BasicVector<3, T>() {}
		template<typename K> inline constexpr explicit Vector(K scalar)												: BasicVector<3, T>(scalar) {}
		template<typename K1, typename K2, typename K3> inline constexpr Vector(const K1 x, const K2 y, const K3 z)	: BasicVector<3, T>(x, y, z) {}
		template<typename K> inline constexpr explicit Vector(const Vector<3, K>& vec)								: BasicVector<3, T>(vec) {}

	};

}
