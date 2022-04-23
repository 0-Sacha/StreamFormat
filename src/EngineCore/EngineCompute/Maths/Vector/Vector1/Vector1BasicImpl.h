#pragma once

#include "../Vector.h"

namespace EngineCore::EngineCompute {

	//------------- Vector1 -------------//
	template <typename Type>
	struct Vector<1, Type, Detail::EngineComputeType::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		static constexpr std::size_t COUNT = 1;
		using ValueType			= Type;
		using ComputeAlgorithm	= Detail::EngineComputeType::EngineComputeBasic;

		using M_Type			= Vector<COUNT, ValueType, ComputeAlgorithm>;
		using ValueArrayType	= std::array<ValueType, COUNT>;

		union {
			ValueArrayType data;
			ValueType x;
		};

		inline constexpr static std::size_t Length()	{ return COUNT; }
		inline constexpr static std::size_t Count()		{ return COUNT; }
		inline constexpr static std::size_t Size()		{ return COUNT; }

		inline constexpr	   ValueType& operator[](const std::size_t idx)		{ ENGINECORE_ASSERT(idx < 1); return data[0]; }
		inline constexpr const ValueType& operator[](const std::size_t idx) const	{ ENGINECORE_ASSERT(idx < 1); return data[0]; }

		inline constexpr		ValueArrayType& GetArray()			{ return data; }
		inline constexpr const	ValueArrayType& GetArray() const	{ return data; }

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

		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&&(const VectorConvertibleTo<1, ValueType> auto& rhs);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator||(const VectorConvertibleTo<1, ValueType> auto& rhs);


		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator+() const;
		// operator -I
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator-() const;
		// operator ~I
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator~() const;

		// operator ++I
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator--(int);

		// operator =
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator=(const VectorConvertibleTo<1, ValueType> auto& vec);

		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator=(const VectorConvertibleTo<2, ValueType> auto& vec);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator=(const VectorConvertibleTo<3, ValueType> auto& vec);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator +=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator+=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator -=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator-=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator *=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator*=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator /=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator/=(const VectorConvertibleTo<1, ValueType> auto& vec);

		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//
		// 
		// operator %=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator%=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator%=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator &=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator&=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator&=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator |=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator|=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator|=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator ^=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator^=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator^=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator <<=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator<<=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator<<=(const VectorConvertibleTo<1, ValueType> auto& vec);

		// operator >>=
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator>>=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator>>=(const VectorConvertibleTo<1, ValueType> auto& vec);
	};
	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator -
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator *
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator /
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator &
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator |
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator ^
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator <<
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);

	// operator >>
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<1, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs);
}









