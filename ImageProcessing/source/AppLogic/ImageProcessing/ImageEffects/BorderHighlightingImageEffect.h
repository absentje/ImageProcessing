#pragma once
#include <AppLogic/ImageProcessing/ImageEffect.h>

class BorderHighlightingImageEffect: public ImageEffect
{
	VL_INSTRUMENT_CLASS( BorderHighlightingImageEffect, ImageEffect ); 
public:
	BorderHighlightingImageEffect();

	virtual void UpdateData() override;
	virtual VLExtension::Effect* GetEffect() override;

protected:
	// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) override;

private:
	vl::ref<VLExtension::Effect>   pipeEffect_;
	float sigma_ = 2.f;
	bool isColorful_ = true;
};