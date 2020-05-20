#include "Editor3DMode.h"
#include <GUI/Editor3DModeWidget.h>
#include <vlGraphics/SceneManagerActorTree.hpp>

namespace
{
}

Editor3DMode::Editor3DMode()
    : super( L"Editor 3D mode" )
{
}

QWidget* Editor3DMode::CreateWidget( QWidget* parent )
{
    return new Editor3DModeWidget( parent, this );
}