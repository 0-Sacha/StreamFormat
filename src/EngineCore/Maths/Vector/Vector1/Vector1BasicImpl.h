#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- Vector1 -------------//
	template <typename Type>
	struct Vector<1, Type, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType = Type;

		union {
			std::array<ValueType, 1> data;
			ValueType x;
		};

		inline constexpr static std::size_t Length()	{ return 1; }
		inline constexpr static std::size_t Count()		{ return 1; }
		inline constexpr static std::size_t Size()		{ return 1; }

		inline constexpr ValueType& operator[](const std::size_t idx)				{ ENGINE_CORE_ASSERT(idx < 1); return data[0]; }
		inline constexpr const ValueType& operator[](const std::size_t idx) const	{ ENGINE_CORE_ASSERT(idx < 1); return data[0]; }

		inline constexpr		std::array<ValueType, 1>& GetArray()		{ return data; }
		inline constexpr const	std::array<ValueType, 1>& GetArray() const	{ return data; }

		//--------------------------------------------//
		//------------- Basic Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		constexpr Vector(const std::convertible_to<ValueType> auto scalar); // S
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& vec);	// V1

		//--------------------------------------------------------------------//
		//------------- Conversion From Other Vector Constructor -------------//
		//--------------------------------------------------------------------//

		// From Vector<2, T, C>
		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& vec);	// V2
		// From Vector<3, T, C>
		constexpr Vector(const VectorConvertibleTo<3, ValueType> auto& vec);	// V3
		// From Vector<4, T, C>
		constexpr Vector(const VectorConvertibleTo<4, ValueType> auto& vec);	// V4



		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//


		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const VectorConvertibleTo<1, ValueType> auto& rhs);
		constexpr bool operator!=(const VectorConvertibleTo<1, ValueType> auto& rhs);

		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator&&(const VectorConvertibleTo<1, ValueType> auto& rhs);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator||(const VectorConvertibleTo<1, ValueType> auto& rhs);


		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>  operator+() const;
		// operator -I
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>  operator-() const;
		// operator ~I
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>  operator~() const;

		// operator ++I
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>  operator--(int);

		// operator =
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator=(const VectorConvertibleTo<1, ValueType> auto& vec);

		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator=(const VectorConvertibleTo<2, ValueType> auto& vec);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator=(const VectorConvertibleTo<3, ValueType> auto& vec);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator +=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator -=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator *=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator /=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const VectorConvertibleTo<1, ValueType> auto& vec);

		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//
		// 
		// operator %=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator &=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator |=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator ^=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator <<=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator >>=
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const VectorConvertibleTo<1, ValueType> auto& vec);
	};
	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator -
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator *
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator /
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator &
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator |
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator ^
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator <<
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator >>
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);
}









