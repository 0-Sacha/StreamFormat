#include "EngineCorepch.h"
#include "EngineCore/Core.h"
#include "FormatterHandler.h"

namespace EngineCore::Instrumentation::FMT {
	FormatterHandler& FormatterHandler::GetInstance() {
        static FormatterHandler instance;
        return instance;
    }
}