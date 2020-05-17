#include "BorderHighlightingImageEffect.h"
#include <GUI/ParamsWidget.h>
#include <AppLogic/VLExtension/Effect.h>
#include <AppLogic/VLExtension/Effects/BorderHighlightingEffect.h>

BorderHighlightingImageEffect::BorderHighlightingImageEffect()
    : super( L"Border highlighting effect" )
{
    pipeEffect_ = new VLExtension::BorderHighlightingEffect;
    UpdateData();
}

void BorderHighlightingImageEffect::UpdateData()
{
    pipeEffect_->GetUniformSet()->gocUniform( "sigma" )->setUniform( highlightDistance_ );
    pipeEffect_->GetUniformSet()->gocUniform( "isColorful" )->setUniform( isColorful_ );
}

VLExtension::Effect* BorderHighlightingImageEffect::GetEffect()
{
    return pipeEffect_.get();
}

void BorderHighlightingImageEffect::OnCreatedParamsWidget( ParamsWidget* paramsWidget )
{
    paramsWidget->AddParam( L"Highlight distance(sigma)", highlightDistance_, 0.1f, 10.f );
    paramsWidget->AddParam( L"Is colorful", isColorful_ );
}
