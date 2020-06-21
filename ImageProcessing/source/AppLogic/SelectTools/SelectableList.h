#pragma once
#include "Selectable.h"
#include <unordered_map>
#include <string>

class SelectableList: public Selectable
{
	VL_INSTRUMENT_CLASS( SelectableList, Selectable );
public:
	SelectableList( const std::wstring& name );

	virtual void Enable( bool value ) {}
	virtual QWidget* CreateWidget( QWidget* parent ) override;

	Selectable* SelectableChanged( const std::wstring& selectable_name );

protected:
	void Add( Selectable* selectable );

private:
	std::unordered_map<std::wstring, vl::ref<Selectable>> selectables_;
	std::wstring curSelectedStr_;

	void EnableSelectable_( const std::wstring& selectable_name, bool value );
	Selectable* GetSelectable_( const std::wstring& selectable_name );

};