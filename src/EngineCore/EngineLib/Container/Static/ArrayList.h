#pragma once

#include "EngineCore/Core/Core.h"
#include "Allocator.h"

namespace EngineCore::EngineLib::Container::Static {

	template<typename T, typename Allocator = Allocator<T>>
	class ArrayList {

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
		constexpr static SizeType BEGIN_CAPACITY = 8;

	public:
		ArrayList()
			: m_Allocator()
			, m_Size(0)
			, m_Capacity(BEGIN_CAPACITY)
			, m_Data(m_Allocator.Allocate(m_Capacity))
		{
		}

		ArrayList(SizeType beginCapacity)
			: m_Allocator()
			, m_Size(0)
			, m_Capacity(beginCapacity)
			, m_Data(m_Allocator.Allocate(m_Capacity))
		{
		}

	public:
		inline SizeType Size() const {
			return m_Size;
		}

		inline bool IsEmpty() const {
			return m_Size == 0;
		}

		inline SizeType Capacity() const {
			return m_Capacity;
		}

		inline PointerType GetData() {
			return m_Data;
		}

		inline ConstPointerType GetData() const {
			return m_Data;
		}

	public:
		ReferenceType PushBack(ConstReferenceType value) {

		}

		ReferenceType PushBack(MoveReferenceType value) {

		}

		template<typename ...Args>
		ReferenceType EmplaceBack(Args&& ...args) {
			
		}

	private:
		void ResizeImpl() {

		}

	private:
		Allocator		m_Allocator;

		SizeType		m_Size;
		SizeType		m_Capacity;
		PointerType		m_Data;
	};
}

