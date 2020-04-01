#pragma once
#include "Selectable.h"

class ParamsSelectable: public Selectable
{
	VL_INSTRUMENT_CLASS( ParamsSelectable, Selectable );
public:
	ParamsSelectable( const std::wstring& name );

	virtual void UpdateData() = 0;
	virtual QWidget* CreateWidget( QWidget* parent ) override final;

protected:
// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) = 0;
};