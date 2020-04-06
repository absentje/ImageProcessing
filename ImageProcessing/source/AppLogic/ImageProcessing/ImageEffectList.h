#pragma once
#include <AppLogic/SelectTools/SelectableList.h>

namespace VLExtension
{
class EffectPipeline;
class Effect;
}

class ImageEffect;

class ImageEffectList: public SelectableList
{
	VL_INSTRUMENT_CLASS( ImageEffectList, SelectableList );
public:
	ImageEffectList();
	VLExtension::EffectPipeline* GetImageEffectsPipeline();

private:
	vl::ref<VLExtension::EffectPipeline> pipeline_;
};