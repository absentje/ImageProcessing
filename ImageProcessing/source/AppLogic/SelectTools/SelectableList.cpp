#include "SelectableList.h"
#include <AppLogic/SelectTools/Widgets/SelectableListWidget.h>

SelectableList::SelectableList( const std::wstring& name )
	: super( name )
{

}

void SelectableList::Add( Selectable* selectable )
{
	if ( selectable )
	{
		selectables_[selectable->GetName()] = selectable;
	}
}

QWidget* SelectableList::CreateWidget( QWidget* parent )
{
	return new SelectableListWidget( this, parent );
}