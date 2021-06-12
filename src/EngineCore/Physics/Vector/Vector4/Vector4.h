#pragma once

#include "Vector4Type.h"

namespace EngineCore {

	template<typename T>
	using Vector4 = Vector<4, T>;

	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int32_t>;
	using Vector4u = Vector4<uint32_t>;

}

// Format
template<typename T>
struct CPPTools::Fmt::FormatType<EngineCore::Vector<4, T>>
{
	static void Write(const EngineCore::Vector<4, T>& vec, CPPTools::Fmt::Formater& formater) {
		formater.LittleFormat("#{{:{4}}, {:{4}}, {:{4}}, {:{4}}}", vec.x, vec.y, vec.z, vec.w, formater.GetFormatData());
	}
};
