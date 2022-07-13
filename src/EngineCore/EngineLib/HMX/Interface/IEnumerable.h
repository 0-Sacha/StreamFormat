#pragma once
#include "EngineCore/EngineLib/RDX/RDXCore.h"

namespace EngineCore::RDX::BasicInterface {

	template <typename T>
	class IEnumerable {
		// IEnumerable Iterator get function (wrapper for begin/end/.. to keep PascalCase)
	public:
		virtual BasicInfo<T>::Iterator GetBeginIterator() = 0;
		virtual BasicInfo<T>::Iterator GetEndIterator() = 0;
		
		virtual BasicInfo<T>::ReverseIterator GetBeginReverseIterator() = 0;
		virtual BasicInfo<T>::ReverseIterator GetEndReverseIterator() = 0;
		
		virtual BasicInfo<T>::ConstIterator GetBeginConstIterator() {
			return GetBeginIterator();
		}
		virtual BasicInfo<T>::ConstIterator GetEndConstIterator() {
			return GetEndIterator();
		}

		virtual BasicInfo<T>::ConstReverseIterator GetBeginConstReverseIterator() {
			return GetBeginReverseIterator();
		}
		virtual BasicInfo<T>::ConstReverseIterator GetEndConstReverseIterator() {
			return GetEndReverseIterator();
		}

	public:
		// AllOf | AnyOf | NoneOf
		template <typename UnaryPredicate>
		constexpr inline bool AllOf(UnaryPredicate predicate) {
			return std::all_of(cbegin(), cend(), predicate);
		}

		template <typename UnaryPredicate>
		constexpr inline bool AnyOf(UnaryPredicate predicate) {
			return std::any_of(cbegin(), cend(), predicate);
		}

		template <typename UnaryPredicate>
		constexpr inline bool NoneOf(UnaryPredicate predicate) {
			return std::none_of(cbegin(), cend(), predicate);
		}

		// ForEach
		template <typename UnaryPredicate>
		constexpr inline UnaryPredicate ForEach(UnaryPredicate predicate) {
			return std::for_each(cbegin(), cend(), predicate);
		}

		template <typename SizeType, typename UnaryPredicate>
		constexpr inline BasicInfo<T>::ConstIterator ForEach(SizeType n, UnaryPredicate predicate) {
			return std::for_each_n(cbegin(), n, predicate);
		}

		// Count
		template <typename TestType>
		constexpr inline BasicInfo<T>::DifferenceType Count(const T& value) {
			return std::count(cbegin(), cend(), value);
		}

		template <typename UnaryPredicate>
		constexpr inline BasicInfo<T>::DifferenceType CountIf(UnaryPredicate predicate) {
			return std::count_if(cbegin(), cend(), predicate);
		}


	
	
	public:
		inline BasicInfo<T>::Iterator begin() {
			return GetBeginIterator();
		}
		inline BasicInfo<T>::Iterator end() {
			return GetEndIterator();
		}

		inline BasicInfo<T>::ConstIterator cbegin() {
			return GetBeginConstIterator();
		}
		inline BasicInfo<T>::ConstIterator cend() {
			return GetEndConstIterator();
		}

		inline BasicInfo<T>::Iterator rbegin() {
			return GetBeginReverseIterator();
		}
		inline BasicInfo<T>::Iterator rend() {
			return GetEndReverseIterator();
		}

		inline BasicInfo<T>::ConstReverseIterator crbegin() {
			return GetBeginConstReverseIterator();
		}
		inline BasicInfo<T>::ConstReverseIterator crend() {
			return GetEndConstReverseIterator();
		}
	};

}