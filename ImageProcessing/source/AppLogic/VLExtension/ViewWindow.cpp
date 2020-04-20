#include "ViewWindow.h"
#include <vlGraphics/UIEventListener.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/Text.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/OpenGLContext.hpp>

#include <Actors/TextureViewActor.h>
#include <FBORender.h>
#include "AppLogic/Util/Timer.h"

namespace VLExtension
{
namespace
{
class VWEventListener: public vl::UIEventListener
{
    VL_INSTRUMENT_CLASS( VWEventListener, vl::UIEventListener )
public:
    VWEventListener( ViewWindow* vw ) : pViewWindow( vw ) { timer.Start(); }

    virtual void initEvent() override {}
    virtual void destroyEvent() override {}
    virtual void updateEvent() override {
        static const float FPS = 60.f;

        if ( timer.GetElapsedSeconds() > 1.f / FPS )
        {
            pViewWindow->Render();
            timer.Start();
        }
    }
    virtual void enableEvent( bool ) override {}
    virtual void addedListenerEvent( vl::OpenGLContext* ) override {}
    virtual void removedListenerEvent( vl::OpenGLContext* ) override {}
    virtual void mouseMoveEvent( int, int ) override {}
    virtual void mouseUpEvent( vl::EMouseButton, int, int ) override {}
    virtual void mouseDownEvent( vl::EMouseButton, int, int ) override {}
    virtual void mouseWheelEvent( int ) override {}
    virtual void keyPressEvent( unsigned short, vl::EKey ) override {}
    virtual void keyReleaseEvent( unsigned short, vl::EKey ) override {}
    virtual void fileDroppedEvent( const std::vector<vl::String>& ) override {}
    virtual void visibilityEvent( bool ) override {}

    virtual void resizeEvent( int x, int y ) override
    {
        pViewWindow->Resize( x, y );
    }
private:
    ViewWindow* pViewWindow;
    Timer timer;
};
}

ViewWindow* ViewWindow::currentViewWindow = nullptr;

ViewWindow::ViewWindow( vl::OpenGLContext* vl_context )
    : pCanvas( vl_context )
{
    pRender = new vl::Rendering;
    pRender->renderer()->setFramebuffer( pCanvas->framebuffer() );
    pRender->camera()->viewport()->setClearColor( 0.2f, 0.3f, 0.4f, 1.0f );
    // делаем первичный рендер, чтоб создался контекст
    pRender->render();
    AddEventListener( vl::ref<VWEventListener>( new VWEventListener( this ) ).get() );
}

ViewWindow::~ViewWindow()
{
    pRender = nullptr;
    pViewScene = nullptr;
}

void ViewWindow::ShowScene( vl::SceneManagerActorTree* scene )
{
    VL_CHECK( scene );
    ClearViewWindow();

    pViewScene = scene;
    pRender->sceneManagers()->push_back( scene );
}

void    ViewWindow::ClearViewWindow()
{
    pRender->sceneManagers()->clear();
    pViewScene = nullptr;
}

void    ViewWindow::Render()
{
    if ( pRender )
    {
        pRender->render();
    }

    // show rendering
    if ( pCanvas && pCanvas->hasDoubleBuffer() )
    {
        pCanvas->swapBuffers();
    }
}

void    ViewWindow::Resize( int width, int height )
{
    pCanvas->setSize( width, height );

    vl::Camera* pCamera = pRender->camera();
    pCamera->viewport()->set( 0, 0, width, height );
    switch ( pCamera->projectionMatrixType() )
    {
    case vl::EProjectionMatrixType::PMT_PerspectiveProjection:
        pCamera->setProjectionPerspective();
        break;
    case vl::EProjectionMatrixType::PMT_OrthographicProjection:
        pCamera->setProjectionOrtho();
        break;
    case vl::EProjectionMatrixType::PMT_PerspectiveProjectionFrustum:
        break;
    case vl::EProjectionMatrixType::PMT_UserProjection:
        break;
    }
} 

void	ViewWindow::AddEventListener( vl::UIEventListener* evListener )
{
    pCanvas->addEventListener( evListener );
}

void	ViewWindow::RemoveEventListener( vl::UIEventListener* evListener )
{
    pCanvas->removeEventListener( evListener );
}

}