#pragma once
#include <AppLogic/Effects/IEffect.h>

namespace vl
{
class Image;
class OpenGLContext;
}

namespace VLExtension
{
class TextureViewActor;
class EffectPipeline;
class BrightnessContrastEffect;
class Effect;
}

class ImageProcessingMode;

class ImageEffect: public IEffect
{
	VL_INSTRUMENT_CLASS( ImageEffect, IEffect );
public:
	ImageEffect( const std::wstring& effectName );

	void	SetImageProcessingMode( ImageProcessingMode* imProcMode );

	virtual void ApplyEffect() override;

protected:
	virtual VLExtension::Effect* GetEffect() = 0;

private:
	vl::ref<VLExtension::EffectPipeline> pipeline_;
	ImageProcessingMode* imProcMode_;
};
