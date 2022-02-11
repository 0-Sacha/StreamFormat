#pragma once

#include "../Core/Base.h"
#include "../Interface/IContainer.h"
#include "../Interface/IEnumerable.h"


namespace EngineCore::STDWrapper {

	template <typename T>
	class List : IContainer<T>, IEnumerable<T> {
	};

}