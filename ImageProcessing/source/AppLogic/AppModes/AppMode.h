#pragma once
#include <vlCore/Object.hpp>
#include <AppLogic/SelectTools/Selectable.h>

namespace VLExtension
{
class ViewWindow;
}

namespace vl
{
class SceneManagerActorTree;
class UIEventListener;
}

class AppMode : public Selectable
{
	VL_INSTRUMENT_CLASS( AppMode, Selectable );
public:
	AppMode( const std::wstring& name );
	virtual void Enable() override;
	virtual void Disable() override;

protected:
	vl::ref<vl::SceneManagerActorTree>  pScene;
	vl::ref<vl::UIEventListener>        pUIEventListener;
};