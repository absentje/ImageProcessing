#pragma once
#include "Selectable.h"
#include <unordered_map>
#include <string>

class SelectableList: public Selectable
{
	VL_INSTRUMENT_CLASS( SelectableList, Selectable );
public:
	SelectableList( const std::wstring& name );

	virtual void Enable() {}
	virtual void Disable() {}
	virtual QWidget* CreateWidget( QWidget* parent ) override;

protected:
	void Add( Selectable* selectable );
	std::unordered_map<std::wstring, vl::ref<Selectable>> selectables_;

private:
	friend class SelectableListWidget;
};

