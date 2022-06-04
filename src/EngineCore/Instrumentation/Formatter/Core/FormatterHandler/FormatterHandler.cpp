#include "EngineCorepch.h"
#include "EngineCore/Core.h"
#include "FormatterHandler.h"

namespace EngineCore::FMT {
	FormatterHandler& FormatterHandler::GetInstance() {
        static FormatterHandler instance;
        return instance;
    }
}