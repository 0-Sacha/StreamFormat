#pragma once

#include "Vector2Type.h"

namespace EngineCore {

	template<typename T>
	using Vector2 = Vector<2, T>;

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int32_t>;
	using Vector2u = Vector2<uint32_t>;

}

// Format
template<typename T>
struct CPPTools::Fmt::FormatType<EngineCore::Vector<2, T>>
{
	static void Write(const EngineCore::Vector<2, T>& vec, CPPTools::Fmt::Formater& formater) {
		formater.LittleFormat("#{{:{2}}, {:{2}}}", vec.x, vec.y, formater.GetFormatData());
	}
};
