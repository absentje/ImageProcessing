#pragma once
#include <string>
#include <vlCore/Vector4.hpp>
#include <AppLogic/AppModes/AppMode.h>
#include <vlCore/String.hpp>

class ImageEffectList;

namespace VLExtension
{
class TextureViewActor;
}

namespace vl
{
    class Image;
}

class ImageProcessingMode: public AppMode
{
    VL_INSTRUMENT_CLASS( ImageProcessingMode, AppMode )
public:
    ImageProcessingMode();

    void LoadImage(const std::wstring& file_path);
    
    void DiscardChange();
    void ApplyChange();
    void ProcessImage();
    void SaveImage();

    virtual QWidget* CreateWidget( QWidget* parent ) override;

private:
    void ShowOutputImage_();

    vl::ref<vl::Image>          sourceImage_;
    vl::ref<vl::Image>          outputImage_;
    vl::String                  imageFilePath_;
    vl::ref<VLExtension::TextureViewActor>   viewActor_;
    vl::ref<ImageEffectList> imageEffectList_;

    friend class ImageProcessingUIListener;
    friend class ImageProcessingModeWidget;
};