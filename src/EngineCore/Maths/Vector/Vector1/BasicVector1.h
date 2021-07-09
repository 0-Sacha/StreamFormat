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

		inline constexpr static auto Length() -> size_t { return 1; }
		inline constexpr static auto Count() -> size_t	{ return 1; }
		inline constexpr static auto Size() -> size_t	{ return 1; }

		inline constexpr		auto Data() -> T&							{ return x; };
		inline constexpr auto Data() const -> const	T&						{ return x; };

		inline constexpr		auto operator[](std::uint8_t /*unused*/) -> T&			{ return x; };
		inline constexpr auto operator[](std::uint8_t /*unused*/) const -> const	T&	{ return x; };

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

		template<typename K> constexpr auto operator==(const BasicVector<1, K>& rhs) -> bool;
		template<typename K> constexpr auto operator!=(const BasicVector<1, K>& rhs) -> bool;



		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr auto  operator+() -> BasicVector<1, T>;
		// operator -I
		constexpr auto  operator-() -> BasicVector<1, T>;
		// operator ++I
		constexpr auto operator++() -> BasicVector<1, T>&;
		// operator --I
		constexpr auto operator--() -> BasicVector<1, T>&;
		// operator I++
		constexpr auto  operator++(int) -> BasicVector<1, T>;
		// operator I--
		constexpr auto  operator--(int) -> BasicVector<1, T>;

		// operator =
		template<typename K>	constexpr auto operator=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator +=
		template<typename K>	constexpr auto operator+=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator+=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator -=
		template<typename K>	constexpr auto operator-=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator-=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator *=
		template<typename K>	constexpr auto operator*=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator*=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator /=
		template<typename K>	constexpr auto operator/=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator/=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// binary condition
		template<typename K>	constexpr auto operator&&(const BasicVector<1, K>& rhs) -> BasicVector<1, T>;
		template<typename K>	constexpr auto operator||(const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

		// operator ~I
		constexpr auto operator~() -> BasicVector<1, T>;

		// operator %=
		template<typename K>	constexpr auto operator%=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator%=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator &=
		template<typename K>	constexpr auto operator&=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator&=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator |=
		template<typename K>	constexpr auto operator|=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator|=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator ^=
		template<typename K>	constexpr auto operator^=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator^=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator <<=
		template<typename K>	constexpr auto operator<<=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator<<=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;

		// operator >>=
		template<typename K>	constexpr auto operator>>=(K scalar) -> BasicVector<1, T>&;
		template<typename K>	constexpr auto operator>>=(const BasicVector<1, K>& vec) -> BasicVector<1, T>&;
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	
	// operator +
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator+(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator+(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator -
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator-(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator-(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator *
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator*(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator*(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator /
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator/(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator/(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator%(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator%(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator &
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator&(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator&(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator |
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator|(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator|(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator ^
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator^(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator^(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator <<
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator<<(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator<<(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;

	// operator >>
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<1, T>& lhs, K rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator>>(K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T>;
	template<typename T, typename K>	constexpr auto operator>>(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T>;


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
