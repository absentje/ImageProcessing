#pragma once
#include <AppLogic/SelectTools/ParamsSelectable.h>

class Mode3D: public ParamsSelectable
{
	VL_INSTRUMENT_CLASS( Mode3D, ParamsSelectable );
public:
	Mode3D( const std::wstring& name );

	virtual void Enable( bool value ) override;
	virtual void UpdateData() = 0;


};
