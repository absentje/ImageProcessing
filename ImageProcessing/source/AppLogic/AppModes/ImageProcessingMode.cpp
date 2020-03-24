#include "ImageProcessingMode.h"
#include <vlCore/Image.hpp>
#include <Actors/TextureRatioViewActor.h>
#include <thread>
#include <vector>
#include <FBORender.h>
#include <EffectPipeline.h>
#include <Effects/BrightnessContrastEffect.h>
#include "AppLogic/Util/Timer.h"
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/UIEventListener.hpp>
#include <QMessageBox>

static QMessageBox* msMessage = nullptr;

class ImageProcessingUIListener: public vl::UIEventListener
{
    VL_INSTRUMENT_CLASS( ImageProcessingController, vl::UIEventListener );
public:
    ImageProcessingUIListener( ImageProcessingMode* ptr )
        : pImageProcessing( ptr ) {}

    virtual void initEvent() override {}
    virtual void destroyEvent() override {}
    virtual void updateEvent() override {}
    virtual void enableEvent( bool enable ) override {}
    virtual void removedListenerEvent( vl::OpenGLContext* openglContext ) override {}
    virtual void mouseMoveEvent( int x, int y ) override {}
    virtual void mouseUpEvent( vl::EMouseButton but, int x, int y ) override {}
    virtual void mouseDownEvent( vl::EMouseButton but, int x, int y ) override {}
    virtual void mouseWheelEvent( int delta ) override {}
    virtual void keyPressEvent( unsigned short unicode, vl::EKey key ) override {}
    virtual void keyReleaseEvent( unsigned short unicode, vl::EKey key ) override {}
    virtual void resizeEvent( int x, int y ) override {}
    virtual void visibilityEvent( bool visible ) override {}


    virtual void fileDroppedEvent( const std::vector<vl::String>& files ) override
    {
        if ( !pImageProcessing || files.empty() ) return;
        pImageProcessing->LoadImage( files[0].toStdWString() );
    }

    virtual void addedListenerEvent( vl::OpenGLContext* openglContext ) override
    {
        if ( pImageProcessing )
        {
            pImageProcessing->pContext = openglContext;
            pImageProcessing->InitPipeline( openglContext );
        }
    }
private:
    ImageProcessingMode* pImageProcessing;
};

ImageProcessingMode::ImageProcessingMode()
    :fBrightness(0.f), fContrast(0.f)
{
    pScene->setCullingEnabled(false);
    pActor = new VLExtension::TextureRatioViewActor;
    pScene->tree()->addActor( pActor.get() );

    pUIEventListener = new ImageProcessingUIListener( this );

    SetImageProcessingType(EImageProcessingType::IPT_PARALLEL_CPU);
}

void ImageProcessingMode::SetImageProcessingType(EImageProcessingType etype)
{
    eIPType = etype;
}

void ImageProcessingMode::LoadImage(const std::wstring& file_path)
{
    pSourceImage = new vl::Image(file_path);
    ProcessImage();
    ShowOutputImage();
}

void ImageProcessingMode::SaveOutputImage()
{
    if ( !pOutputImage )
    {
        return;
    }
    std::wstring fileName = pSourceImage->filePath().extractFileName().toStdWString();
    std::wstring fileType = pSourceImage->filePath().extractFileExtension().toStdWString();
    auto iter = fileName.find(L'.');
    fileName.erase(iter);

    std::wstring newFilePath = L"resources/images/" + fileName + L"_обработано." + fileType;
    vl::saveImage(pOutputImage.get(), newFilePath);
}

void ImageProcessingMode::SetBrightness(float value)
{
    fBrightness = value;
}

void ImageProcessingMode::SetContrast(float value)
{
    fContrast = value;
}

void ImageProcessingMode::ProcessImage()
{
    static const int THREAD_COUNT = 4;
    std::vector<std::thread> threads;
    if ( !msMessage )
    {
        msMessage = new QMessageBox;
    }
    msMessage->show();

    Timer timer;
    timer.Start();
    switch(eIPType)
    {
    case EImageProcessingType::IPT_CPU:
    {
        pOutputImage = new vl::Image(*pSourceImage);
        ProcessOutputImage(1, 1);
        msMessage->setText(QString(std::to_string(timer.GetElapsedSeconds() * 1000.f).c_str()) + " ms.");
    }

    break;
    case EImageProcessingType::IPT_PARALLEL_CPU:
    {
        pOutputImage = new vl::Image(*pSourceImage);
        for (int i = 0; i != THREAD_COUNT; ++i)
        {
            threads.emplace_back([this, i]{ ProcessOutputImage(i, THREAD_COUNT); });
        }
        for (int i = 0; i != THREAD_COUNT; ++i)
        {
            threads.rbegin()->join();
            threads.pop_back();
        }
    }
    break;

    case EImageProcessingType::IPT_GPU:
    {
        if (!pPipeline) break;
        pPipeline->Resize(pSourceImage->width(), pSourceImage->height());
        pOutputImage = new vl::Image(*pSourceImage);
        pPipeline->SetInputTexture(vl::ref<vl::Texture>(new vl::Texture(pOutputImage.get())).get());
        if (pEffect)
        {
            pEffect->SetBrightness(fBrightness);
            pEffect->SetContrast(fContrast);
        }
        vl::Texture* outTexture = pPipeline->RenderOutTexture();
        pOutputImage = textureToImage(outTexture);
    }
    break;
    default :
        break;
    }
    msMessage->setText("ProcessingTime: " + QString(std::to_string(timer.GetElapsedSeconds() * 1000.f).c_str()) + " ms.");
}

void ImageProcessingMode::ShowOutputImage()
{
    if ( !pOutputImage )
    {
        return;
    }
    pActor->SetTexture( vl::ref<vl::Texture>( new vl::Texture( pOutputImage.get() ) ).get() );
}

void ImageProcessingMode::ProcessOutputImage(int i, int w)
{
    if ( !pOutputImage )
    {
        return;
    }
    unsigned char* pixels = pOutputImage->pixels();
    int bytesPerPixel = pOutputImage->bitsPerPixel() / 8;
    int pixelCount = pOutputImage->width() * pOutputImage->height();
    int j = i;
    while ( j < pixelCount )
    {
        ProcessColor( *reinterpret_cast<vl::ubvec3*>( pixels + bytesPerPixel * j ) );
        j += w;
    }
}

void    ImageProcessingMode::ProcessColor(vl::ubvec3& color)
{
    using UByte = unsigned char;
    vl::vec3 norm_color = vl::vec3(color.x() / 255.f, color.y() / 255.f, color.z() / 255.f);

    //  fContrast
    float factor = 259.f / 255.f * (fContrast + 255.f)  / (259.f - fContrast);
    norm_color = factor * (norm_color - vl::vec3(0.5f)) + vl::vec3(0.5f);


    toYUV(norm_color);
    // correct YUV
    float& Y = norm_color.x();
//    float& U = norm_color.y();
//    float& V = norm_color.z();

    static const float BaseY = 0.5f;

    //  fBrightness
    Y = vl::clamp(Y + fBrightness / 100.f, 0.f, 1.f);


    toRGB(norm_color);

    // fLightning
//    norm_color = norm_color + vl::vec3(fLightning / 100.f);

    color.x() = static_cast<UByte>(vl::clamp(norm_color.x() * 255.f, 0.f, 255.f));
    color.y() = static_cast<UByte>(vl::clamp(norm_color.y() * 255.f, 0.f, 255.f));
    color.z() = static_cast<UByte>(vl::clamp(norm_color.z() * 255.f, 0.f, 255.f));
}

void    ImageProcessingMode::toYUV(vl::vec3& RGB)
{
    static const vl::mat3 coeffs =
            vl::mat3(
                0.2126f, 0.7152f, 0.0722f,
                -0.0999f, -0.3360f, 0.4360f,
                0.6150f, -0.5586f, -0.0563f
                );

    RGB = coeffs * RGB;
}

void    ImageProcessingMode::toRGB(vl::vec3& YUV)
{
    static const vl::mat3 coeffs =
            vl::mat3(
                1.f,    0.f,        1.2803f,
                1.f,    -0.2148f,   -0.3805f,
                1.f,    2.1279f,     0.f
                );
    YUV = coeffs * YUV;
}

void    ImageProcessingMode::InitPipeline(vl::OpenGLContext* context)
{
    pPipeline = new VLExtension::EffectPipeline(context);
    pEffect = new VLExtension::BrightnessContrastEffect;
    pEffect->SetBrightness(fBrightness);
    pEffect->SetContrast(fContrast);
    pPipeline->AddEffect(pEffect.get());
}

vl::ref<vl::Image> ImageProcessingMode::textureToImage(vl::Texture* inTexture)
{
    vl::ref<vl::Image> resultValue = new vl::Image;
    vl::ref<VLExtension::Actor> pTextureViewActor = new VLExtension::TextureViewActor(inTexture);
    VLExtension::FBORender fbo(pContext);
    fbo.Resize(inTexture->width(), inTexture->height());
    fbo.AddActor(pTextureViewActor.get());
    fbo.Render(*resultValue);
    return resultValue;
}