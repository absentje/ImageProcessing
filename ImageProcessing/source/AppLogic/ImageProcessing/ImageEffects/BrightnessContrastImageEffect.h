#pragma once
#include <AppLogic/ImageProcessing/ImageEffect.h>

namespace VLExtension
{
class Effect;
class BrightnessContrastEffect;
}

class BrightnessContrastImageEffect: public ImageEffect
{
	VL_INSTRUMENT_CLASS( BrightnessContrastImageEffect, ImageEffect );
public:
	BrightnessContrastImageEffect();

	virtual void UpdateData() override;
	virtual VLExtension::Effect* GetEffect() override;

protected: 
	// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) override;

private:
	vl::ref<VLExtension::Effect>   pipeEffect_;
	float brightness_ = 0.f;
	float contrast_ = 0.f;
};

