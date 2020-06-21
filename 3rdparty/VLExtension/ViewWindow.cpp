#include "ViewWindow.h"
#include <vlGraphics/UIEventListener.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/Text.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <vlGraphics/Clear.hpp>
#include <VLExtension/Actors/FPSActor.h>

#include "Actors/TextureViewActor.h"
#include "FBORender.h"
#include "Util/Timer.h"

namespace VLExtension
{
namespace
{
constexpr bool FPSEnable = true;
constexpr int FPSActorRenderRank = 1000;
const vl::vec4 clearColor = vl::vec4( 0.2f, 0.3f, 0.4f, 1.0f );
}

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
        static const float FPS = 1000.f;
        static const float FPS_reverse = 1.f / FPS;
        if ( timer.GetElapsedSeconds() > FPS_reverse )
        {
            pViewWindow->Render();
            timer.Start();
        }

        pViewWindow;
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
    rendering_ = new vl::Rendering;
    rendering_->renderer()->setFramebuffer( pCanvas->framebuffer() );
    rendering_->camera()->viewport()->setClearColor( clearColor );
    // делаем первичный рендер, чтоб создался контекст
    rendering_->render();
    AddEventListener( vl::ref<VWEventListener>( new VWEventListener( this ) ).get() );

    background_ = new vl::SceneManagerActorTree;
    background_->setCullingEnabled( false );

    { // add clear actor (glClear)
        vl::ref<vl::Clear> clearRenderable = new vl::Clear;
        clearRenderable->setClearColorValue( clearColor );
        clearRenderable->setClearColorBuffer( true );
        clearRenderable->setClearDepthBuffer( true );

        vl::ref<vl::Actor> clearActor = new vl::Actor( clearRenderable.get(), new vl::Effect );
        clearActor->setRenderRank( -1 );
        background_->tree()->addActor( clearActor.get() );
    }
    { // add fps actor
        if ( FPSEnable && vl::Has_Fixed_Function_Pipeline )
        {
            vl::ref<vl::Actor> fpsActor = new VLExtension::FPSActor;
            fpsActor->setRenderRank( FPSActorRenderRank );
            background_->tree()->addActor( fpsActor.get() );
        }
    }
    ClearViewWindow();
}

ViewWindow::~ViewWindow()
{
    rendering_ = nullptr;
    viewScene_ = nullptr;
}

void ViewWindow::ShowScene( vl::SceneManagerActorTree* scene )
{
    VL_CHECK( scene );
    ClearViewWindow();

    viewScene_ = scene;
    rendering_->sceneManagers()->push_back( scene );
}

void    ViewWindow::ClearViewWindow()
{
    rendering_->sceneManagers()->clear();
    rendering_->sceneManagers()->push_back( background_.get() );
    viewScene_ = nullptr;
}

void    ViewWindow::Render()
{
    if ( rendering_ )
    {
        rendering_->render();
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
    UpdateCamera();
    Render();
}

void    ViewWindow::UpdateCamera()
{
    vl::Camera* pCamera = rendering_->camera();
    pCamera->viewport()->set( 0, 0, GetWidth(), GetHeight() );
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

int     ViewWindow::GetWidth() const
{
    return pCanvas->width();
}

int     ViewWindow::GetHeight() const
{
    return pCanvas->height();
}

void	ViewWindow::AddEventListener( vl::UIEventListener* evListener )
{
    pCanvas->addEventListener( evListener );
}

void	ViewWindow::RemoveEventListener( vl::UIEventListener* evListener )
{
    pCanvas->removeEventListener( evListener );
}

void    ViewWindow::SetCamera( vl::Camera* camera )
{
    rendering_->setCamera( camera );
}

}