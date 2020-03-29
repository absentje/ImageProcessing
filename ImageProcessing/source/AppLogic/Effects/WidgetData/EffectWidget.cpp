#include "EffectWidget.h"
#include <QVBoxLayout>
#include <QSlider>
#include "EffectParamWidget.h"
#include <AppLogic/Effects/IEffect.h>

EffectWidget::EffectWidget( QWidget* parent, IEffect* effect )
	: QWidget( parent ), effect_( effect )
{
	mainLayout = new QVBoxLayout( this );
	setLayout( mainLayout );
}

void EffectWidget::AddParam( const std::wstring& paramName, float& param, float min, float max )
{
	auto floatWidgetParam = new FloatWidgetParam( param, min, max, this );
	mainLayout->addWidget( floatWidgetParam );
}

void EffectWidget::AddParam( const std::wstring& paramName, int& param, int min, int max )
{
	auto intWidgetParam = new IntWidgetParam( param, min, max, this );
	mainLayout->addWidget( intWidgetParam );
}

void EffectWidget::OnUpdate()
{
	effect_->UpdateData();
}