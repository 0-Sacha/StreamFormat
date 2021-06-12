#pragma once

#include "../Vector.h"

namespace EngineCore {

	template<typename T>
	struct Vector<3, T>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//
		union { T x; };
		union { T y; };
		union { T z; };

		inline constexpr static size_t Length() { return 3; }
		inline constexpr static size_t Count() { return 3; }
		inline constexpr static size_t Size() { return 3; }

		constexpr T& Data(const uint8_t idx);
		constexpr const T& Data(const uint8_t idx) const;

		constexpr T& operator[](const uint8_t idx);
		constexpr const T& operator[](const uint8_t idx) const;



		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//
		constexpr Vector();
		template<typename K> constexpr Vector(K scalar);
		template<typename K1, typename K2, typename K3> constexpr Vector(K1 x, K2 y, K3 z);
		template<typename K> constexpr Vector(const Vector<3, K>& vec);



		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//


		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const Vector<3, T>& rhs);
		constexpr bool operator!=(const Vector<3, T>& rhs);



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<3, T> operator+();
		// operator -I
		constexpr Vector<3, T> operator-();
		// operator ++I
		template<typename K> constexpr Vector<3, T>& operator++();
		// operator --I
		template<typename K> constexpr Vector<3, T>& operator--();
		// operator I++
		template<typename K> constexpr Vector<3, T>  operator++(int);
		// operator I--
		template<typename K> constexpr Vector<3, T>  operator--(int);

		// operator =
		template<typename K> constexpr Vector<3, T>& operator=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator=(const Vector<3, K>& vec);

		// operator +=
		template<typename K> constexpr Vector<3, T>& operator+=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator+=(const Vector<3, K>& vec);

		// operator -=
		template<typename K> constexpr Vector<3, T>& operator-=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator-=(const Vector<3, K>& vec);

		// operator *=
		template<typename K> constexpr Vector<3, T>& operator*=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator*=(const Vector<3, K>& vec);

		// operator /=
		template<typename K> constexpr Vector<3, T>& operator/=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator/=(const Vector<3, K>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator ~I
		constexpr Vector<3, T> operator~();

		constexpr Vector<3, T> operator&&(const Vector<3, T>& rhs);
		constexpr Vector<3, T> operator||(const Vector<3, T>& rhs);

		// operator %=
		template<typename K> constexpr Vector<3, T>& operator%=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator%=(const Vector<3, K>& vec);

		// operator &=
		template<typename K> constexpr Vector<3, T>& operator&=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator&=(const Vector<3, K>& vec);

		// operator |=
		template<typename K> constexpr Vector<3, T>& operator|=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator|=(const Vector<3, K>& vec);

		// operator ^=
		template<typename K> constexpr Vector<3, T>& operator^=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator^=(const Vector<3, K>& vec);

		// operator <<=
		template<typename K> constexpr Vector<3, T>& operator<<=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator<<=(const Vector<3, K>& vec);

		// operator >>=
		template<typename K> constexpr Vector<3, T>& operator>>=(const K scalar);
		template<typename K> constexpr Vector<3, T>& operator>>=(const Vector<3, K>& vec);
	};



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K> constexpr Vector<3, T> operator+(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator+(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator+(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator -
	template<typename T, typename K> constexpr Vector<3, T> operator-(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator-(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator-(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator *
	template<typename T, typename K> constexpr Vector<3, T> operator*(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator*(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator*(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator /
	template<typename T, typename K> constexpr Vector<3, T> operator/(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator/(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator/(const Vector<3, T>& lhs, const Vector<3, K>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K> constexpr Vector<3, T> operator%(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator%(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator%(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator &
	template<typename T, typename K> constexpr Vector<3, T> operator&(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator&(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator&(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator |
	template<typename T, typename K> constexpr Vector<3, T> operator|(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator|(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator|(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator ^
	template<typename T, typename K> constexpr Vector<3, T> operator^(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator^(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator^(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator <<
	template<typename T, typename K> constexpr Vector<3, T> operator<<(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator<<(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator<<(const Vector<3, T>& lhs, const Vector<3, K>& rhs);

	// operator >>
	template<typename T, typename K> constexpr Vector<3, T> operator>>(const Vector<3, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator>>(const K lhs, const Vector<3, T>& rhs);
	template<typename T, typename K> constexpr Vector<3, T> operator>>(const Vector<3, T>& lhs, const Vector<3, K>& rhs);
}


#include "Vector3Type.inl"
