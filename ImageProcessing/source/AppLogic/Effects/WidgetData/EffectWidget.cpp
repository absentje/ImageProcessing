#include "EffectWidget.h"
#include <QVBoxLayout>
#include <QSlider>
#include "EffectParamWidget.h"
#include <AppLogic/Effects/IEffect.h>
#include <QLabel>

EffectWidget::EffectWidget( QWidget* parent, IEffect* effect )
	: QGroupBox( QString::fromStdWString( effect->GetEffectName() ), parent ), effect_( effect )
{
	mainLayout = new QVBoxLayout( this );
	setLayout( mainLayout );
}

void EffectWidget::AddParam( const std::wstring& paramName, float& param, float min, float max )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto floatWidgetParam = new FloatWidgetParam( param, min, max, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( floatWidgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void EffectWidget::AddParam( const std::wstring& paramName, int& param, int min, int max )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto intWidgetParam = new IntWidgetParam( param, min, max, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( intWidgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void EffectWidget::OnUpdate()
{
	effect_->UpdateData();
}