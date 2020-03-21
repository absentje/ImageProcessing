#ifndef BRIGHTNESSCONTRASTEFFECT_H
#define BRIGHTNESSCONTRASTEFFECT_H
#include "Effect.h"

namespace vl
{
    class Uniform;
}

class BrightnessContrastEffect : public Effect
{
    VL_INSTRUMENT_CLASS(BrightnessContrastEffect, Effect)
public:
    BrightnessContrastEffect();

    void		SetBrightness(float v);
    void		SetContrast(float v);
    float		GetBrightness() const;
    float		GetContrast() const;

    virtual void	onPipelineAdd(Shader* shader, int width, int height) override;

protected:
    vl::ref<vl::Uniform>	pUniBrightness;
    vl::ref<vl::Uniform>	pUniContrast;
    float		Brightness;
    float		Contrast;
};

#endif // BRIGHTNESSCONTRASTEFFECT_H
