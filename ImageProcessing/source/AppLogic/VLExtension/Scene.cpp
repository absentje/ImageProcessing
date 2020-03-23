#include "Scene.h"
#include "Actor.h"
#include "SceneController.h"
#include "ViewWindow.h"
#include <Actors/TextureViewActor.h>
#include <vlGraphics/SceneManagerActorTree.hpp>


namespace VLExtension
{
Scene::Scene( const std::wstring& scene_name )
    : pViewWindow( nullptr ), scene_name_( scene_name )
{
    pSceneManager = new vl::SceneManagerActorTree;
}

const std::wstring& Scene::GetName() const
{
    return scene_name_;
}

void    Scene::AddRenderActor( Actor* actor )
{
    VL_CHECK( actor );
    GetRenderSceneManager()->tree()->addActor( actor );
}

void	Scene::RemoveRenderActor( Actor* actor )
{
    VL_CHECK( actor );
    GetRenderSceneManager()->tree()->eraseActor( actor );
}

vl::SceneManagerActorTree* Scene::GetRenderSceneManager()
{
    return pSceneManager.get();
}

const vl::SceneManagerActorTree* Scene::GetRenderSceneManager() const
{
    return pSceneManager.get();
}

void Scene::AddSceneController( const std::wstring& name, SceneController* controller )
{
    VL_CHECK( controller );
//    controller->pSceneCamera = GetRenderCamera();
    mSceneControllers[name] = controller;
    if ( pViewWindow )
        pViewWindow->AddEventListener( controller );
    // вначале добавл€ем в ивентЋистнеры, потом уже каллбек на добавлении к сцене
    controller->onSceneEnter( this );
}

void Scene::RemoveSceneController( const std::wstring& name )
{
    auto f = mSceneControllers.find( name );
    if ( f != mSceneControllers.end() )
    {
        auto& controller = f->second;
        controller->onSceneLeave( this );
        // в обратном пор€дке: вначале каллбеки - потом удал€ем листнер
        if ( pViewWindow )
        {
            pViewWindow->RemoveEventListener( controller.get() );
        }
        mSceneControllers.erase( f );
    }
}

void Scene::onAddToViewWindow( ViewWindow* vw )
{
    VL_CHECK( vw );
    VL_CHECK( !pViewWindow );
    pViewWindow = vw;
    for ( auto& s : mSceneControllers )
    {
        SceneController* controller = s.second.get();
        pViewWindow->AddEventListener( controller );
    }
}

void Scene::onRemoveFromViewWindow( ViewWindow* vw )
{
    VL_CHECK( vw );
    VL_CHECK( pViewWindow );
    for ( auto& s : mSceneControllers )
    {
        SceneController* controller = s.second.get();
        vw->RemoveEventListener( controller );
    }
    pViewWindow = nullptr;
}
}