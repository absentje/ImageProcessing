#include "ImageEffect.h"
#include <vlCore/Image.hpp>
#include <VLExtension/EffectPipeline.h>
#include <AppLogic/AppModes/ImageProcessingMode.h>
#include <VLExtension/Util/TextureReader.h>
#include <GUI/ParamsWidget.h>
#include <vlGraphics/Texture.hpp>
#include <VLExtension/Effect.h>

ImageEffect::ImageEffect( const std::wstring& name )
	: super( name )
{

}

void ImageEffect::Enable( bool value )
{
	GetEffect()->SetEnable( value );
}