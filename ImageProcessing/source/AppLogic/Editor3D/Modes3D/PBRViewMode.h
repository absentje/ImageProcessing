#pragma once
#include <AppLogic/Editor3D/Mode3D.h>
#include <vlGraphics/ActorTree.hpp>
#include <VLExtension/Actor.h>
#include <array>

class PBRViewMode: public Mode3D
{
	VL_INSTRUMENT_CLASS( PBRViewMode, Mode3D );
public:
	PBRViewMode( vl::SceneManagerActorTree* scene );

	virtual void Enable( bool value ) override;
	virtual void UpdateData() override;

	static constexpr size_t cTexturesCount = 5U;
protected:
	// widget-parameters will be attached here
	virtual void OnCreatedParamsWidget( ParamsWidget* paramsWidget ) override;

private:
	vl::ref<vl::ActorTree> actorTree_ = nullptr;

	vl::ref<VLExtension::Actor> actor_ = nullptr;
	vl::ref<vl::Geometry> geom_ = nullptr;

	std::array<vl::ref<vl::Texture>, cTexturesCount> textures_;
};
