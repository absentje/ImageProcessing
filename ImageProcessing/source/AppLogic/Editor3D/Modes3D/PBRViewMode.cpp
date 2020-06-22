#include "PBRViewMode.h"
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Geometry.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>
#include <VLExtension/Actor.h>
#include <VLExtension/Actors/SkyBoxActor.h>

namespace
{
vl::ref<vl::Actor> createPlaneActor()
{
    vl::ref<VLExtension::Actor> planeActor = new VLExtension::Actor( vl::makeBox( vl::vec3( 0.f ), 1.f, 1.f, 1.f ).get() );
    auto shader = planeActor->GetShader();

    vl::ref<vl::Texture> texture = new vl::Texture( "resources/images/plane_texture.jpg", vl::TF_RGBA, true );
    texture->getTexParameter()->setWrap( vl::ETexParamWrap::TPW_CLAMP_TO_BORDER );
    texture->getTexParameter()->setMinFilter( vl::ETexParamFilter::TPF_LINEAR_MIPMAP_LINEAR );
    texture->getTexParameter()->setMagFilter( vl::ETexParamFilter::TPF_LINEAR );
    shader->gocTextureSampler( 0 )->setTexture( texture.get() );
    shader->SetVShader( L"resources/glsl/test_plane_view.vs" );
    shader->SetFShader( L"resources/glsl/test_plane_view.fs" );
    shader->enable( vl::EN_DEPTH_TEST );
    return planeActor;
}
}

PBRViewMode::PBRViewMode( vl::SceneManagerActorTree* scene )
	: super( L"PBR View mode", scene )
{
    actorTree_ = new vl::ActorTree;
    actorTree_->addActor( createPlaneActor().get() );
    actorTree_->addActor( new VLExtension::SkyBoxActor );
}

void	PBRViewMode::Enable( bool value )
{
	super::Enable( value );
    if ( value )
    {
        scene_->setCullingEnabled( false );
        scene_->tree()->addChild( actorTree_.get() );
    }
}

void	PBRViewMode::UpdateData()
{

}

void	PBRViewMode::OnCreatedParamsWidget( ParamsWidget* paramsWidget )
{

}