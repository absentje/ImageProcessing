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
    pipeEffect_->GetUniformSet()->gocUniform( "highlightDistance" )->setUniform( highlightDistance_ );
}

VLExtension::Effect* BorderHighlightingImageEffect::GetEffect()
{
    return pipeEffect_.get();
}

void BorderHighlightingImageEffect::OnCreatedParamsWidget( ParamsWidget* paramsWidget )
{
    paramsWidget->AddParam( L"Highlight distance", highlightDistance_, 0.f, 1.f );
}
