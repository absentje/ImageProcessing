#include "AppMode.h"
#include <AppLogic/VLExtension/ViewWindow.h>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/UIEventListener.hpp>

AppMode::AppMode( const std::wstring& name )
	: super( name )
{
	pScene = new vl::SceneManagerActorTree;
}

void AppMode::Enable()
{
	auto* viewWindow = VLExtension::ViewWindow::currentViewWindow;

	viewWindow->ShowScene( pScene.get() );
	if ( pUIEventListener )
	{
		viewWindow->AddEventListener( pUIEventListener.get() );
	}
}

void AppMode::Disable()
{
	auto* viewWindow = VLExtension::ViewWindow::currentViewWindow;

	viewWindow->ClearViewWindow();
	if ( pUIEventListener )
	{
		viewWindow->RemoveEventListener( pUIEventListener.get() );
	}
}