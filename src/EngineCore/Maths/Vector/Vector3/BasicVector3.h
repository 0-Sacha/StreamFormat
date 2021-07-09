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

		inline constexpr static auto Length() -> size_t { return 2; }
		inline constexpr static auto Count() -> size_t	{ return 2; }
		inline constexpr static auto Size() -> size_t	{ return 2; }

		constexpr auto Data(uint8_t idx) -> T&;
		constexpr auto Data(uint8_t idx) const -> const T&;

		constexpr auto operator[](uint8_t idx) -> T&;
		constexpr auto operator[](uint8_t idx) const -> const T&;

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

		template<typename K> constexpr auto operator==(const BasicVector<3, K>& rhs) -> bool;
		template<typename K> constexpr auto operator!=(const BasicVector<3, K>& rhs) -> bool;



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr auto  operator+() -> BasicVector<3, T>;
		// operator -I
		constexpr auto  operator-() -> BasicVector<3, T>;
		// operator ++I
		constexpr auto operator++() -> BasicVector<3, T>&;
		// operator --I
		constexpr auto operator--() -> BasicVector<3, T>&;
		// operator I++
		constexpr auto  operator++(int) -> BasicVector<3, T>;
		// operator I--
		constexpr auto  operator--(int) -> BasicVector<3, T>;

		// operator =
		template<typename K>	constexpr auto operator=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator +=
		template<typename K>	constexpr auto operator+=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator+=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator -=
		template<typename K>	constexpr auto operator-=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator-=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator *=
		template<typename K>	constexpr auto operator*=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator*=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator /=
		template<typename K>	constexpr auto operator/=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator/=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// binary condition
		template<typename K>	constexpr auto operator&&(const BasicVector<3, K>& rhs) -> BasicVector<3, T>;
		template<typename K>	constexpr auto operator||(const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

		// operator ~I
		constexpr auto operator~() -> BasicVector<3, T>;

		// operator %=
		template<typename K>	constexpr auto operator%=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator%=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator &=
		template<typename K>	constexpr auto operator&=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator&=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator |=
		template<typename K>	constexpr auto operator|=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator|=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator ^=
		template<typename K>	constexpr auto operator^=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator^=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator <<=
		template<typename K>	constexpr auto operator<<=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator<<=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;

		// operator >>=
		template<typename K>	constexpr auto operator>>=(K scalar) -> BasicVector<3, T>&;
		template<typename K>	constexpr auto operator>>=(const BasicVector<3, K>& vec) -> BasicVector<3, T>&;
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator+(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator -
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator-(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator *
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator*(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator /
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator/(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator%(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator &
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator&(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator |
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator|(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator ^
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator^(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator <<
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator<<(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;

	// operator >>
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<3, T>& lhs, K rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator>>(K lhs, const BasicVector<3, T>& rhs) -> BasicVector<3, T>;
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) -> BasicVector<3, T>;


	//------------- Vector3 -------------//
	template <typename T>
	struct Vector<3, T, EngineCompute::EngineComputeBasic> : public BasicVector<3, T> {

		inline constexpr Vector()																					: BasicVector<3, T>() {}
		template<typename K> inline constexpr explicit Vector(K scalar)														: BasicVector<3, T>(scalar) {}
		template<typename K1, typename K2, typename K3> inline constexpr Vector(const K1 x, const K2 y, const K3 z)	: BasicVector<3, T>(x, y, z) {}
		template<typename K> inline constexpr explicit Vector(const Vector<3, K>& vec)										: BasicVector<3, T>(vec) {}

	};

}
