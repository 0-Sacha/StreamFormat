
#include "FormatterHandler.h"

namespace EngineCore::Fmt {
	FormatterHandler& FormatterHandler::GetInstance() {
        static FormatterHandler instance;
        return instance;
    }
}