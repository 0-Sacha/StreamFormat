#pragma once

#include "Vector.h"


namespace EngineCore {

	template <std::size_t COUNT, typename Type>
	struct Vector<COUNT, Type, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType			= Type;
		using ComputeAlgorithm	= EngineCompute::EngineComputeBasic;

		using M_Type			= Vector<COUNT, ValueType, ComputeAlgorithm>;
		using ValueArrayType	= std::array<ValueType, COUNT>;
		
		ValueArrayType data;

		inline constexpr static std::size_t Length()	{ return COUNT; }
		inline constexpr static std::size_t Count()		{ return COUNT; }
		inline constexpr static std::size_t Size()		{ return COUNT; }


		inline constexpr	   ValueType& operator[](const std::size_t idx)			{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const ValueType& operator[](const std::size_t idx) const	{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }

		inline constexpr		std::array<ValueType, COUNT>& GetArray()		{ return data; }
		inline constexpr const	std::array<ValueType, COUNT>& GetArray() const	{ return data; }

		//--------------------------------------------//
		//------------- Basic Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		constexpr Vector(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& vec);

		constexpr Vector(const std::convertible_to<ValueType> auto ... value);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//
		constexpr Vector(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//




		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const VectorConvertibleTo<COUNT, ValueType> auto& rhs);
		constexpr bool operator!=(const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator&&(const VectorConvertibleTo<COUNT, ValueType> auto& rhs);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator||(const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>  operator+() const;
		// operator -I
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>  operator-() const;
		// operator ~I
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>  operator~() const;

		// operator ++I
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>  operator--(int);

		// operator =
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator +=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator -=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator *=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator /=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator %=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator &=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator |=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator ^=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator <<=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);

		// operator >>=
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const VectorConvertibleTo<COUNT, ValueType> auto& vec);
	};
	
	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	
	// operator +
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator -
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator *
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator /
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	
	// operator %
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator &
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator |
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator ^
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator <<
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);

	// operator >>
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <std::size_t COUNT, typename ValueType> constexpr Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<COUNT, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<COUNT, ValueType> auto& rhs);
	
}



