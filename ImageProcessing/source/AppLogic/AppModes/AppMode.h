#pragma once
#include <vlCore/Object.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/UIEventListener.hpp>
#include <AppLogic/SelectTools/Selectable.h>
#include <vector>


namespace VLExtension
{
class ViewWindow;
}

namespace vl
{
class SceneManagerActorTree;
class UIEventListener;
class Camera;
}

class AppMode : public Selectable
{
	VL_INSTRUMENT_CLASS( AppMode, Selectable );
public:
	AppMode( const std::wstring& name );
	virtual void Enable() override;
	virtual void Disable() override;

protected:
	vl::ref<vl::SceneManagerActorTree>			scene_;
	std::vector<vl::ref<vl::UIEventListener>>	UIEventListeners_;
	vl::ref<vl::Camera>							camera_;
};