#include "ImageEffect.h"
#include <vlCore/Image.hpp>
#include <AppLogic/VLExtension/EffectPipeline.h>
#include <AppLogic/AppModes/ImageProcessingMode.h>
#include <AppLogic/VLExtension/Util/TextureReader.h>
#include <GUI/ParamsWidget.h>
#include <vlGraphics/Texture.hpp>
#include <AppLogic/VLExtension/Effect.h>

ImageEffect::ImageEffect( const std::wstring& name )
	: super( name )
{

}

void ImageEffect::Enable()
{
	GetEffect()->SetEnable( true );
}

void ImageEffect::Disable()
{
	GetEffect()->SetEnable( false );
}