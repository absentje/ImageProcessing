#include "GaussianBlurEffect.h"
#include <VLExtension/Shader.h>

namespace VLExtension
{

GaussianBlurEffect::GaussianBlurEffect()
    : super( L"resources/glsl/gaussian_blur_effect.fs" )
{
    SetSigma( sigma_ );
}

void GaussianBlurEffect::SetSigma( float sigma )
{
    sigma_ = sigma;
    uniform_set_->gocUniform( "sigma" )->setUniform( sigma_ );
}

}