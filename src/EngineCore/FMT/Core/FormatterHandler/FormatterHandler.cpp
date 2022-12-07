#include "EngineCore/Core/Core.h"
#include "EngineCorepch.h"
#include "FormatterHandler.h"

namespace EngineCore::FMT {
	FormatterHandler& FormatterHandler::GetInstance() {
        static FormatterHandler instance;
        return instance;
    }
}