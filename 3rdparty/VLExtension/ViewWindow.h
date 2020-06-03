#pragma once
#include <vlCore/Object.hpp>

namespace vl
{
    class UIEventListener;
    class Rendering;
    class SceneManagerActorTree;
    class OpenGLContext;
    class Camera;
}

namespace VLExtension
{

class ViewWindow: public vl::Object
{
    VL_INSTRUMENT_CLASS( ViewWindow, vl::Object )
public:
    ViewWindow( vl::OpenGLContext* vl_context );
    ~ViewWindow() override;

    void    AddEventListener( vl::UIEventListener* evListener );
    void    RemoveEventListener( vl::UIEventListener* evListener );

    void	ShowScene( vl::SceneManagerActorTree* scene );
    void    SetCamera( vl::Camera* camera );

    void    Resize( int width, int height );
    void    ClearViewWindow();
    void    Render();

    static ViewWindow* currentViewWindow;

private:
    vl::OpenGLContext* pCanvas;

    vl::ref<vl::Rendering>				rendering_;
    vl::ref<vl::SceneManagerActorTree>  viewScene_;
    vl::ref<vl::SceneManagerActorTree>  background_;
};
}