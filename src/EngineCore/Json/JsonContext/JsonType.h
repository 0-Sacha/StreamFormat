#pragma once

namespace EngineCore::JSON
{
    class JsonContext;

	template<typename T>
	struct JsonType {
		static inline void Load(T& t, JsonContext& context)
        {
            // TODO : error recovery for unknown types
		}
	};
}
