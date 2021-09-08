#pragma once

#include "../Vector.h"

namespace EngineCore {

	template<typename T>
	struct BasicVector<1, T>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//
		union {
			struct { T x; };
		};

		inline constexpr static size_t Length() { return 1; }
		inline constexpr static size_t Count()	{ return 1; }
		inline constexpr static size_t Size()	{ return 1; }

		inline constexpr T& Data()				{ return x; };
		constexpr const T& Data() const			{ return x; };

		constexpr T& operator[](uint8_t)				{ return x; };
		constexpr const T& operator[](uint8_t) const	{ return x; };



		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		template<typename K> constexpr Vector(K scalar);
		template<typename K> constexpr Vector(const BasicVector<1, K>& vec);



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
		constexpr Vector<1, T, ComputeAlgorithm>  operator+();
		// operator -I
		constexpr Vector<1, T, ComputeAlgorithm>  operator-();
		// operator ++I
		constexpr Vector<1, T, ComputeAlgorithm>& operator++();
		// operator --I
		constexpr Vector<1, T, ComputeAlgorithm>& operator--();
		// operator I++
		constexpr Vector<1, T, ComputeAlgorithm>  operator++(int);
		// operator I--
		constexpr Vector<1, T, ComputeAlgorithm>  operator--(int);

		// operator =
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator +=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator+=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator+=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator -=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator-=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator-=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator *=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator*=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator*=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator /=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator/=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator/=(const Vector<1, K, ComputeAlgorithmClient>& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator ~I
		constexpr Vector<1, T, ComputeAlgorithm> operator~();

		constexpr Vector<1, T, ComputeAlgorithm> operator&&(const Vector<1, T, ComputeAlgorithm>& rhs);
		constexpr Vector<1, T, ComputeAlgorithm> operator||(const Vector<1, T, ComputeAlgorithm>& rhs);

		// operator %=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator%=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator%=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator &=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator&=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator&=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator |=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator|=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator|=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator ^=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator^=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator^=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator <<=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator<<=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator<<=(const Vector<1, K, ComputeAlgorithmClient>& vec);

		// operator >>=
		template<typename K>									constexpr Vector<1, T, ComputeAlgorithm>& operator>>=(const K scalar);
		template<typename K, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm>& operator>>=(const Vector<1, K, ComputeAlgorithmClient>& vec);
	};



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator+(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator+(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator+(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator -
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator-(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator-(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator-(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator *
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator*(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator*(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator*(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator /
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator/(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator/(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator/(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator%(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator%(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator%(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator &
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator&(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator&(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator&(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator |
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator|(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator|(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator|(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator ^
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator^(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator^(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator^(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator <<
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator<<(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator<<(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator<<(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);

	// operator >>
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator>>(const Vector<1, T, ComputeAlgorithm>& lhs, const K rhs);
	template<typename T, typename K, typename ComputeAlgorithm>										constexpr Vector<1, T, ComputeAlgorithm> operator>>(const K lhs, const Vector<1, T, ComputeAlgorithm>& rhs);
	template<typename T, typename K, typename ComputeAlgorithm, typename ComputeAlgorithmClient>	constexpr Vector<1, T, ComputeAlgorithm> operator>>(const Vector<1, T, ComputeAlgorithm>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs);
*/

}
