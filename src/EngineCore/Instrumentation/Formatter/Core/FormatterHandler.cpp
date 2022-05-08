#include "EngineCorepch.h"
#include "EngineCore/Core.h"
#include "FormatterHandler.h"

namespace EngineCore::Instrumentation::Fmt {
	FormatterHandler& FormatterHandler::GetInstance() {
        static FormatterHandler instance;
        return instance;
    }
}