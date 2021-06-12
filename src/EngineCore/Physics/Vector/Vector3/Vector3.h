#pragma once

#include "Vector3Type.h"

namespace EngineCore {

	template<typename T>
	using Vector3 = Vector<3, T>;

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int32_t>;
	using Vector3u = Vector3<uint32_t>;

}

// Format
template<typename T>
struct CPPTools::Fmt::FormatType<EngineCore::Vector<3, T>>
{
	static void Write(const EngineCore::Vector<3, T>& vec, CPPTools::Fmt::Formater& formater) {
		formater.LittleFormat("#{{:{3}}, {:{3}}, {:{3}}}", vec.x, vec.y, vec.z formater.GetFormatData());
	}
};
