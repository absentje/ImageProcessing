#include "ParamsWidget.h"
#include <QVBoxLayout>
#include <QSlider>
#include "ParamWidget.h"
#include <AppLogic/SelectTools/ParamsSelectable.h>
#include <QLabel>

ParamsWidget::ParamsWidget( QWidget* parent, ParamsSelectable* effect )
	: QGroupBox( QString::fromStdWString( effect->GetName() ), parent ), effect_( effect )
{
	mainLayout = new QVBoxLayout( this );
	setLayout( mainLayout );
}

void ParamsWidget::AddParam( const std::wstring& paramName, float& param, float min, float max )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto floatWidgetParam = new FloatParamWidget( param, min, max, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( floatWidgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void ParamsWidget::AddParam( const std::wstring& paramName, int& param, int min, int max )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto intWidgetParam = new IntParamWidget( param, min, max, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( intWidgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void ParamsWidget::OnUpdate()
{
	effect_->UpdateData();
}