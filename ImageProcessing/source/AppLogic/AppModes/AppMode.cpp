#include "AppMode.h"
#include <VLExtension/ViewWindow.h>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/UIEventListener.hpp>

AppMode::AppMode( const std::wstring& name )
	: super( name )
{
	scene_ = new vl::SceneManagerActorTree;
	camera_ = new vl::Camera;
}

void AppMode::Enable()
{
	auto* viewWindow = VLExtension::ViewWindow::currentViewWindow;

	viewWindow->ShowScene( scene_.get() );
	viewWindow->SetCamera( camera_.get() );

	for ( auto& evListener : UIEventListeners_ )
	{
		viewWindow->AddEventListener( evListener.get() );
	}
}

void AppMode::Disable()
{
	auto* viewWindow = VLExtension::ViewWindow::currentViewWindow;

	viewWindow->ClearViewWindow();
	for ( auto& evListener : UIEventListeners_ )
	{
		viewWindow->RemoveEventListener( evListener.get() );
	}
}