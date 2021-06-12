#pragma once

#include "../Vector.h"

namespace EngineCore {

	template<typename T>
	struct Vector<1, T>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//
		union { T x; };

		inline constexpr static size_t Length() { return 1; }
		inline constexpr static size_t Count() { return 1; }
		inline constexpr static size_t Size() { return 1; }

		inline constexpr T& Data() { return x; };
		constexpr const T& Data() const { return x; };

		constexpr T& operator[]() { return x; };
		constexpr const T& operator[]() const { return x; };



		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		template<typename K> constexpr Vector(K scalar);
		template<typename K> constexpr Vector(const Vector<1, K>& vec);



		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const Vector<1, T>& rhs);
		constexpr bool operator!=(const Vector<1, T>& rhs);



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<1, T> operator+();
		// operator -I
		constexpr Vector<1, T> operator-();
		// operator ++I
		template<typename K> constexpr Vector<1, T>& operator++();
		// operator --I
		template<typename K> constexpr Vector<1, T>& operator--();
		// operator I++
		template<typename K> constexpr Vector<1, T>  operator++(int);
		// operator I--
		template<typename K> constexpr Vector<1, T>  operator--(int);

		// operator =
		template<typename K> constexpr Vector<1, T>& operator=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator=(const Vector<1, K>& vec);

		// operator +=
		template<typename K> constexpr Vector<1, T>& operator+=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator+=(const Vector<1, K>& vec);

		// operator -=
		template<typename K> constexpr Vector<1, T>& operator-=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator-=(const Vector<1, K>& vec);

		// operator *=
		template<typename K> constexpr Vector<1, T>& operator*=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator*=(const Vector<1, K>& vec);

		// operator /=
		template<typename K> constexpr Vector<1, T>& operator/=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator/=(const Vector<1, K>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator ~I
		constexpr Vector<1, T> operator~();

		constexpr Vector<1, T> operator&&(const Vector<1, T>& rhs);
		constexpr Vector<1, T> operator||(const Vector<1, T>& rhs);

		// operator %=
		template<typename K> constexpr Vector<1, T>& operator%=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator%=(const Vector<1, K>& vec);

		// operator &=
		template<typename K> constexpr Vector<1, T>& operator&=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator&=(const Vector<1, K>& vec);

		// operator |=
		template<typename K> constexpr Vector<1, T>& operator|=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator|=(const Vector<1, K>& vec);

		// operator ^=
		template<typename K> constexpr Vector<1, T>& operator^=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator^=(const Vector<1, K>& vec);

		// operator <<=
		template<typename K> constexpr Vector<1, T>& operator<<=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator<<=(const Vector<1, K>& vec);

		// operator >>=
		template<typename K> constexpr Vector<1, T>& operator>>=(const K scalar);
		template<typename K> constexpr Vector<1, T>& operator>>=(const Vector<1, K>& vec);
	};



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K> constexpr Vector<1, T> operator+(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator+(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator+(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator -
	template<typename T, typename K> constexpr Vector<1, T> operator-(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator-(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator-(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator *
	template<typename T, typename K> constexpr Vector<1, T> operator*(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator*(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator*(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator /
	template<typename T, typename K> constexpr Vector<1, T> operator/(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator/(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator/(const Vector<1, T>& lhs, const Vector<1, K>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K> constexpr Vector<1, T> operator%(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator%(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator%(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator &
	template<typename T, typename K> constexpr Vector<1, T> operator&(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator&(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator&(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator |
	template<typename T, typename K> constexpr Vector<1, T> operator|(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator|(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator|(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator ^
	template<typename T, typename K> constexpr Vector<1, T> operator^(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator^(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator^(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator <<
	template<typename T, typename K> constexpr Vector<1, T> operator<<(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator<<(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator<<(const Vector<1, T>& lhs, const Vector<1, K>& rhs);

	// operator >>
	template<typename T, typename K> constexpr Vector<1, T> operator>>(const Vector<1, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator>>(const K lhs, const Vector<1, T>& rhs);
	template<typename T, typename K> constexpr Vector<1, T> operator>>(const Vector<1, T>& lhs, const Vector<1, K>& rhs);
}


#include "Vector1Type.inl"
