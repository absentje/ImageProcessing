#include "GaussianBlurImageEffect.h"
#include <GUI/ParamsWidget.h>
#include <VLExtension/Effect.h>
#include <VLExtension/Effects/GaussianBlurEffect.h>

GaussianBlurImageEffect::GaussianBlurImageEffect()
    : super( L"Gaussian blur effect" )
{
    pipeEffect_ = new VLExtension::GaussianBlurEffect;
    UpdateData();
}

void GaussianBlurImageEffect::UpdateData()
{
    pipeEffect_->SetSigma( sigma_ );
}

VLExtension::Effect* GaussianBlurImageEffect::GetEffect()
{
    return pipeEffect_.get();
}

void GaussianBlurImageEffect::OnCreatedParamsWidget( ParamsWidget* paramsWidget )
{
    paramsWidget->AddParam( L"Sigma(highlight distance)", sigma_, 0.1f, 5.f );
}
