#pragma once

namespace EngineCore::EngineLib::Detail {

	template <typename T>
	class STDWrapperInfo {
	public:
		using SizeType = T::size_type;
		using ValueType = T::value_type;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;


		using Iterator = T::iterator;
		using ConstIterator = T::const_iterator;
		using ReverseIterator = T::reverse_iterator;
		using ConstReverseIterator = T::const_reverse_iterator;

		using DifferenceType = T::difference_type;
	};

}