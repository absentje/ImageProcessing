#include "ParamWidget.h"
#include <AppLogic/SelectTools/Selectable.h>
#include <GUI/ParamsWidget.h>
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

	float alpha = ( param - min ) / ( max - min );
	setValue( (int)vl::mix( float( 0 ), float( cMaxSliderValue ), alpha ) );
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
	setValue( param );
}

void IntParamWidget::sliderValueChanged_( int value )
{
	param_ = value;
	effectWidget_->OnUpdate();
}

///////////////////////////////////////////////////////////////
// BoolParamWidget /////////////////////////////////////////////
BoolParamWidget::BoolParamWidget( bool& param, ParamsWidget* paramsWidget )
	: QCheckBox( paramsWidget ), effectWidget_( paramsWidget ),
	param_( param )
{
	connect( this, SIGNAL( stateChanged( int ) ),
			 this, SLOT( checkBoxValueChanged_( int ) ) );
	setValue_( param );
}

void BoolParamWidget::setValue_( bool value )
{
	setCheckState( value ? Qt::CheckState::Checked : Qt::CheckState::Unchecked );
}

void BoolParamWidget::checkBoxValueChanged_( int value )
{
	param_ = value;
	effectWidget_->OnUpdate();
}