#pragma once
#include "EngineCore/LIB/RDX/RDXCore.h"

namespace EngineCore::RDX::BasicInterface {

	template <typename T>
	class IContainer {

	public:
		virtual BasicInterface<T>::SizeType Count() = 0;

	public:
		bool IsEmpty() { return Count() == 0; };

	};

}