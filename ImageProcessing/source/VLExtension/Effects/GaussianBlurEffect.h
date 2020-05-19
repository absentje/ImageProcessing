#pragma once
#include <VLExtension/Effect.h>

namespace VLExtension
{
class GaussianBlurEffect : public Effect
{
    VL_INSTRUMENT_CLASS( BorderHighlightingEffect, Effect )
public:
    GaussianBlurEffect();

    void SetSigma( float sigma );

private:
    float sigma_ = 1.f;
};
}