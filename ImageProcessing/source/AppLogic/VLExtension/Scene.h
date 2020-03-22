#pragma once
#include <vlCore/Object.hpp>

#include <unordered_map>
#include <string>

namespace vl
{
class SceneManagerActorTree;
}

namespace VLExtension
{
class Actor;
class SceneController;
class ViewWindow;

/*
    �������/������������ ����� �����
*/
class Scene: public vl::Object
{
    VL_INSTRUMENT_CLASS( Scene, vl::Object )
public:
    Scene( const std::wstring& scene_name );

    // ------------- common methods -------------------
    const std::wstring& GetName() const;
    // ��������� �������� � ����������������� (��� ��������)
    void			AddRenderActor( Actor* actor );
    void			RemoveRenderActor( Actor* actor );

    vl::SceneManagerActorTree* GetRenderSceneManager();
    const vl::SceneManagerActorTree* GetRenderSceneManager() const;

    void AddSceneController( const std::wstring& name, SceneController* controller );
    void RemoveSceneController( const std::wstring& name );

protected:
    virtual void onAddToViewWindow( ViewWindow* vw );
    virtual void onRemoveFromViewWindow( ViewWindow* vw );

private:
    ViewWindow* pViewWindow;
    friend class ViewWindow;

    std::wstring                        scene_name_;
    vl::ref<vl::SceneManagerActorTree>	pSceneManager;

    std::unordered_map<std::wstring, vl::ref<SceneController>>	mSceneControllers;
};
}