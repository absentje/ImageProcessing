#pragma once
#include <AppLogic/VLExtension/Effect.h>

namespace VLExtension
{
class BrightnessContrastEffect: public Effect
{
    VL_INSTRUMENT_CLASS( BrightnessContrastEffect, Effect )
public:
    BrightnessContrastEffect();

    void		SetBrightness( float v );
    void		SetContrast( float v );
    float		GetBrightness() const;
    float		GetContrast() const;

protected:
    float		brightness_ = 0.f;
    float		contrast_ = 0.f;
};
}