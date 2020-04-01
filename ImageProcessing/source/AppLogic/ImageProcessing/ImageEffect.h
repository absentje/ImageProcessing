#pragma once
#include <AppLogic/SelectTools/ParamsSelectable.h>

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

class ImageEffect: public ParamsSelectable
{
	VL_INSTRUMENT_CLASS( ImageEffect, ParamsSelectable );
public:
	ImageEffect( const std::wstring& name );

	void	SetImageProcessingMode( ImageProcessingMode* imProcMode );

	virtual void Apply() override;
	virtual void UpdateData() = 0;

protected:
	virtual VLExtension::Effect* GetEffect() = 0;

private:
	vl::ref<VLExtension::EffectPipeline> pipeline_;
	ImageProcessingMode* imProcMode_ = nullptr;
};
