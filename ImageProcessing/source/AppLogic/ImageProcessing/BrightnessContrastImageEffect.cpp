#include "BrightnessContrastImageEffect.h"
#include <Effects/BrightnessContrastEffect.h>
#include <AppLogic/Effects/WidgetData/ParamsWidget.h>
#include <AppLogic/VLExtension/EffectPipeline.h>

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
    pipeEffect_ = new VLExtension::BrightnessContrastEffect;
    UpdateData();
}

void BrightnessContrastImageEffect::UpdateData()
{
    pipeEffect_->SetBrightness( brightness_ );
    pipeEffect_->SetContrast( contrast_ );
}

void BrightnessContrastImageEffect::OnCreatedEffectWidget( ParamsWidget* effectWidget )
{
    effectWidget->AddParam( L"Brightness", brightness_, -100.f, 100.f );
    effectWidget->AddParam( L"Contrast", contrast_, -100.f, 100.f );
}

VLExtension::Effect* BrightnessContrastImageEffect::GetEffect()
{
    return pipeEffect_.get();
}