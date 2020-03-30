#include "BrightnessContrastEffect.h"
#include <vlGraphics/Uniform.hpp>
#include <Shader.h>

const float DEFAULT_BRIGHTNESS = 0.0f;
const float DEFAULT_CONTRAST = 0.0f;

namespace VLExtension
{
BrightnessContrastEffect::BrightnessContrastEffect()
    : Brightness( DEFAULT_BRIGHTNESS ), Contrast( DEFAULT_CONTRAST )
{
    pUniBrightness = new vl::Uniform( "brightness" );
    pUniBrightness->setUniform( Brightness );

    pUniContrast = new vl::Uniform( "contrast" );
    pUniContrast->setUniform( Contrast );
}

void	BrightnessContrastEffect::onPipelineAdd( Shader* shader, int width, int height )
{
    shader->SetFShader( L"resources/glsl/brightness_contrast_effect.fs" );
    shader->setUniform( pUniBrightness.get() );
    shader->setUniform( pUniContrast.get() );
}

float	BrightnessContrastEffect::GetBrightness() const
{
    return Brightness;
}
float	BrightnessContrastEffect::GetContrast() const
{
    return Contrast;
}
void	BrightnessContrastEffect::SetBrightness( float v )
{
    Brightness = v;
    pUniBrightness->setUniform( v );
}
void	BrightnessContrastEffect::SetContrast( float v )
{
    Contrast = v;
    pUniContrast->setUniform( v );
}
}