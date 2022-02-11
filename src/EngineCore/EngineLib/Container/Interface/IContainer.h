#pragma once
#include "../Core/Base.h"

namespace EngineCore::STDWrapper::BasicInterface {
	template <typename T>
	class IContainer {
	public:
		virtual BasicInterface<T>::SizeType Count() = 0;
		virtual bool IsEmpty() = 0;
	};
}