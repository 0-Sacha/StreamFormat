#include "ProjectCore/Core/Core.h"
#include "FormatterHandler.h"

namespace ProjectCore::FMT::Detail {
	FormatterHandler& Detail::FormatterHandler::GetInstance() {
        static FormatterHandler instance;
        return instance;
    }
}
