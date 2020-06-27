#include "PBRViewMode.h"
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Geometry.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>
#include <VLExtension/Actor.h>
#include <VLExtension/Actors/SkyBoxActor.h>
#include <GUI/ParamsWidget.h>
#include <unordered_map>

namespace
{
vl::ref<VLExtension::Actor> createPlaneActor()
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

vl::ref<VLExtension::Actor> createMainActor()
{
    vl::ref<vl::Geometry> geom = vl::makeBox( vl::vec3( 0.f ), 1.f, 1.f, 1.f );
    geom->computeNormals();
    vl::ref<VLExtension::Actor> planeActor = new VLExtension::Actor( geom.get() );
    auto shader = planeActor->GetShader();
    shader->SetVShader( L"resources/glsl/pbr.vs" );
    shader->SetFShader( L"resources/glsl/pbr.fs" );
    shader->enable( vl::EN_DEPTH_TEST );
    return planeActor;
}

const std::array<std::string, PBRViewMode::cTexturesCount> textureNames
{
    "albedoMap",
    "normalMap",
    "metallicMap",
    "roughnessMap",
    "aoMap",
};
}

PBRViewMode::PBRViewMode( vl::SceneManagerActorTree* scene )
	: super( L"PBR View mode", scene )
{
    actor_ = createMainActor();
    geom_ = actor_->GetGeometry();
    auto shader = actor_->GetShader();
    for ( size_t i = 0; i != cTexturesCount; ++i )
    {
        textures_[i] = new vl::Texture;
        actor_->gocUniform( textureNames[i].c_str() )->setUniform( int( i ) );
        shader->gocTextureSampler( i )->setTexture( textures_[i].get() );

        textures_[i]->getTexParameter()->setWrap( vl::ETexParamWrap::TPW_CLAMP_TO_BORDER );
        textures_[i]->getTexParameter()->setMinFilter( vl::ETexParamFilter::TPF_LINEAR_MIPMAP_LINEAR );
        textures_[i]->getTexParameter()->setMagFilter( vl::ETexParamFilter::TPF_LINEAR );
    }

    actorTree_ = new vl::ActorTree;
    actorTree_->addActor( actor_.get() );
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
    /*auto shader = actor_->GetShader();
    for ( size_t i = 0; i != cTexturesCount; ++i )
    {
        shader->gocTextureSampler( i )->setTexture( textures_[i].get() );
    }*/
}

void	PBRViewMode::OnCreatedParamsWidget( ParamsWidget* paramsWidget )
{
    paramsWidget->AddParam(L"Mesh", *geom_ );
    paramsWidget->AddParam( L"Albedo map", *textures_[0] );
    paramsWidget->AddParam( L"Normal map", *textures_[1] );
    paramsWidget->AddParam( L"Metallic map", *textures_[2] );
    paramsWidget->AddParam( L"Roughness map", *textures_[3] );
    paramsWidget->AddParam( L"AO map", *textures_[4] );
}