#include "Editor3DMode.h"
#include <GUI/Editor3DModeWidget.h>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/TrackballManipulator.hpp>

namespace
{

vl::ref<vl::Actor> createPlaneActor()
{

    return nullptr;
}

}

Editor3DMode::Editor3DMode()
    : super( L"Editor 3D mode" )
{

    scene_->setCullingEnabled( false );
//    scene_->tree()->addActor( createPlaneActor().get() );



}

QWidget* Editor3DMode::CreateWidget( QWidget* parent )
{
    return new Editor3DModeWidget( parent, this );
}