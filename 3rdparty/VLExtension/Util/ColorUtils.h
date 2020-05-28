#pragma once
#include <vlCore/Vector3.hpp>

namespace ColorUtils
{
void    toYUV( vl::vec3& RGB );
void    toRGB( vl::vec3& YUV );
}