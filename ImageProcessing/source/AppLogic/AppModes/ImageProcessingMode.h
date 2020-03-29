#pragma once
#include <string>
#include <vlCore/Object.hpp>
#include <vlCore/Vector4.hpp>
#include <AppLogic/AppModes/AppMode.h>

class ImageEffect;

namespace VLExtension
{
class TextureViewActor;
class EffectPipeline;
class BrightnessContrastEffect;
}

namespace vl
{
    class UIEventListener;
    class Image;
    class OpenGLContext;
    class Texture;
    class SceneManagerActorTree;
}

class ImageProcessingMode: public AppMode
{
    VL_INSTRUMENT_CLASS( ImageProcessingMode, vl::Object)
public:
    ImageProcessingMode();

    void LoadImage(const std::wstring& file_path);
    void SaveOutputImage();
    void ShowOutputImage();
    void ProcessImage();

private:
    vl::ref<vl::Image>          pSourceImage;
    vl::ref<vl::Image>          pOutputImage;
    vl::ref<VLExtension::TextureViewActor>   pActor;
    vl::ref<ImageEffect> currentImageEffect_;

    vl::OpenGLContext* pContext;

    friend class ImageProcessingUIListener;
    friend class ImageEffect;
    friend class ImageProcessingModeWidget;

};