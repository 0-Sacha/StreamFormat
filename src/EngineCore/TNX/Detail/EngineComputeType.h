#pragma once

namespace EngineCore::TNX::TNXType {

	struct TNXBasic {};

	struct TNXSSE4 {};
	struct TNXAVX {};
	struct TNXAVX2 {};
	struct TNXAVX512 {};

	using TNXDefault = TNXBasic;
}
