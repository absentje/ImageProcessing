#include "SelectableList.h"
#include <GUI/SelectableListWidget.h>

SelectableList::SelectableList( const std::wstring& name )
	: super( name )
{

}

Selectable* SelectableList::SelectableChanged( const std::wstring& selectable_name )
{
	EnableSelectable_( curSelectedStr_, false );
	curSelectedStr_ = selectable_name;
	EnableSelectable_( curSelectedStr_, true );
	return GetSelectable_( selectable_name );
}

Selectable* SelectableList::GetSelectable_( const std::wstring& selectable_name )
{
	auto it = selectables_.find( selectable_name );
	return it != selectables_.end() ? it->second.get() : nullptr;
}


void SelectableList::EnableSelectable_( const std::wstring& selectable_name, bool value )
{
	if ( auto selectable = GetSelectable_( selectable_name ) )
	{
		selectable->Enable( value );
	}
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
	auto widget = new SelectableListWidget( this, parent );
	widget->AddSelectableName( L"" );
	for ( auto& selectable : selectables_ )
	{
		widget->AddSelectableName( selectable.second->GetName());
	}
	return widget;
}