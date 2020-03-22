#pragma once

#include <vlCore/vlnamespace.hpp>
#include <vlGraphics/UIEventListener.hpp>

class Scene;

class SceneController : public vl::UIEventListener
{
    VL_INSTRUMENT_CLASS(SceneController, vl::UIEventListener)
public:
	virtual void onSceneEnter(Scene* scene) {}
	virtual void onSceneLeave(Scene* scene) {}

	// vl::UIEventListener overriding
    virtual void initEvent() override {}
    virtual void destroyEvent() override {}
    virtual void updateEvent() override {}
    virtual void enableEvent(bool enable) override {}
    virtual void addedListenerEvent(vl::OpenGLContext* openglContext) override {}
    virtual void removedListenerEvent(vl::OpenGLContext* openglContext) override {}
    virtual void mouseMoveEvent(int x, int y) override {}
    virtual void mouseUpEvent(vl::EMouseButton but, int x, int y) override {}
    virtual void mouseDownEvent(vl::EMouseButton but, int x, int y) override {}
    virtual void mouseWheelEvent(int delta) override {}
    virtual void keyPressEvent(unsigned short unicode, vl::EKey key) override {}
    virtual void keyReleaseEvent(unsigned short unicode, vl::EKey key) override {}
    virtual void resizeEvent(int x, int y) override {}
    virtual void fileDroppedEvent(const std::vector<vl::String>& files) override {}
    virtual void visibilityEvent(bool visible) override {}

private:
	friend class Scene;
};