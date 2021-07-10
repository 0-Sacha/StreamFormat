#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- BasicVector2 -------------//
	template<typename T>
	struct BasicVector<2, T>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		union {
			T data[2];
			struct { T x, y; };
			struct { T u, v; };
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
		template<typename K1, typename K2> constexpr BasicVector(K1 x, K2 y);
		template<typename K> constexpr explicit BasicVector(const BasicVector<2, K>& vec);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template<typename K> constexpr bool operator==(const BasicVector<2, K>& rhs);
		template<typename K> constexpr bool operator!=(const BasicVector<2, K>& rhs);



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr BasicVector<2, T>  operator+();
		// operator -I
		constexpr BasicVector<2, T>  operator-();
		// operator ++I
		constexpr BasicVector<2, T>& operator++();
		// operator --I
		constexpr BasicVector<2, T>& operator--();
		// operator I++
		constexpr BasicVector<2, T>  operator++(int);
		// operator I--
		constexpr BasicVector<2, T>  operator--(int);

		// operator =
		template<typename K>	constexpr BasicVector<2, T>& operator=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator=(const BasicVector<2, K>& vec);

		// operator +=
		template<typename K>	constexpr BasicVector<2, T>& operator+=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator+=(const BasicVector<2, K>& vec);

		// operator -=
		template<typename K>	constexpr BasicVector<2, T>& operator-=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator-=(const BasicVector<2, K>& vec);

		// operator *=
		template<typename K>	constexpr BasicVector<2, T>& operator*=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator*=(const BasicVector<2, K>& vec);

		// operator /=
		template<typename K>	constexpr BasicVector<2, T>& operator/=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator/=(const BasicVector<2, K>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// binary condition
		template<typename K>	constexpr BasicVector<2, T> operator&&(const BasicVector<2, K>& rhs);
		template<typename K>	constexpr BasicVector<2, T> operator||(const BasicVector<2, K>& rhs);

		// operator ~I
		constexpr BasicVector<2, T> operator~();

		// operator %=
		template<typename K>	constexpr BasicVector<2, T>& operator%=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator%=(const BasicVector<2, K>& vec);

		// operator &=
		template<typename K>	constexpr BasicVector<2, T>& operator&=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator&=(const BasicVector<2, K>& vec);

		// operator |=
		template<typename K>	constexpr BasicVector<2, T>& operator|=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator|=(const BasicVector<2, K>& vec);

		// operator ^=
		template<typename K>	constexpr BasicVector<2, T>& operator^=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator^=(const BasicVector<2, K>& vec);

		// operator <<=
		template<typename K>	constexpr BasicVector<2, T>& operator<<=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator<<=(const BasicVector<2, K>& vec);

		// operator >>=
		template<typename K>	constexpr BasicVector<2, T>& operator>>=(K scalar);
		template<typename K>	constexpr BasicVector<2, T>& operator>>=(const BasicVector<2, K>& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>	constexpr BasicVector<2, T> operator+(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator+(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator+(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator -
	template<typename T, typename K>	constexpr BasicVector<2, T> operator-(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator-(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator-(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator *
	template<typename T, typename K>	constexpr BasicVector<2, T> operator*(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator*(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator*(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator /
	template<typename T, typename K>	constexpr BasicVector<2, T> operator/(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator/(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator/(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>	constexpr BasicVector<2, T> operator%(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator%(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator%(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator &
	template<typename T, typename K>	constexpr BasicVector<2, T> operator&(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator&(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator&(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator |
	template<typename T, typename K>	constexpr BasicVector<2, T> operator|(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator|(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator|(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator ^
	template<typename T, typename K>	constexpr BasicVector<2, T> operator^(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator^(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator^(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator <<
	template<typename T, typename K>	constexpr BasicVector<2, T> operator<<(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator<<(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator<<(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);

	// operator >>
	template<typename T, typename K>	constexpr BasicVector<2, T> operator>>(const BasicVector<2, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator>>(K lhs, const BasicVector<2, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<2, T> operator>>(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs);


	//------------- Vector2 -------------//
	template <typename T>
	struct Vector<2, T, EngineCompute::EngineComputeBasic> : public BasicVector<2, T> {

		inline constexpr Vector()															: BasicVector<2, T>() {}
		template<typename K> inline constexpr explicit Vector(const K scalar)				: BasicVector<2, T>(scalar) {}
		template<typename K1, typename K2> inline constexpr Vector(const K1 x, const K2 y)	: BasicVector<2, T>(x, y) {}
		template<typename K> inline constexpr explicit Vector(const Vector<2, K>& vec)		: BasicVector<2, T>(vec) {}

	};

}
