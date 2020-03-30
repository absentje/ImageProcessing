#include "ParamsSelector.h"
#include <AppLogic/Effects/WidgetData/ParamsWidget.h>

ParamsSelector::ParamsSelector( const std::wstring& name )
	: super( name )
{

}

QWidget* ParamsSelector::CreateWidget( QWidget* parent )
{
	ParamsWidget* effectWidget = new ParamsWidget( parent, this );
	OnCreatedEffectWidget( effectWidget );
	return effectWidget;
}