#pragma once
#include "ImageEffect.h"

namespace VLExtension
{
class BrightnessContrastEffect;
}

class BrightnessContrastImageEffect: public ImageEffect
{
	VL_INSTRUMENT_CLASS( BrightnessContrastImageEffect, ImageEffect );
public:
	BrightnessContrastImageEffect();

	virtual void UpdateData() override;

protected: 
	virtual VLExtension::Effect* GetEffect() override;
	// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) override;

private:
	vl::ref<VLExtension::BrightnessContrastEffect>   pipeEffect_;
	float brightness_ = 0.f;
	float contrast_ = 0.f;
};

