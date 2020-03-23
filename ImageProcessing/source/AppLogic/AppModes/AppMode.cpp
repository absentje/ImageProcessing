#include "AppMode.h"
#include <AppLogic/VLExtension/ViewWindow.h>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/UIEventListener.hpp>

AppMode::AppMode()
{
	pScene = new vl::SceneManagerActorTree;
}

void AppMode::Enable( VLExtension::ViewWindow* viewWindow/*, WidgetNode* widgetNode*/ )
{
//	enable_( widgetNode );
	viewWindow->ShowScene( pScene.get() );
	if ( pUIEventListener )
	{
		viewWindow->AddEventListener( pUIEventListener.get() );
	}
}