#pragma once
#include <string>
#include <vlCore/Object.hpp>
#include <vlCore/Vector4.hpp>
#include <AppLogic/AppModes/AppMode.h>
#include <vlCore/String.hpp>

class Selectable;

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
    
    void DiscardChange();
    void ApplyChange();
    void ProcessImage();
    void SaveImage();

private:
    void ShowOutputImage_();

    vl::ref<vl::Image>          pSourceImage;
    vl::ref<vl::Image>          pOutputImage;
    vl::String                  imageFilePath_;
    vl::ref<VLExtension::TextureViewActor>   pActor;
    vl::ref<Selectable> imageEffectList_;

    friend class ImageProcessingUIListener;
    friend class ImageEffect;
    friend class ImageProcessingModeWidget;

    vl::ref<VLExtension::EffectPipeline> pipeline_;

};