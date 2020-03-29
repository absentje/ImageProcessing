#include "ColorUtils.h"
#include <vlCore/Matrix3.hpp>

namespace ColorUtils
{
void toYUV( vl::vec3& RGB )
{
    static const vl::mat3 coeffs =
        vl::mat3(
            0.2126f, 0.7152f, 0.0722f,
            -0.0999f, -0.3360f, 0.4360f,
            0.6150f, -0.5586f, -0.0563f
            );

    RGB = coeffs * RGB;
}

void toRGB( vl::vec3& YUV )
{
    static const vl::mat3 coeffs =
        vl::mat3(
            1.f, 0.f, 1.2803f,
            1.f, -0.2148f, -0.3805f,
            1.f, 2.1279f, 0.f
            );
    YUV = coeffs * YUV;
}
}