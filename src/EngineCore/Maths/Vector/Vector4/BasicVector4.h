#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- BasicVector4 -------------//
	template<typename T>
	struct BasicVector<4, T>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		union {
			T data[2];
			struct { T x, y, z, w; };
		};

		inline constexpr static auto Length() -> size_t { return 2; }
		inline constexpr static auto Count() -> size_t	{ return 2; }
		inline constexpr static auto Size() -> size_t	{ return 2; }

		constexpr		auto Data(uint8_t idx) -> T&;
		[[nodiscard]] constexpr auto Data(uint8_t idx) const -> const T&;

		constexpr		auto operator[](uint8_t idx) -> T&;
		constexpr auto operator[](uint8_t idx) const -> const T&;

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr BasicVector();
		template<typename K> constexpr explicit BasicVector(K scalar);
		template<typename K1, typename K2, typename K3, typename K4> constexpr BasicVector(K1 x, K2 y ,K3 z, K4 w);
		template<typename K> constexpr explicit BasicVector(const BasicVector<4, K>& vec);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template<typename K> constexpr auto operator==(const BasicVector<4, K>& rhs) -> bool;
		template<typename K> constexpr auto operator!=(const BasicVector<4, K>& rhs) -> bool;



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr auto  operator+() -> BasicVector<4, T>;
		// operator -I
		constexpr auto  operator-() -> BasicVector<4, T>;
		// operator ++I
		constexpr auto operator++() -> BasicVector<4, T>&;
		// operator --I
		constexpr auto operator--() -> BasicVector<4, T>&;
		// operator I++
		constexpr auto  operator++(int) -> BasicVector<4, T>;
		// operator I--
		constexpr auto  operator--(int) -> BasicVector<4, T>;

		// operator =
		template<typename K>	constexpr auto operator=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator +=
		template<typename K>	constexpr auto operator+=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator+=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator -=
		template<typename K>	constexpr auto operator-=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator-=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator *=
		template<typename K>	constexpr auto operator*=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator*=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator /=
		template<typename K>	constexpr auto operator/=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator/=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// binary condition
		template<typename K>	constexpr auto operator&&(const BasicVector<4, K>& rhs) -> BasicVector<4, T>;
		template<typename K>	constexpr auto operator||(const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

		// operator ~I
		constexpr auto operator~() -> BasicVector<4, T>;

		// operator %=
		template<typename K>	constexpr auto operator%=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator%=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator &=
		template<typename K>	constexpr auto operator&=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator&=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator |=
		template<typename K>	constexpr auto operator|=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator|=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator ^=
		template<typename K>	constexpr auto operator^=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator^=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator <<=
		template<typename K>	constexpr auto operator<<=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator<<=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;

		// operator >>=
		template<typename K>	constexpr auto operator>>=(K scalar) -> BasicVector<4, T>&;
		template<typename K>	constexpr auto operator>>=(const BasicVector<4, K>& vec) -> BasicVector<4, T>&;
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator+(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator -
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator-(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator *
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator*(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator /
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator/(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator%(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator &
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator&(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator |
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator|(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator ^
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator^(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator <<
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator<<(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;

	// operator >>
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<4, T>& lhs, K rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator>>(K lhs, const BasicVector<4, T>& rhs) -> BasicVector<4, T>;
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<4, T>& lhs, const BasicVector<4, K>& rhs) -> BasicVector<4, T>;


	//------------- Vector4 -------------//
	template <typename T>
	struct Vector<4, T, EngineCompute::EngineComputeBasic> : public BasicVector<4, T> {

		inline constexpr Vector()																												: BasicVector<4, T>() {}
		template<typename K> inline constexpr explicit Vector(const K scalar)																			: BasicVector<4, T>(scalar) {}
		template<typename K1, typename K2, typename K3, typename K4> inline constexpr Vector(const K1 x, const K2 y, const K3 z, const K4 w)	: BasicVector<4, T>(x, y, z, w) {}
		template<typename K> inline constexpr explicit Vector(const Vector<4, K>& vec)																	: BasicVector<4, T>(vec) {}

	};

}
