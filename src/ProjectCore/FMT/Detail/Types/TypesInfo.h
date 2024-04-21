#pragma once

#include "ProjectCore/Core/Core.h"

namespace ProjectCore::FMT::Detail::TypesInfo
{
    template<typename T>
    struct NumberDetail {
        bool IsFloatingNumber    = std::is_floating_point_v<T>;
        bool IsSigned            = std::is_signed_v<T>;
    };
}
