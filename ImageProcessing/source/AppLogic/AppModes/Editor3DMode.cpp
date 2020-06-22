#include "Editor3DMode.h"
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/TrackballManipulator.hpp>
#include <vlGraphics/GhostCameraManipulator.hpp>

using ManipulatorType = vl::TrackballManipulator;


Editor3DMode::Editor3DMode()
    : super( L"Editor 3D mode" )
{
    // set camera
    vl::vec3 eye = vl::vec3( 0, 0, 5 );
    vl::vec3 center = vl::vec3( 0, 0, 0 );
    vl::vec3 up = vl::vec3( 0, 1, 0 );
    vl::mat4 view_mat = vl::mat4::getLookAt( eye, center, up );
    camera_->setViewMatrix( view_mat );

    // set manipulator
    vl::ref<ManipulatorType> manipulator = new ManipulatorType;
    manipulator->setCamera( camera_.get() );
    UIEventListeners_.push_back( manipulator.get() );

    // set modeList
    mode3DList_ = new Mode3DList( scene_.get() );
}

QWidget* Editor3DMode::CreateWidget( QWidget* parent )
{
    return mode3DList_->CreateWidget( parent );
}