#pragma once

#include "EngineCore/EngineLib/RDX/RDXCore.h"

namespace EngineCore::RDX {

	template <typename T>
	class List : IContainer<T>, IEnumerable<T> {

	};

}