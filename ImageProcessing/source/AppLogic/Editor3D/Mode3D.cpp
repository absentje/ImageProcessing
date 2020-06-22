#include "Mode3D.h"
#include <GUI/ParamsWidget.h>

Mode3D::Mode3D( const std::wstring& name, vl::SceneManagerActorTree* scene )
	: super( name ), scene_( scene )
{

}

void Mode3D::Enable( bool value )
{
	if ( !value )
	{
		scene_->tree()->actors()->clear();
		scene_->tree()->eraseAllChildren();
	}

}