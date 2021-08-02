#pragma once

#include "../Vector.h"

namespace EngineCore {

	//------------- Vector4 -------------//
	template <typename Type>
	struct Vector<4, Type, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType = Type;
		
		union {
			std::array<ValueType, 4> data;
			struct { ValueType x, y, z, w; };
		};

		inline constexpr static std::size_t Length()	{ return 4; }
		inline constexpr static std::size_t Count()		{ return 4; }
		inline constexpr static std::size_t Size()		{ return 4; }


		inline constexpr ValueType& operator[](const std::size_t idx)				{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }
		inline constexpr const ValueType& operator[](const std::size_t idx) const	{ ENGINE_CORE_ASSERT(idx < Count()); return data[idx]; }

		inline constexpr		std::array<ValueType, 4>& GetArray()		{ return data; }
		inline constexpr const	std::array<ValueType, 4>& GetArray() const	{ return data; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr Vector();
		constexpr Vector(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w);
		constexpr Vector(const VectorConvertibleTo<4, ValueType> auto& vec);

		//--------------------------------------------------------------------//
		//------------- Conversion From Other Vector Constructor -------------//
		//--------------------------------------------------------------------//


		// From Vector<1, T, C>
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& scalar);	// V1 as S

		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w);		// V1 - S  - S  - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w);		// S  - V1 - S  - S 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w);	// V1 - V1 - S  - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const std::convertible_to<ValueType> auto w);		// S  - S  - V1 - S  -- 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const std::convertible_to<ValueType> auto w);	// V1 - S  - V1 - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const std::convertible_to<ValueType> auto w);	// S  - V1 - V1 - S 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const std::convertible_to<ValueType> auto w);	// V1 - V1 - V1 - S 
		constexpr Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);		// S  - S  - S  - V1 -- -- 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// V1 - S  - S  - V1
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// S  - V1 - S  - V1
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// V1 - V1 - S  - V1
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// S  - S  - V1 - V1 -- 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// V1 - S  - V1 - V1
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// S  - V1 - V1 - V1
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// V1 - V1 - V1 - V1

		// From Vector<2, T, C>
		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const VectorConvertibleTo<2, ValueType> auto zw);	// V2 - V2

		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w);		// V2 - S  - S
		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const VectorConvertibleTo<1, ValueType> auto z, const std::convertible_to<ValueType> auto w);	// V2 - V1 - S 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz, const std::convertible_to<ValueType> auto w);		// S  - V2 - S
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz, const std::convertible_to<ValueType> auto w);	// V1 - V2 - S
		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const std::convertible_to<ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// V2 - S  - V1
		constexpr Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const VectorConvertibleTo<1, ValueType> auto z, const VectorConvertibleTo<1, ValueType> auto w);	// V2 - V1 - V1 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz, const VectorConvertibleTo<1, ValueType> auto w);	// S  - V2 - V1
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz, const VectorConvertibleTo<1, ValueType> auto w);	// V1 - V2 - V1

		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<2, ValueType> auto zw);	// V1 - V1 - V2 -- -- 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<2, ValueType> auto zw);		// S  - S  - V2	-- -- 
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<2, ValueType> auto zw);	// V1 - S  - V2 -- -- 
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<2, ValueType> auto zw);	// S  - V1 - V2	-- -- 


		// From Vector<3, T, C>
		constexpr Vector(const VectorConvertibleTo<3, ValueType> auto& xyz, const std::convertible_to<ValueType> auto w);		// V3 - S
		constexpr Vector(const VectorConvertibleTo<3, ValueType> auto& xyz, const VectorConvertibleTo<1, ValueType> auto w);	// V3 - V1
		constexpr Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<3, ValueType> auto yzw);		// S  - V3
		constexpr Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<3, ValueType> auto yzw);	// V1 - V3


		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//


		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const VectorConvertibleTo<4, ValueType> auto& rhs);
		constexpr bool operator!=(const VectorConvertibleTo<4, ValueType> auto& rhs);

		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator&&(const VectorConvertibleTo<4, ValueType> auto& rhs);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator||(const VectorConvertibleTo<4, ValueType> auto& rhs);

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>  operator+() const;
		// operator -I
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>  operator-() const;
		// operator ~I
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>  operator~() const;

		// operator ++I
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>  operator--(int);

		// operator =
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator +=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator -=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator *=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator /=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const VectorConvertibleTo<4, ValueType> auto& vec);


		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//

		// operator %=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator%=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator &=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator&=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator |=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator|=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator ^=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator^=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator <<=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator<<=(const VectorConvertibleTo<4, ValueType> auto& vec);

		// operator >>=
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const std::convertible_to<ValueType> auto scalar);
		constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& operator>>=(const VectorConvertibleTo<4, ValueType> auto& vec);
	};

	// ------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator -
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator *
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator /
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator &
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator |
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator ^
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator <<
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);

	// operator >>
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType> constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<4, ValueType> auto& rhs);
}














