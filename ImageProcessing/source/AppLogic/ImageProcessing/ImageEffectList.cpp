#include "ImageEffectList.h"
#include "ImageEffect.h"
#include <VLExtension/EffectPipeline.h>
#include <AppLogic/ImageProcessing/ImageEffects/BrightnessContrastImageEffect.h>
#include <AppLogic/ImageProcessing/ImageEffects/BorderHighlightingImageEffect.h>
#include <AppLogic/ImageProcessing/ImageEffects/GaussianBlurImageEffect.h>
#include <VLExtension/Effect.h>

ImageEffectList::ImageEffectList()
	: super( L"ImageEffects" )
{
	pipeline_ = new VLExtension::EffectPipeline;

	std::vector<vl::ref<ImageEffect>> imageEffects =
	{
		new BrightnessContrastImageEffect,
		new BorderHighlightingImageEffect,
		new GaussianBlurImageEffect
	};

	for ( auto imageEffect : imageEffects )
	{
		Add( imageEffect.get() );
		pipeline_->AddEffect( imageEffect->GetEffect() );
		imageEffect->GetEffect()->SetEnable( false );
	}
}

VLExtension::EffectPipeline* ImageEffectList::GetImageEffectsPipeline()
{
	return pipeline_.get();
}