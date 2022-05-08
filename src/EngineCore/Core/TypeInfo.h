#pragma once

#include <utility>
#include <type_traits>

namespace EngineCore::EngineLib::Core {

	template <typename T>
	class TypeInfo {
	public:
		using SizeType				= std::size_t;
		using ValueType				= std::remove_cvref_t<T>;
		using PointerType			= ValueType*;
		using ConstPointerType		= const ValueType*;
		using ReferenceType			= ValueType&;
		using ConstReferenceType	= const ValueType&;
		using MoveReferenceType		= ValueType&&;
	};

}