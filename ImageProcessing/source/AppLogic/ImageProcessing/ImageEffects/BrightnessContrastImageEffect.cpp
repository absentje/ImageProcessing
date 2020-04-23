#include "BrightnessContrastImageEffect.h"
#include <GUI/ParamsWidget.h>
#include <AppLogic/VLExtension/EffectPipeline.h>
#include <AppLogic/VLExtension/Effect.h>

namespace
{
constexpr float cMinBrightnessValue = -100.f;
constexpr float cMaxBrightnessValue = 100.f;
constexpr float cMinContrastValue = -100.f;
constexpr float cMaxContrastValue = 100.f;
}

BrightnessContrastImageEffect::BrightnessContrastImageEffect()
    : super( L"Brightness-Contrast effect" )
{
    pipeEffect_ = new VLExtension::Effect( L"resources/glsl/brightness_contrast_effect.fs" );
    UpdateData();
}

void BrightnessContrastImageEffect::UpdateData()
{
    pipeEffect_->GetUniformSet()->gocUniform( "brightness" )->setUniform( brightness_ );
    pipeEffect_->GetUniformSet()->gocUniform( "contrast" )->setUniform( contrast_ );
}

void BrightnessContrastImageEffect::OnCreatedParamsWidget( ParamsWidget* paramsWidget )
{
    paramsWidget->AddParam( L"Brightness", brightness_, -100.f, 100.f );
    paramsWidget->AddParam( L"Contrast", contrast_, -100.f, 100.f );
}

VLExtension::Effect* BrightnessContrastImageEffect::GetEffect()
{
    return pipeEffect_.get();
}