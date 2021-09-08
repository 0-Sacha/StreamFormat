#pragma once

#include "../Vector.h"

namespace EngineCore {

	template<typename T, typename ComputeAlgorithm>
	struct Vector<2, T, ComputeAlgorithm>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//
		union {
			struct { T x, y; };
		};

		inline constexpr static size_t Length() { return 2; }
		inline constexpr static size_t Count() { return 2; }
		inline constexpr static size_t Size() { return 2; }

		constexpr T& Data(const uint8_t idx);
		constexpr const T& Data(const uint8_t idx) const;

		constexpr T& operator[](const uint8_t idx);
		constexpr const T& operator[](const uint8_t idx) const;



		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//
		constexpr Vector();
		template<typename K> constexpr Vector(K scalar);
		template<typename K1, typename K2> constexpr Vector(K1 x, K2 y);
		template<typename K> constexpr Vector(const Vector<2, K>& vec);



		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//

		// From Vector<1, K>
		template<typename K> constexpr Vector(const Vector<1, K>& vec);
		template<typename K1, typename K2> constexpr Vector(const Vector<1, K1>& x, const K2 y);
		template<typename K1, typename K2> constexpr Vector(const K1 x, const Vector<1, K2>& y);
		template<typename K1, typename K2> constexpr Vector(const Vector<1, K1>& x, const Vector<1, K2>& y);



		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const Vector<2, T>& rhs);
		constexpr bool operator!=(const Vector<2, T>& rhs);



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<2, T> operator+();
		// operator -I
		constexpr Vector<2, T> operator-();
		// operator ++I
		template<typename K> constexpr Vector<2, T>& operator++();
		// operator --I
		template<typename K> constexpr Vector<2, T>& operator--();
		// operator I++
		template<typename K> constexpr Vector<2, T>  operator++(int);
		// operator I--
		template<typename K> constexpr Vector<2, T>  operator--(int);

		// operator =
		template<typename K> constexpr Vector<2, T>& operator=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator=(const Vector<2, K>& vec);

		// operator +=
		template<typename K> constexpr Vector<2, T>& operator+=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator+=(const Vector<2, K>& vec);

		// operator -=
		template<typename K> constexpr Vector<2, T>& operator-=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator-=(const Vector<2, K>& vec);

		// operator *=
		template<typename K> constexpr Vector<2, T>& operator*=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator*=(const Vector<2, K>& vec);

		// operator /=
		template<typename K> constexpr Vector<2, T>& operator/=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator/=(const Vector<2, K>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator ~I
		constexpr Vector<2, T> operator~();

		constexpr Vector<2, T> operator&&(const Vector<2, T>& rhs);
		constexpr Vector<2, T> operator||(const Vector<2, T>& rhs);

		// operator %=
		template<typename K> constexpr Vector<2, T>& operator%=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator%=(const Vector<2, K>& vec);

		// operator &=
		template<typename K> constexpr Vector<2, T>& operator&=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator&=(const Vector<2, K>& vec);

		// operator |=
		template<typename K> constexpr Vector<2, T>& operator|=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator|=(const Vector<2, K>& vec);

		// operator ^=
		template<typename K> constexpr Vector<2, T>& operator^=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator^=(const Vector<2, K>& vec);

		// operator <<=
		template<typename K> constexpr Vector<2, T>& operator<<=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator<<=(const Vector<2, K>& vec);

		// operator >>=
		template<typename K> constexpr Vector<2, T>& operator>>=(const K scalar);
		template<typename K> constexpr Vector<2, T>& operator>>=(const Vector<2, K>& vec);
	};



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K> constexpr Vector<2, T> operator+(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator+(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator+(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator -
	template<typename T, typename K> constexpr Vector<2, T> operator-(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator-(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator-(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator *
	template<typename T, typename K> constexpr Vector<2, T> operator*(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator*(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator*(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator /
	template<typename T, typename K> constexpr Vector<2, T> operator/(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator/(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator/(const Vector<2, T>& lhs, const Vector<2, K>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K> constexpr Vector<2, T> operator%(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator%(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator%(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator &
	template<typename T, typename K> constexpr Vector<2, T> operator&(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator&(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator&(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator |
	template<typename T, typename K> constexpr Vector<2, T> operator|(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator|(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator|(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator ^
	template<typename T, typename K> constexpr Vector<2, T> operator^(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator^(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator^(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator <<
	template<typename T, typename K> constexpr Vector<2, T> operator<<(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator<<(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator<<(const Vector<2, T>& lhs, const Vector<2, K>& rhs);

	// operator >>
	template<typename T, typename K> constexpr Vector<2, T> operator>>(const Vector<2, T>& lhs, const K rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator>>(const K lhs, const Vector<2, T>& rhs);
	template<typename T, typename K> constexpr Vector<2, T> operator>>(const Vector<2, T>& lhs, const Vector<2, K>& rhs);
}


#include "Vector2Type.inl"
