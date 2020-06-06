#include "SkyBoxActor.h"
#include <vlGraphics/Geometry.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>
#include <limits>

namespace VLExtension
{
SkyBoxActor::SkyBoxActor()
	: super( vl::makeBox( vl::vec3( 0.f ), 5.f, 5.f, 5.f, false ).get() )
{
	prepareEffect_();
	SetCubemap( "resources/images/skyboxes/0" );
	setRenderRank( std::numeric_limits<int>::max() );
}

void SkyBoxActor::prepareEffect_()
{
	auto shader = GetShader();
	shader->SetVShader( L"resources/glsl/skybox.vs" );
	shader->SetFShader( L"resources/glsl/skybox.fs" );
	shader->enable( vl::EN_DEPTH_TEST );
	shader->gocDepthFunc()->set( vl::EFunction::FU_LEQUAL );
	/* // need it?
	if ( auto depthMask = shader->renderState( vl::ERenderState::RS_DepthMask )->as<vl::DepthMask>() )
	{
		depthMask->set( false );
	}
	*/
}


void SkyBoxActor::SetCubemap( const std::string& cubemap_folder )
{
	vl::ref<vl::Image> img_cubemap = vl::loadCubemap(
		cubemap_folder + "/right.jpg",		// (x+) right
		cubemap_folder + "/left.jpg",		// (x-) left
		cubemap_folder + "/top.jpg",		// (y+) top
		cubemap_folder + "/bottom.jpg",		// (y-) bottom
		cubemap_folder + "/front.jpg",		// (z+) front
		cubemap_folder + "/back.jpg"		// (z-) back
	);
	img_cubemap->flipVertically();
	SetCubemap( img_cubemap.get() );
}

void SkyBoxActor::SetCubemap( vl::Image* cubemap )
{
	if ( !cubemap )
	{
		return;
	}
	vl::ref<vl::Texture> cubemapTex = new vl::Texture;

	cubemapTex->createTextureCubemap( cubemap, vl::ETextureFormat::TF_RGBA, true );
	// Texture filtering modes
	cubemapTex->getTexParameter()->setMagFilter( vl::TPF_LINEAR );
	cubemapTex->getTexParameter()->setMinFilter( vl::TPF_LINEAR_MIPMAP_LINEAR );
	// Clamp to edge to minimize seams
	cubemapTex->getTexParameter()->setWrapS( vl::TPW_CLAMP_TO_EDGE );
	cubemapTex->getTexParameter()->setWrapT( vl::TPW_CLAMP_TO_EDGE );
	cubemapTex->getTexParameter()->setWrapR( vl::TPW_CLAMP_TO_EDGE );

	SetCubemap( cubemapTex.get() );

}

void SkyBoxActor::SetCubemap( vl::Texture* cubemap )
{
	if ( !cubemap )
	{
		return;
	}

	cubemap_ = cubemap;
	auto shader = GetShader();
	shader->gocTextureSampler( 0 )->setTexture( cubemap_.get() );
}

}