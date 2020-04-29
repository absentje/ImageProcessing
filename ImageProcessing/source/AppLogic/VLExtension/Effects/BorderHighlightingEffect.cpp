#include "BorderHighlightingEffect.h"
#include <AppLogic/VLExtension/Shader.h>

namespace VLExtension
{

BorderHighlightingEffect::BorderHighlightingEffect()
    : super( L"resources/glsl/border_highlighting_effect.fs" )
{
    sobelDistancePipe_ = new EffectPipeline;
    sobelDistancePipe_->SetIsInputResizing( false );
    sobelDistancePipe_->SetTextureFormat( vl::ETextureFormat::TF_R32F );
    sobelDistancePipe_->AddEffect(
        vl::ref<VLExtension::Effect>( new VLExtension::Effect( L"resources/glsl/sobel_distance.fs" ) ).get() );

    uniform_set_->gocUniform( "sobel_distance_texture" )->setUniform( 1 );
}

void BorderHighlightingEffect::preRenderUpdate( Shader* shader, int width, int height, float deltaTime )
{
    sobelDistancePipe_->Resize( width, height );
    sobelDistancePipe_->SetInputTexture( shader->gocTextureSampler( 0 )->texture() );
    shader->gocTextureSampler( 1 )->setTexture( sobelDistancePipe_->RenderOutTexture() );
}

}