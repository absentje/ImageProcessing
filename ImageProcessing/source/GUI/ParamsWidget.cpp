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
	auto widgetParam = new FloatParamWidget( param, min, max, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( widgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void ParamsWidget::AddParam( const std::wstring& paramName, int& param, int min, int max )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto widgetParam = new IntParamWidget( param, min, max, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( widgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void ParamsWidget::AddParam( const std::wstring& paramName, bool& param )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto widgetParam = new BoolParamWidget( param, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( widgetParam, 1 );
	mainLayout->addSpacing( 5 );

}

void ParamsWidget::AddParam( const std::wstring& paramName, vl::Texture& param )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto widgetParam = new TextureParamWidget( param, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( widgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void ParamsWidget::AddParam( const std::wstring& paramName, vl::Geometry& param )
{
	auto label = new QLabel( QString::fromStdWString( paramName ), this );
	auto widgetParam = new GeometryParamWidget( param, this );
	mainLayout->addWidget( label, 1 );
	mainLayout->addWidget( widgetParam, 1 );
	mainLayout->addSpacing( 5 );
}

void ParamsWidget::OnUpdate()
{
	effect_->UpdateData();
}