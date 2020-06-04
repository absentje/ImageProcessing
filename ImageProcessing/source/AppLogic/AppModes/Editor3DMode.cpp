#include "Editor3DMode.h"
#include <GUI/Editor3DModeWidget.h>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/TrackballManipulator.hpp>
#include <vlGraphics/GhostCameraManipulator.hpp>
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Geometry.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>
#include <VLExtension/Actor.h>

namespace
{

vl::ref<vl::Actor> createPlaneActor()
{
    vl::ref<VLExtension::Actor> planeActor = new VLExtension::Actor( vl::makeBox( vl::vec3( 0.f ), 1.f, 1.f, 1.f ).get() );
    auto shader = planeActor->GetShader();

    vl::ref<vl::Texture> texture = new vl::Texture( "resources/images/plane_texture.jpg", vl::TF_RGBA, true );
    texture->getTexParameter()->setWrap( vl::ETexParamWrap::TPW_REPEAT );
    texture->getTexParameter()->setMinFilter( vl::ETexParamFilter::TPF_LINEAR_MIPMAP_LINEAR );
//    texture->getTexParameter()->setMinFilter( vl::ETexParamFilter::TPF_NEAREST );

    shader->gocTextureSampler( 0 )->setTexture( texture.get() );
    shader->SetVShader( L"resources/glsl/test_plane_view.vs" );
    shader->SetFShader( L"resources/glsl/test_plane_view.fs" );
    shader->enable( vl::EN_DEPTH_TEST );
    return planeActor;
}

}

Editor3DMode::Editor3DMode()
    : super( L"Editor 3D mode" )
{
    scene_->setCullingEnabled( false );
    scene_->tree()->addActor( createPlaneActor().get() );

    vl::vec3 eye = vl::vec3( 0, 1, 4 ); // camera position
    vl::vec3 center = vl::vec3( 0, 0, 0 );   // point the camera is looking at
    vl::vec3 up = vl::vec3( 0, 1, 0 );   // up direction
    vl::mat4 view_mat = vl::mat4::getLookAt( eye, center, up );
    camera_->setViewMatrix( view_mat );

    vl::ref<vl::TrackballManipulator> manipulator = new vl::TrackballManipulator;
    manipulator->setCamera( camera_.get() );
    UIEventListeners_.push_back( manipulator.get() );
}

QWidget* Editor3DMode::CreateWidget( QWidget* parent )
{
    return new Editor3DModeWidget( parent, this );
}