#include "EngineCore/Core/Core.h"
#include "FormatterHandler.h"

namespace EngineCore::FMT::Detail {
	FormatterHandler& Detail::FormatterHandler::GetInstance() {
        static FormatterHandler instance;
        return instance;
    }
}