#include "EffectParamWidget.h"
#include <AppLogic/Effects/IEffect.h>
#include <AppLogic/Effects/WidgetData/EffectWidget.h>
#include <vlCore/glsl_math.hpp>

namespace
{
constexpr int cMaxSliderValue = 1000;

}

///////////////////////////////////////////////////////////////
// FloatWidgetParam ///////////////////////////////////////////
FloatWidgetParam::FloatWidgetParam( float& param, float min, float max, EffectWidget* effectWidget )
	: QSlider( Qt::Orientation::Horizontal, effectWidget ), effectWidget_( effectWidget ),
	param_( param ), min_( min ), max_( max )
{
	connect( this, SIGNAL( valueChanged( int ) ),
			 this, SLOT( sliderValueChanged_( int ) ) );

	setMinimum( 0 );
	setMaximum( cMaxSliderValue );
	setValue( cMaxSliderValue / 2 );
}

void FloatWidgetParam::sliderValueChanged_( int value )
{
	param_ = vl::mix( min_, max_, float( value ) / float( cMaxSliderValue ) );
	effectWidget_->OnUpdate();
}
///////////////////////////////////////////////////////////////
// IntWidgetParam /////////////////////////////////////////////
IntWidgetParam::IntWidgetParam( int& param, int min, int max, EffectWidget* effectWidget )
	: QSlider( Qt::Orientation::Horizontal, effectWidget ), effectWidget_( effectWidget ),
	param_( param ), min_( min ), max_( max )
{
	connect( this, SIGNAL( valueChanged( int ) ),
			 this, SLOT( sliderValueChanged_( int ) ) );

	setMinimum( min_ );
	setMaximum( max_ );
	setValue( ( max_ + min_ ) / 2 );
}

void IntWidgetParam::sliderValueChanged_( int value )
{
	param_ = value;
	effectWidget_->OnUpdate();
}