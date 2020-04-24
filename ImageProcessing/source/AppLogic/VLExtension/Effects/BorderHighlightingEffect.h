#pragma once
#include <AppLogic/VLExtension/Effect.h>
#include <AppLogic/VLExtension/EffectPipeline.h>

namespace VLExtension
{
class BorderHighlightingEffect: public Effect
{
    VL_INSTRUMENT_CLASS( BorderHighlightingEffect, Effect )
public:
    BorderHighlightingEffect();

    virtual void	preRenderUpdate( Shader* shader, int width, int height, float deltaTime ) {}

private:
    vl::ref<EffectPipeline> sobelDistancePipe_;
};
}