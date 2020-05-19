#include "BorderHighlightingImageEffect.h"
#include <GUI/ParamsWidget.h>
#include <VLExtension/Effect.h>
#include <VLExtension/Effects/BorderHighlightingEffect.h>

BorderHighlightingImageEffect::BorderHighlightingImageEffect()
    : super( L"Border highlighting effect" )
{
    pipeEffect_ = new VLExtension::BorderHighlightingEffect;
    UpdateData();
}

void BorderHighlightingImageEffect::UpdateData()
{
    pipeEffect_->GetUniformSet()->gocUniform( "sigma" )->setUniform( sigma_ );
    pipeEffect_->GetUniformSet()->gocUniform( "is_colorful" )->setUniform( isColorful_ );
}

VLExtension::Effect* BorderHighlightingImageEffect::GetEffect()
{
    return pipeEffect_.get();
}

void BorderHighlightingImageEffect::OnCreatedParamsWidget( ParamsWidget* paramsWidget )
{
    paramsWidget->AddParam( L"Sigma(param - border distance or diffuse)", sigma_, 0.1f, 5.f );
    paramsWidget->AddParam( L"Is colorful", isColorful_ );
}
