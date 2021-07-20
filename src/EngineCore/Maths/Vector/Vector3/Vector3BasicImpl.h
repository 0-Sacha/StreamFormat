#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- Vector3 -------------//
	template <typename Type>
	struct Vector<3, Type, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType = Type;
		
		union {
			std::array<ValueType, 3> data;
			struct { ValueType x, y, z; };
		};

		inline constexpr static std::size_t Length()	{ return 3; }
		inline constexpr static std::size_t Count()		{ return 3; }
		inline constexpr static std::size_t Size()		{ return 3; }


		inline constexpr ValueType& operator[](const std::size_t idx)				{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const ValueType& operator[](const std::size_t idx) const	{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }

		inline constexpr		std::array<ValueType, 3>& GetArray()		{ return data; }
		inline constexpr const	std::array<ValueType, 3>& GetArray() const	{ return data; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		constexpr Vector(const std::convertible_to<ValueType> auto scalar);																							// S
		constexpr Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z);	// S - S - S
		constexpr Vector(const VectorConvertible<3, ValueType> auto& vec);																							// V3

		//--------------------------------------------------------------------//
		//------------- Conversion From Other Vector Constructor -------------//
		//--------------------------------------------------------------------//

		// From Vector<1, T, C>
		constexpr Vector(const VectorConvertible<1, ValueType> auto& scalar);	// V1 as S

		constexpr Vector(const VectorConvertible<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z);		// V1 - S  - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const std::convertible_to<ValueType> auto z);		// S  - V1 - S 
		constexpr Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const std::convertible_to<ValueType> auto z);		// V1 - V1 - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<1, ValueType> auto z);		// S  - S  - V1 -- 
		constexpr Vector(const VectorConvertible<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<1, ValueType> auto z);		// V1 - S  - V1
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<1, ValueType> auto z);		// S  - V1 - V1
		constexpr Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<1, ValueType> auto z);	// V1 - V1 - V1


		// From Vector<2, T, C>
		constexpr Vector(const VectorConvertible<2, ValueType> auto& xy, const std::convertible_to<ValueType> auto z);		// V2 - S 
		constexpr Vector(const VectorConvertible<2, ValueType> auto& xy, const VectorConvertible<1, ValueType> auto z);		// V2 - V1 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<2, ValueType> auto yz);		// S  - V2
		constexpr Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<2, ValueType> auto yz);		// V1 - V2

		// From Vector<4, T, C>
		constexpr Vector(const VectorConvertible<4, ValueType> auto& vec);	// V4

		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//


		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const VectorConvertible<3, ValueType> auto& rhs);
		constexpr bool operator!=(const VectorConvertible<3, ValueType> auto& rhs);

		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator&&(const VectorConvertible<3, ValueType> auto& rhs);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator||(const VectorConvertible<3, ValueType> auto& rhs);

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>  operator+();
		// operator -I
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>  operator-();
		// operator ~I
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator~();

		// operator ++I
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>  operator--(int);

		// operator =
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator=(const VectorConvertible<3, ValueType> auto& vec);

		// operator +=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const VectorConvertible<3, ValueType> auto& vec);

		// operator -=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const VectorConvertible<3, ValueType> auto& vec);

		// operator *=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const VectorConvertible<3, ValueType> auto& vec);

		// operator /=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const VectorConvertible<3, ValueType> auto& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator %=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const VectorConvertible<3, ValueType> auto& vec);

		// operator &=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const VectorConvertible<3, ValueType> auto& vec);

		// operator |=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const VectorConvertible<3, ValueType> auto& vec);

		// operator ^=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const VectorConvertible<3, ValueType> auto& vec);

		// operator <<=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const VectorConvertible<3, ValueType> auto& vec);

		// operator >>=
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const VectorConvertible<3, ValueType> auto& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator -
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator *
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator /
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator &
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator |
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator ^
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator <<
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

	// operator >>
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<3, ValueType> auto& rhs);

}





