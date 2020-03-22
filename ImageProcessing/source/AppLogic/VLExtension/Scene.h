#pragma once
#include <vlCore/Object.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>

#include <set>
#include <unordered_map>
#include <string>

class Actor;
class SceneController;
class ViewWindow;

/*
	базовый/интерфейсный класс сцены
*/
class Scene : public vl::Object
{
    VL_INSTRUMENT_CLASS(Scene, vl::Object)
public:
	Scene(const std::wstring& scene_name);

	// ------------- common methods -------------------
	const std::wstring&		GetName() const;
	// добавл€ет узијктор в рендер—ценћанагер (дл€ удобства)
    void			AddRenderActor(Actor* actor);
    void			RemoveRenderActor(Actor* actor);

	vl::SceneManagerActorTree*			GetRenderSceneManager();
	const vl::SceneManagerActorTree*	GetRenderSceneManager() const;
	vl::Camera*					GetRenderCamera();
	const vl::Camera*			GetRenderCamera() const;

    void AddSceneController(const std::wstring& name, SceneController* controller);
    void RemoveSceneController(const std::wstring& name);

protected:
    virtual void onAddToViewWindow(ViewWindow* vw);
    virtual void onRemoveFromViewWindow(ViewWindow* vw);

private:
    ViewWindow*	pViewWindow;
    friend class ViewWindow;

    std::wstring                        scene_name_;
    vl::ref<vl::SceneManagerActorTree>	pSceneManager;
    vl::ref<vl::Camera>                 pCamera;

    std::unordered_map<std::wstring, vl::ref<SceneController>>	mSceneControllers;
};