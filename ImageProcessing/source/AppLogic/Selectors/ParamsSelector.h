#pragma once
#include "Selector.h"

class ParamsSelector: public Selector
{
	VL_INSTRUMENT_CLASS( ParamsSelector, Selector );
public:
	ParamsSelector( const std::wstring& name );

	virtual void UpdateData() = 0;
	virtual QWidget* CreateWidget( QWidget* parent ) override final;

protected:
// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) = 0;
};