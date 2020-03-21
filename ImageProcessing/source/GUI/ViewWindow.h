#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H
#include <QWidget>
#include <vlCore/Object.hpp>

class FBORender;
class Scene;
class TextureViewActor;

namespace vl
{
    class UIEventListener;
    class Rendering;
    class SceneManagerActorTree;
    class OpenGLContext;
}

class ViewWindow : public vl::Object
{
    VL_INSTRUMENT_CLASS(ViewWindow, vl::Object)
public:
    ViewWindow(vl::OpenGLContext* vl_context);
    ~ViewWindow() override;

    void    AddEventListener(vl::UIEventListener* evListener);
    void    RemoveEventListener(vl::UIEventListener* evListener);

    void	ShowScene(Scene* scene);

    void    Resize(int width, int height);
    void    ClearViewWindow();
    void    Render();
private:
    vl::OpenGLContext* pCanvas;

    vl::ref<vl::Rendering>				pRender;
    vl::ref<vl::SceneManagerActorTree>  pSceneMananager;
    vl::ref<Scene>                      pViewScene;
    vl::ref<FBORender>                  pFBO;
    vl::ref<TextureViewActor>           pViewActor;
};

#endif // VIEWWINDOW_H
