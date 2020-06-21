#pragma once
#include <AppLogic/Editor3D/Mode3D.h>

class PBRViewMode: public Mode3D
{
	VL_INSTRUMENT_CLASS( PBRViewMode, Mode3D );
public:
	PBRViewMode();

	virtual void Enable( bool value ) override;
	virtual void UpdateData() = 0;
};
