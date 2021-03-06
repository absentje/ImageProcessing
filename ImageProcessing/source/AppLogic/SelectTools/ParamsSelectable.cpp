#include "ParamsSelectable.h"
#include <GUI/ParamsWidget.h>

ParamsSelectable::ParamsSelectable( const std::wstring& name )
	: super( name )
{

}

QWidget* ParamsSelectable::CreateWidget( QWidget* parent )
{
	ParamsWidget* paramsWidget = new ParamsWidget( parent, this );
	OnCreatedParamsWidget( paramsWidget );
	return paramsWidget;
}