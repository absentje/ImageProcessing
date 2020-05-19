#pragma once
#include <AppLogic/ImageProcessing/ImageEffect.h>

namespace VLExtension
{
class GaussianBlurEffect;
}

class GaussianBlurImageEffect : public ImageEffect
{
	VL_INSTRUMENT_CLASS( GaussianBlurImageEffect, ImageEffect );
public:
	GaussianBlurImageEffect();

	virtual void UpdateData() override;
	virtual VLExtension::Effect* GetEffect() override;

protected:
	// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) override;

private:
	vl::ref<VLExtension::GaussianBlurEffect>   pipeEffect_;
	float sigma_ = 2.f;
	bool isColorful_ = true;
};