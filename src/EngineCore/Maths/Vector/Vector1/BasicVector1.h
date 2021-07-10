#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- BasicVector1 -------------//
	template<typename T>
	struct BasicVector<1, T>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		union {
			T data[1];
			T x;
		};

		inline constexpr static size_t Length()	{ return 1; }
		inline constexpr static size_t Count()	{ return 1; }
		inline constexpr static size_t Size()		{ return 1; }

		inline constexpr		T& Data()							{ return x; };
		inline constexpr const	T& Data() const						{ return x; };

		inline constexpr		T& operator[](std::uint8_t /*unused*/) 			{ return x; };
		inline constexpr const	T& operator[](std::uint8_t /*unused*/) const	{ return x; };

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr BasicVector();
		template<typename K> constexpr explicit BasicVector(K scalar);
		template<typename K> constexpr explicit BasicVector(const BasicVector<1, K>& vec);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template<typename K> constexpr bool operator==(const BasicVector<1, K>& rhs);
		template<typename K> constexpr bool operator!=(const BasicVector<1, K>& rhs);



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr BasicVector<1, T>  operator+();
		// operator -I
		constexpr BasicVector<1, T>  operator-();
		// operator ++I
		constexpr BasicVector<1, T>& operator++();
		// operator --I
		constexpr BasicVector<1, T>& operator--();
		// operator I++
		constexpr BasicVector<1, T>  operator++(int);
		// operator I--
		constexpr BasicVector<1, T>  operator--(int);

		// operator =
		template<typename K>	constexpr BasicVector<1, T>& operator=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator=(const BasicVector<1, K>& vec);

		// operator +=
		template<typename K>	constexpr BasicVector<1, T>& operator+=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator+=(const BasicVector<1, K>& vec);

		// operator -=
		template<typename K>	constexpr BasicVector<1, T>& operator-=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator-=(const BasicVector<1, K>& vec);

		// operator *=
		template<typename K>	constexpr BasicVector<1, T>& operator*=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator*=(const BasicVector<1, K>& vec);

		// operator /=
		template<typename K>	constexpr BasicVector<1, T>& operator/=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator/=(const BasicVector<1, K>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// binary condition
		template<typename K>	constexpr BasicVector<1, T> operator&&(const BasicVector<1, K>& rhs);
		template<typename K>	constexpr BasicVector<1, T> operator||(const BasicVector<1, K>& rhs);

		// operator ~I
		constexpr BasicVector<1, T> operator~();

		// operator %=
		template<typename K>	constexpr BasicVector<1, T>& operator%=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator%=(const BasicVector<1, K>& vec);

		// operator &=
		template<typename K>	constexpr BasicVector<1, T>& operator&=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator&=(const BasicVector<1, K>& vec);

		// operator |=
		template<typename K>	constexpr BasicVector<1, T>& operator|=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator|=(const BasicVector<1, K>& vec);

		// operator ^=
		template<typename K>	constexpr BasicVector<1, T>& operator^=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator^=(const BasicVector<1, K>& vec);

		// operator <<=
		template<typename K>	constexpr BasicVector<1, T>& operator<<=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator<<=(const BasicVector<1, K>& vec);

		// operator >>=
		template<typename K>	constexpr BasicVector<1, T>& operator>>=(K scalar);
		template<typename K>	constexpr BasicVector<1, T>& operator>>=(const BasicVector<1, K>& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	
	// operator +
	template<typename T, typename K>	constexpr BasicVector<1, T> operator+(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator+(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator+(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator -
	template<typename T, typename K>	constexpr BasicVector<1, T> operator-(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator-(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator-(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator *
	template<typename T, typename K>	constexpr BasicVector<1, T> operator*(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator*(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator*(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator /
	template<typename T, typename K>	constexpr BasicVector<1, T> operator/(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator/(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator/(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>	constexpr BasicVector<1, T> operator%(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator%(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator%(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator &
	template<typename T, typename K>	constexpr BasicVector<1, T> operator&(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator&(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator&(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator |
	template<typename T, typename K>	constexpr BasicVector<1, T> operator|(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator|(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator|(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator ^
	template<typename T, typename K>	constexpr BasicVector<1, T> operator^(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator^(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator^(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator <<
	template<typename T, typename K>	constexpr BasicVector<1, T> operator<<(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator<<(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator<<(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);

	// operator >>
	template<typename T, typename K>	constexpr BasicVector<1, T> operator>>(const BasicVector<1, T>& lhs, K rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator>>(K lhs, const BasicVector<1, T>& rhs);
	template<typename T, typename K>	constexpr BasicVector<1, T> operator>>(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs);


	//----------------------------------------------//
	//------------- Vector1 Basic Impl -------------//
	//----------------------------------------------//
	template <typename T>
	struct Vector<1, T, EngineCompute::EngineComputeBasic> : public BasicVector<1, T> {

		inline constexpr Vector()													: BasicVector<1, T>() {}
		template<typename K> inline constexpr explicit Vector(K scalar)						: BasicVector<1, T>(scalar) {}
		template<typename K> inline constexpr explicit Vector(const BasicVector<1, K>& vec)	: BasicVector<1, T>(vec) {}

	};
}
