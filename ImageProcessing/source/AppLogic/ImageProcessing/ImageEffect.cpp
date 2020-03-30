#include "ImageEffect.h"
#include <vlCore/Image.hpp>
#include <AppLogic/VLExtension/EffectPipeline.h>
#include <AppLogic/AppModes/ImageProcessingMode.h>
#include <AppLogic/VLExtension/Util/TextureReader.h>
#include <vlGraphics/Texture.hpp>

ImageEffect::ImageEffect( const std::wstring& effectName )
	: IEffect( effectName )
{

}

void ImageEffect::ApplyEffect()
{
	if ( !imProcMode_ || !imProcMode_->pSourceImage )
	{
		return;
	}
	if ( !pipeline_ )
	{
		pipeline_ = new VLExtension::EffectPipeline( imProcMode_->pContext );
		pipeline_->AddEffect( GetEffect() );
	}
	pipeline_->SetInputTexture( new vl::Texture( imProcMode_->pSourceImage.get() ) );
	pipeline_->Resize( imProcMode_->pSourceImage->width(), imProcMode_->pSourceImage->height() );
	vl::Texture* outTexture = pipeline_->RenderOutTexture();
	imProcMode_->pOutputImage = TextureReader::TextureToImage( outTexture );
}

void ImageEffect::SetImageProcessingMode( ImageProcessingMode* imProcMode )
{
	imProcMode_ = imProcMode;
}