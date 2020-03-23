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

class WidgetNode;

class AppMode : public vl::Object
{
	VL_INSTRUMENT_CLASS(AppMode, vl::Object);
public:
	AppMode();

	void Enable( VLExtension::ViewWindow* viewWindow/*, WidgetNode* widgetNode*/ );

protected:
	virtual void enable_( WidgetNode* widgetNode ) {};

	vl::ref<vl::SceneManagerActorTree>  pScene;
	vl::ref<vl::UIEventListener>        pUIEventListener;
};