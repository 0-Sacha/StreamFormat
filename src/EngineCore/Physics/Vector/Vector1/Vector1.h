#pragma once

#include "Vector1Type.h"

namespace EngineCore {

	template<typename T>
	using Vector1 = Vector<1, T>;

	using Vector1f = Vector1<float>;
	using Vector1d = Vector1<double>;
	using Vector1i = Vector1<int32_t>;
	using Vector1u = Vector1<uint32_t>;

}

// Format
template<typename T>
struct CPPTools::Fmt::FormatType<EngineCore::Vector<1, T>>
{
	static void Write(const EngineCore::Vector<1, T>& vec, CPPTools::Fmt::Formater& formater) {
		formater.LittleFormat("#{{:{1}}}", vec.x, formater.GetFormatData());
	}
};
