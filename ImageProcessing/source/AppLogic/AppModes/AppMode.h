#pragma once
#include <vlCore/Object.hpp>

namespace VLExtension
{
class ViewWindow;
}

namespace vl
{
class SceneManagerActorTree;
class UIEventListener;
}

class AppMode : public vl::Object
{
	VL_INSTRUMENT_CLASS(AppMode, vl::Object);
public:
	AppMode();
	void Enable( VLExtension::ViewWindow* viewWindow );

protected:
	vl::ref<vl::SceneManagerActorTree>  pScene;
	vl::ref<vl::UIEventListener>        pUIEventListener;
};