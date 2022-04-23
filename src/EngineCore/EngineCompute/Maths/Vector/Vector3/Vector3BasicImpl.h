#pragma once

#include "../Vector.h"

namespace EngineCore::EngineCompute {

	//------------- Vector3 -------------//
	template <typename Type>
	struct Vector<3, Type, Detail::EngineComputeType::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		static constexpr std::size_t COUNT = 3;
		using ValueType			= Type;
		using ComputeAlgorithm	= Detail::EngineComputeType::EngineComputeBasic;

		using M_Type			= Vector<COUNT, ValueType, ComputeAlgorithm>;
		using ValueArrayType	= std::array<ValueType, COUNT>;
		
		union {
			ValueArrayType data;
			struct { ValueType x, y, z; };
		};

		inline constexpr static std::size_t Length()	{ return COUNT; }
		inline constexpr static std::size_t Count()		{ return COUNT; }
		inline constexpr static std::size_t Size()		{ return COUNT; }


		inline constexpr	   ValueType& operator[](const std::size_t idx)		{ ENGINECORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const ValueType& operator[](const std::size_t idx) const	{ ENGINECORE_ASSERT(idx < Count()); return data[idx]; }

		inline constexpr		ValueArrayType& GetArray()			{ return data; }
		inline constexpr const	ValueArrayType& GetArray() const	{ return data; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		constexpr Vector(const std::convertible_to<ValueType> auto scalar);																							// S
		constexpr Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z);	// S - S - S
		constexpr Vector(const VectorConvertibleTo<3, ValueType> auto& vec);																							// V3

		//--------------------------------------------------------------------//
		//------------- Conversion From Other Vector Constructor -------------//
		//--------------------------------------------------------------------//

		// From Vector<1, T, C>
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& scalar);	// V1 as S

		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z);		// V1 - S  - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z);		// S  - V1 - S 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z);		// V1 - V1 - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z);		// S  - S  - V1 -- 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z);		// V1 - S  - V1
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z);		// S  - V1 - V1
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z);	// V1 - V1 - V1


		// From Vector<2, T, C>
		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const std::convertible_to<ValueType> auto z);		// V2 - S 
		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const VectorConvertibleTo<1, ValueType> auto z);		// V2 - V1 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz);		// S  - V2
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz);		// V1 - V2

		// From Vector<4, T, C>
		constexpr Vector(const VectorConvertibleTo<4, ValueType> auto& vec);	// V4

		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//


		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const VectorConvertibleTo<3, ValueType> auto& rhs);
		constexpr bool operator!=(const VectorConvertibleTo<3, ValueType> auto& rhs);

		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&&(const VectorConvertibleTo<3, ValueType> auto& rhs);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator||(const VectorConvertibleTo<3, ValueType> auto& rhs);

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator+() const;
		// operator -I
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator-() const;
		// operator ~I
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator~() const;

		// operator ++I
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>  operator--(int);

		// operator =
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator +=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator+=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator -=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator-=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator *=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator*=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator /=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator/=(const VectorConvertibleTo<3, ValueType> auto& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator %=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator%=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator%=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator &=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator&=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator&=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator |=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator|=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator|=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator ^=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator^=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator^=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator <<=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator<<=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator<<=(const VectorConvertibleTo<3, ValueType> auto& vec);

		// operator >>=
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator>>=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& operator>>=(const VectorConvertibleTo<3, ValueType> auto& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator -
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator *
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator /
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator &
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator |
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator ^
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator <<
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

	// operator >>
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<3, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs);

}





