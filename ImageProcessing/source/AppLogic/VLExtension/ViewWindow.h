#pragma once
#include <vlCore/Object.hpp>

namespace vl
{
    class UIEventListener;
    class Rendering;
    class SceneManagerActorTree;
    class OpenGLContext;
}

namespace VLExtension
{
class FBORender;
class TextureViewActor;

class ViewWindow: public vl::Object
{
    VL_INSTRUMENT_CLASS( ViewWindow, vl::Object )
public:
    ViewWindow( vl::OpenGLContext* vl_context );
    ~ViewWindow() override;

    void    AddEventListener( vl::UIEventListener* evListener );
    void    RemoveEventListener( vl::UIEventListener* evListener );

    void	ShowScene( vl::SceneManagerActorTree* scene );

    void    Resize( int width, int height );
    void    ClearViewWindow();
    void    Render();
private:
    vl::OpenGLContext* pCanvas;

    vl::ref<vl::Rendering>				pRender;
    vl::ref<vl::SceneManagerActorTree>  pViewScene;
};
}