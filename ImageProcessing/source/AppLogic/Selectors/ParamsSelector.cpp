#include "ParamsSelector.h"
#include <AppLogic/Selectors/WidgetData/ParamsWidget.h>

ParamsSelector::ParamsSelector( const std::wstring& name )
	: super( name )
{

}

QWidget* ParamsSelector::CreateWidget( QWidget* parent )
{
	ParamsWidget* paramsWidget = new ParamsWidget( parent, this );
	OnCreatedParamsWidget( paramsWidget );
	return paramsWidget;
}