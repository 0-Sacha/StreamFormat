#pragma once

#include "EngineCore/Core/Core.h"

namespace EngineCore::EngineLib::Container::Static {
	
	template<typename T>
	class Allocator {

	public:
		using TypeInfo 				= Core::TypeInfo<T>;
		using SizeType 				= typename TypeInfo::SizeType;
		using ValueType				= typename TypeInfo::ValueType;
		using PointerType			= typename TypeInfo::PointerType;
		using ConstPointerType		= typename TypeInfo::ConstPointerType;
		using ReferenceType			= typename TypeInfo::ReferenceType;
		using ConstReferenceType	= typename TypeInfo::ConstReferenceType;
		using MoveReferenceType		= typename TypeInfo::MoveReferenceType;

	public:
		inline Allocator() {}

	public:
		// Allocate memory but doesn't call constructor
		inline PointerType Allocate(SizeType count) {
			return static_cast<PointerType>(::operator new (GetSizeToAllocate(count)));
		}

		// Deallocate but not Destruct
		inline void Deallocate(PointerType ptr, SizeType count) {
			::operator delete (ptr, GetSizeToAllocate(count));
		}

		// Allocate and Construct
		inline PointerType AllocateConstruct(SizeType count) {
			return static_cast<PointerType>(::new ValueType[GetSizeToAllocate(count)]);
		}

		// Destruct and Deallocate
		inline void DeallocateDestruct(PointerType ptr, SizeType count) {
			::delete[] ptr;
		}

		// Allocate and Construct only one
		template<typename ...Args>
		inline PointerType AllocateConstructOne(Args&& ...args) {
			return ::new ValueType(std::forward<Args>(args)...);
		}

		// Destruct and Deallocate only one
		inline PointerType DeallocateDestructOne(PointerType ptr) {
			::delete ptr;
		}

		// Allocate and Construct only one
		template<typename ...Args>
		inline PointerType Construct(PointerType ptr, Args&& ...args) {
			new(ptr) ValueType(std::forward<Args>(args)...);
			return ptr;
		}

		// Destruct and Deallocate only one
		inline void Destruct(PointerType ptr) {
			ptr->~ValueType();
		}
		
	public:
		constexpr inline static SizeType GetSizeToAllocate(SizeType count) {
			return sizeof(ValueType) * count;
		}
	};

}