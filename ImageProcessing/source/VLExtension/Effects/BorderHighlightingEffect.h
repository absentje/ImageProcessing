#pragma once
#include <VLExtension/Effect.h>
#include <VLExtension/EffectPipeline.h>

namespace VLExtension
{
class BorderHighlightingEffect: public Effect
{
    VL_INSTRUMENT_CLASS( BorderHighlightingEffect, Effect )
public:
    BorderHighlightingEffect();

    virtual void preRenderUpdate( Shader* shader, int width, int height, float deltaTime ) override;

private:
    vl::ref<EffectPipeline> sobelDistancePipe_;
};
}