#pragma once

#include "Vector4BasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector()
		: x{}, y{}, z{}, w{} {}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto scalar)
		: x{ static_cast<ValueType>(scalar) }, y{ static_cast<ValueType>(scalar) }, z{ static_cast<ValueType>(scalar) }, w{ static_cast<ValueType>(scalar) } {}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w) } {}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<4, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) }, y{ static_cast<ValueType>(vec.y) }, z{ static_cast<ValueType>(vec.z) }, w{ static_cast<ValueType>(vec.w) } {}


	//--------------------------------------------------------------------//
	//------------- Conversion From Other Vector Constructor -------------//
	//--------------------------------------------------------------------//

	// From Vector<1, T, C>
	// V1 as S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& scalar)
		: x{ static_cast<ValueType>(scalar) }, y{ static_cast<ValueType>(scalar) }, z{ static_cast<ValueType>(scalar) }, w{ static_cast<ValueType>(scalar) } {}


	// V1 - S  - S  - S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w) } {}

	// S  - V1 - S  - S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w) } {}
	
	// V1 - V1 - S  - S 
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w) } {}
	
	// S  - S  - V1 - S  -- 
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w) } {}
	
	// V1 - S  - V1 - S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w) } {}
	
	// S  - V1 - V1 - S 
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w) } {}
	
	// V1 - V1 - V1 - S 
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w) } {}
	
	// S  - S  - S  - V1 -- --
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// V1 - S  - S  - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// S  - V1 - S  - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// V1 - V1 - S  - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const std::convertible_to<ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// S  - S  - V1 - V1 --
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// V1 - S  - V1 - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w) } {}
	
	// S  - V1 - V1 - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// V1 - V1 - V1 - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<1, ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w) } {}

	// From Vector<2, T, C>
	// V2 - V2
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<2, ValueType> auto& xy, const VectorConvertible<2, ValueType> auto zw)
		: x{ static_cast<ValueType>(xy.x) }, y{ static_cast<ValueType>(xy.y) }, z{ static_cast<ValueType>(zw.z) }, w{ static_cast<ValueType>(zw.w) } {}

	
	// V2 - S  - S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<2, ValueType> auto& xy, const std::convertible_to<ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(xy.x) }, y{ static_cast<ValueType>(xy.y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w) } {}
	
	// V2 - V1 - S 
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<2, ValueType> auto& xy, const VectorConvertible<1, ValueType> auto z, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(xy.x) }, y{ static_cast<ValueType>(xy.y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w) } {}
	
	// S  - V2 - S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<2, ValueType> auto yz, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(yz.y) }, z{ static_cast<ValueType>(yz.z) }, w{ static_cast<ValueType>(w) } {}
	
	// V1 - V2 - S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<2, ValueType> auto yz, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(yz.y) }, z{ static_cast<ValueType>(yz.z) }, w{ static_cast<ValueType>(w) } {}
		
	// V2 - S  - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<2, ValueType> auto& xy, const std::convertible_to<ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(xy.x) }, y{ static_cast<ValueType>(xy.y) }, z{ static_cast<ValueType>(z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// V2 - V1 - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<2, ValueType> auto& xy, const VectorConvertible<1, ValueType> auto z, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(xy.x) }, y{ static_cast<ValueType>(xy.y) }, z{ static_cast<ValueType>(z.z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// S  - V2 - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<2, ValueType> auto yz, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(yz.y) }, z{ static_cast<ValueType>(yz.z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// V1 - V2 - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<2, ValueType> auto yz, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(yz.y) }, z{ static_cast<ValueType>(yz.z) }, w{ static_cast<ValueType>(w.w) } {}


	// V1 - V1 - V2
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<2, ValueType> auto zw)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(zw.z) }, w{ static_cast<ValueType>(zw.w) } {}
	
	// S  - S  - V2
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<2, ValueType> auto zw)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(zw.z) }, w{ static_cast<ValueType>(zw.w) } {}
	
	// V1 - S  - V2
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertible<2, ValueType> auto zw)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(zw.z) }, w{ static_cast<ValueType>(zw.w) } {}
	
	// S  - V1 - V2
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<1, ValueType> auto y, const VectorConvertible<2, ValueType> auto zw)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(zw.z) }, w{ static_cast<ValueType>(zw.w) } {}


	// From Vector<3, T, C>
	// V3 - S
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<3, ValueType> auto& xyz, const std::convertible_to<ValueType> auto w)
		: x{ static_cast<ValueType>(xyz.x) }, y{ static_cast<ValueType>(xyz.y) }, z{ static_cast<ValueType>(xyz.z) }, w{ static_cast<ValueType>(w) } {}
	
	// V3 - V1
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<3, ValueType> auto& xyz, const VectorConvertible<1, ValueType> auto w)
		: x{ static_cast<ValueType>(xyz.x) }, y{ static_cast<ValueType>(xyz.y) }, z{ static_cast<ValueType>(xyz.z) }, w{ static_cast<ValueType>(w.w) } {}
	
	// S  - V3
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertible<3, ValueType> auto yzw)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(yzw.y) }, z{ static_cast<ValueType>(yzw.z) }, w{ static_cast<ValueType>(yzw.w) } {}
	
	// V1 - V3
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertible<1, ValueType> auto& x, const VectorConvertible<3, ValueType> auto yzw)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(yzw.y) }, z{ static_cast<ValueType>(yzw.z) }, w{ static_cast<ValueType>(yzw.w) } {}


	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename ValueType>
	inline constexpr bool Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator==(const VectorConvertible<4, ValueType> auto& rhs) {
		return this->x == rhs.x && this->y == rhs.y && this->z && rhs.z && this->w && rhs.w;
	}

	template <typename ValueType>
	inline constexpr bool Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator!=(const VectorConvertible<4, ValueType> auto& rhs) {
		return !(*this == rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator&&(const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(this->x && rhs.x, this->y && rhs.y, this->z && rhs.z, this->w && rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator||(const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(this->x || rhs.x, this->y || rhs.y, this->z || rhs.z, this->w || rhs.w);
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator-() {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(-this->x, -this->y, -this->z, -this->w);
	}

	// operator ~I
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator~() {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(~this->x, ~this->y, ~this->z, ~this->w);
	}


	// operator ++I
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator++() {
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	// operator --I
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator--() {
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	// operator I++
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<4, ValueType, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<4, ValueType, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}

	// operator =
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		this->x = static_cast<ValueType>(scalar);
		this->y = static_cast<ValueType>(scalar);
		this->z = static_cast<ValueType>(scalar);
		this->w = static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		this->y = static_cast<ValueType>(vec.y);
		this->z = static_cast<ValueType>(vec.z);
		this->w = static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator +=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		this->x += static_cast<ValueType>(scalar);
		this->y += static_cast<ValueType>(scalar);
		this->z += static_cast<ValueType>(scalar);
		this->w += static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator+=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x += static_cast<ValueType>(vec.x);
		this->y += static_cast<ValueType>(vec.y);
		this->z += static_cast<ValueType>(vec.z);
		this->w += static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator -=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		this->x -= static_cast<ValueType>(scalar);
		this->y -= static_cast<ValueType>(scalar);
		this->z -= static_cast<ValueType>(scalar);
		this->w -= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator-=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x -= static_cast<ValueType>(vec.x);
		this->y -= static_cast<ValueType>(vec.y);
		this->z -= static_cast<ValueType>(vec.z);
		this->w -= static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator *=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		this->x *= static_cast<ValueType>(scalar);
		this->y *= static_cast<ValueType>(scalar);
		this->z *= static_cast<ValueType>(scalar);
		this->w *= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator*=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x *= static_cast<ValueType>(vec.x);
		this->y *= static_cast<ValueType>(vec.y);
		this->z *= static_cast<ValueType>(vec.z);
		this->w *= static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator /=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		this->x /= static_cast<ValueType>(scalar);
		this->y /= static_cast<ValueType>(scalar);
		this->z /= static_cast<ValueType>(scalar);
		this->w /= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator/=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x /= static_cast<ValueType>(vec.x);
		this->y /= static_cast<ValueType>(vec.y);
		this->z /= static_cast<ValueType>(vec.z);
		this->w /= static_cast<ValueType>(vec.w);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator%=(const std::convertible_to<ValueType> auto scalar) {
		this->x %= static_cast<ValueType>(scalar);
		this->y %= static_cast<ValueType>(scalar);
		this->z %= static_cast<ValueType>(scalar);
		this->w %= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator%=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x %= static_cast<ValueType>(vec.x);
		this->y %= static_cast<ValueType>(vec.y);
		this->z %= static_cast<ValueType>(vec.z);
		this->w %= static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator &=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator&=(const std::convertible_to<ValueType> auto scalar) {
		this->x &= static_cast<ValueType>(scalar);
		this->y &= static_cast<ValueType>(scalar);
		this->z &= static_cast<ValueType>(scalar);
		this->w &= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator&=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x &= static_cast<ValueType>(vec.x);
		this->y &= static_cast<ValueType>(vec.y);
		this->z &= static_cast<ValueType>(vec.z);
		this->w &= static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator |=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator|=(const std::convertible_to<ValueType> auto scalar) {
		this->x |= static_cast<ValueType>(scalar);
		this->y |= static_cast<ValueType>(scalar);
		this->z |= static_cast<ValueType>(scalar);
		this->w |= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator|=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x |= static_cast<ValueType>(vec.x);
		this->y |= static_cast<ValueType>(vec.y);
		this->z |= static_cast<ValueType>(vec.z);
		this->w |= static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator ^=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator^=(const std::convertible_to<ValueType> auto scalar) {
		this->x ^= static_cast<ValueType>(scalar);
		this->y ^= static_cast<ValueType>(scalar);
		this->z ^= static_cast<ValueType>(scalar);
		this->w ^= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator^=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x ^= static_cast<ValueType>(vec.x);
		this->y ^= static_cast<ValueType>(vec.y);
		this->z ^= static_cast<ValueType>(vec.z);
		this->w ^= static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator <<=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator<<=(const std::convertible_to<ValueType> auto scalar) {
		this->x <<= static_cast<ValueType>(scalar);
		this->y <<= static_cast<ValueType>(scalar);
		this->z <<= static_cast<ValueType>(scalar);
		this->w <<= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator<<=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x <<= static_cast<ValueType>(vec.x);
		this->y <<= static_cast<ValueType>(vec.y);
		this->z <<= static_cast<ValueType>(vec.z);
		this->w <<= static_cast<ValueType>(vec.w);
		return *this;
	}

	// operator >>=
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator>>=(const std::convertible_to<ValueType> auto scalar) {
		this->x >>= static_cast<ValueType>(scalar);
		this->y >>= static_cast<ValueType>(scalar);
		this->z >>= static_cast<ValueType>(scalar);
		this->w >>= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic>& Vector<4, ValueType, EngineCompute::EngineComputeBasic>::operator>>=(const VectorConvertible<4, ValueType> auto& vec) {
		this->x >>= static_cast<ValueType>(vec.x);
		this->y >>= static_cast<ValueType>(vec.y);
		this->z >>= static_cast<ValueType>(vec.z);
		this->w >>= static_cast<ValueType>(vec.w);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	// operator -
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	// operator *
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
	}

	// operator /
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x % rhs, lhs.y % rhs, lhs.z % rhs, lhs.w % rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs % rhs.x, lhs % rhs.y, lhs % rhs.z, lhs % rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z, lhs.w % rhs.w);
	}

	// operator &
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs, lhs.w & rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z, lhs & rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z, lhs.w & rhs.w);
	}

	// operator |
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs, lhs.w | rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z, lhs | rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z, lhs.w | rhs.w);
	}

	// operator ^
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs, lhs.w ^ rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z, lhs ^ rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z, lhs.w ^ rhs.w);
	}

	// operator <<
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs, lhs.w << rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs << rhs.x, rhs << rhs.y, rhs << rhs.z, rhs << rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z, lhs.w << rhs.w);
	}

	// operator >>
	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs, lhs.w >> rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z, lhs >> rhs.w);
	}

	template <typename ValueType>
	inline constexpr Vector<4, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<4, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertible<4, ValueType> auto& rhs) {
		return Vector<4, ValueType, EngineCompute::EngineComputeBasic>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z, lhs.w >> rhs.w);
	}
}