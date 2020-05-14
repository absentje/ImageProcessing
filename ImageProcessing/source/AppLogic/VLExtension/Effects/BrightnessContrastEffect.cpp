#include "BrightnessContrastEffect.h"
#include <vlGraphics/Uniform.hpp>
#include <AppLogic/VLExtension/Shader.h>

const float DEFAULT_BRIGHTNESS = 0.0f;
const float DEFAULT_CONTRAST = 0.0f;

namespace VLExtension
{
BrightnessContrastEffect::BrightnessContrastEffect()
    : super( L"resources/glsl/brightness_contrast_effect.fs" )
{
    SetBrightness( DEFAULT_BRIGHTNESS );
    SetContrast( DEFAULT_CONTRAST );
}

float	BrightnessContrastEffect::GetBrightness() const
{
    return brightness_;
}
float	BrightnessContrastEffect::GetContrast() const
{
    return contrast_;
}
void	BrightnessContrastEffect::SetBrightness( float v )
{
    brightness_ = v;
    uniform_set_->gocUniform( "brightness" )->setUniform( brightness_ );
}
void	BrightnessContrastEffect::SetContrast( float v )
{
    contrast_ = v;
    uniform_set_->gocUniform( "contrast" )->setUniform( contrast_ );
}
}