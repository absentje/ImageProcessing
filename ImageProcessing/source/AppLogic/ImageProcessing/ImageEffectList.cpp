#include "ImageEffectList.h"
#include "ImageEffect.h"
#include <AppLogic/VLExtension/EffectPipeline.h>

ImageEffectList::ImageEffectList()
	: super( L"ImageEffects" )
{
}

void ImageEffectList::AddImageEffect( ImageEffect* effect )
{
	Add( effect );
}