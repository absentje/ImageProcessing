#pragma once
#include <AppLogic/Editor3D/Mode3D.h>
#include <vlGraphics/ActorTree.hpp>

class PBRViewMode: public Mode3D
{
	VL_INSTRUMENT_CLASS( PBRViewMode, Mode3D );
public:
	PBRViewMode( vl::SceneManagerActorTree* scene );

	virtual void Enable( bool value ) override;
	virtual void UpdateData() override;

protected:
	// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) override;

private:
	vl::ref<vl::ActorTree> actorTree_;
};
