#include "ParamWidget.h"
#include <AppLogic/Selectors/Selector.h>
#include <AppLogic/Selectors/WidgetData/ParamsWidget.h>
#include <vlCore/glsl_math.hpp>

namespace
{
constexpr int cMaxSliderValue = 1000;

}

///////////////////////////////////////////////////////////////
// FloatParamWidget ///////////////////////////////////////////
FloatParamWidget::FloatParamWidget( float& param, float min, float max, ParamsWidget* paramsWidget )
	: QSlider( Qt::Orientation::Horizontal, paramsWidget ), effectWidget_( paramsWidget ),
	param_( param ), min_( min ), max_( max )
{
	connect( this, SIGNAL( valueChanged( int ) ),
			 this, SLOT( sliderValueChanged_( int ) ) );

	setMinimum( 0 );
	setMaximum( cMaxSliderValue );
	setValue( cMaxSliderValue / 2 );
}

void FloatParamWidget::sliderValueChanged_( int value )
{
	param_ = vl::mix( min_, max_, float( value ) / float( cMaxSliderValue ) );
	effectWidget_->OnUpdate();
}
///////////////////////////////////////////////////////////////
// IntParamWidget /////////////////////////////////////////////
IntParamWidget::IntParamWidget( int& param, int min, int max, ParamsWidget* paramsWidget )
	: QSlider( Qt::Orientation::Horizontal, paramsWidget ), effectWidget_( paramsWidget ),
	param_( param ), min_( min ), max_( max )
{
	connect( this, SIGNAL( valueChanged( int ) ),
			 this, SLOT( sliderValueChanged_( int ) ) );

	setMinimum( min_ );
	setMaximum( max_ );
	setValue( ( max_ + min_ ) / 2 );
}

void IntParamWidget::sliderValueChanged_( int value )
{
	param_ = value;
	effectWidget_->OnUpdate();
}