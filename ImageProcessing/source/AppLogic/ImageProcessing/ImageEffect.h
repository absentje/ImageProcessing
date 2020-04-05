#pragma once
#include <AppLogic/SelectTools/ParamsSelectable.h>

namespace VLExtension
{
class EffectPipeline;
class Effect;
}

class ImageProcessingMode;

class ImageEffect: public ParamsSelectable
{
	VL_INSTRUMENT_CLASS( ImageEffect, ParamsSelectable );
public:
	ImageEffect( const std::wstring& name );

	virtual void Enable() override;
	virtual void Disable() override;
	virtual void UpdateData() = 0;

	virtual VLExtension::Effect* GetEffect() = 0;
};
