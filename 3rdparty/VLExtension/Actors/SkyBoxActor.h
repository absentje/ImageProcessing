#pragma once
#include <VLExtension/Actor.h>
#include <vlGraphics/Texture.hpp>
#include <string>

namespace VLExtension
{
class SkyBoxActor : public Actor
{
	VL_INSTRUMENT_CLASS( SkyBoxActor, Actor );
public:
	SkyBoxActor();

	void SetCubemap( const std::string& cubemap_folder );
	void SetCubemap( vl::Image* cubemap );
	void SetCubemap( vl::Texture* cubemap );

private:
	void prepareEffect_();

	vl::ref<vl::Texture> cubemap_;
};
}