#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include <string>
#include <vlCore/Object.hpp>
#include <vlCore/Vector4.hpp>

class Scene;
class TextureViewActor;
class EffectPipeline;
class BrightnessContrastEffect;

namespace vl
{
    class UIEventListener;
    class Image;
    class OpenGLContext;
    class Texture;
}

enum class EImageProcessingType : unsigned char
{
    IPT_CPU,
    IPT_PARALLEL_CPU,
    IPT_GPU
};

class ImageProcessing : public vl::Object
{
    VL_INSTRUMENT_CLASS(ImageProcessing, vl::Object)
public:
    ImageProcessing();

    Scene* GetScene();

    void LoadImage(const std::wstring& file_path);
    void SetBrightness(float value);
    void SetContrast(float value);
    void SetImageProcessingType(EImageProcessingType etype);
    void ProcessImage();
    void SaveOutputImage();
    void ShowOutputImage();


private:
    void    InitPipeline(vl::OpenGLContext* context);
    void    ProcessOutputImage(int i, int w);
    void    ProcessColor(vl::ubvec3& color);
    void    toYUV(vl::vec3& RGB);
    void    toRGB(vl::vec3& YUV);
    vl::ref<vl::Image> textureToImage(vl::Texture* inTexture);

private:
    vl::ref<Scene>              pScene;
    vl::ref<vl::Image>          pSourceImage;
    vl::ref<vl::Image>          pOutputImage;
    vl::ref<TextureViewActor>   pActor;

    vl::ref<EffectPipeline>             pPipeline;
    vl::ref<BrightnessContrastEffect>   pEffect;

    float fBrightness;
    float fContrast;
    EImageProcessingType eIPType;

    vl::OpenGLContext* pContext;

    friend class ImageProcessingController;
};

#endif // IMAGEPROCESSING_H
