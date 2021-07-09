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

		inline constexpr static auto Length() -> size_t { return 2; }
		inline constexpr static auto Count() -> size_t { return 2; }
		inline constexpr static auto Size() -> size_t { return 2; }

		constexpr		auto Data(uint8_t idx) -> T&;
		constexpr auto Data(uint8_t idx) const -> const T&;

		constexpr		auto operator[](uint8_t idx) -> T&;
		constexpr auto operator[](uint8_t idx) const -> const T&;

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

		template<typename K> constexpr auto operator==(const BasicVector<2, K>& rhs) -> bool;
		template<typename K> constexpr auto operator!=(const BasicVector<2, K>& rhs) -> bool;



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr auto  operator+() -> BasicVector<2, T>;
		// operator -I
		constexpr auto  operator-() -> BasicVector<2, T>;
		// operator ++I
		constexpr auto operator++() -> BasicVector<2, T>&;
		// operator --I
		constexpr auto operator--() -> BasicVector<2, T>&;
		// operator I++
		constexpr auto  operator++(int) -> BasicVector<2, T>;
		// operator I--
		constexpr auto  operator--(int) -> BasicVector<2, T>;

		// operator =
		template<typename K>	constexpr auto operator=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator +=
		template<typename K>	constexpr auto operator+=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator+=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator -=
		template<typename K>	constexpr auto operator-=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator-=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator *=
		template<typename K>	constexpr auto operator*=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator*=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator /=
		template<typename K>	constexpr auto operator/=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator/=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// binary condition
		template<typename K>	constexpr auto operator&&(const BasicVector<2, K>& rhs) -> BasicVector<2, T>;
		template<typename K>	constexpr auto operator||(const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

		// operator ~I
		constexpr auto operator~() -> BasicVector<2, T>;

		// operator %=
		template<typename K>	constexpr auto operator%=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator%=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator &=
		template<typename K>	constexpr auto operator&=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator&=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator |=
		template<typename K>	constexpr auto operator|=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator|=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator ^=
		template<typename K>	constexpr auto operator^=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator^=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator <<=
		template<typename K>	constexpr auto operator<<=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator<<=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;

		// operator >>=
		template<typename K>	constexpr auto operator>>=(K scalar) -> BasicVector<2, T>&;
		template<typename K>	constexpr auto operator>>=(const BasicVector<2, K>& vec) -> BasicVector<2, T>&;
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator+(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator -
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator-(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator *
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator*(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator /
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator/(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator%(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator &
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator&(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator |
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator|(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator ^
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator^(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator <<
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator<<(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;

	// operator >>
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<2, T>& lhs, K rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator>>(K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T>;
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T>;


	//------------- Vector2 -------------//
	template <typename T>
	struct Vector<2, T, EngineCompute::EngineComputeBasic> : public BasicVector<2, T> {

		inline constexpr Vector()															: BasicVector<2, T>() {}
		template<typename K> inline constexpr explicit Vector(const K scalar)						: BasicVector<2, T>(scalar) {}
		template<typename K1, typename K2> inline constexpr Vector(const K1 x, const K2 y)	: BasicVector<2, T>(x, y) {}
		template<typename K> inline constexpr explicit Vector(const Vector<2, K>& vec)				: BasicVector<2, T>(vec) {}

	};

}
