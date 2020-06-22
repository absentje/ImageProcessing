#pragma once
#include <AppLogic/SelectTools/ParamsSelectable.h>
#include <vlGraphics/SceneManagerActorTree.hpp>

class Mode3D: public ParamsSelectable
{
	VL_INSTRUMENT_CLASS( Mode3D, ParamsSelectable );
public:
	Mode3D( const std::wstring& name, vl::SceneManagerActorTree* scene );

	virtual void Enable( bool value ) override;
	virtual void UpdateData() = 0;

protected:
	vl::ref<vl::SceneManagerActorTree> scene_;
};
