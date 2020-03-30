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
#include <AppLogic/ImageProcessing/BrightnessContrastImageEffect.h>


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
        }
    }
private:
    ImageProcessingMode* pImageProcessing;
};

ImageProcessingMode::ImageProcessingMode()
{
    pScene->setCullingEnabled(false);
    pActor = new VLExtension::TextureRatioViewActor;
    pScene->tree()->addActor( pActor.get() );

    pUIEventListener = new ImageProcessingUIListener( this );
    currentImageEffect_ = new BrightnessContrastImageEffect();
    currentImageEffect_->SetImageProcessingMode( this );
}

void ImageProcessingMode::LoadImage(const std::wstring& file_path)
{
    pSourceImage = vl::loadImage( file_path );
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

void ImageProcessingMode::ProcessImage()
{
    currentImageEffect_->ApplyEffect();
}

void ImageProcessingMode::DiscardChange()
{
    pOutputImage = pSourceImage;
    ShowOutputImage();
}

void ImageProcessingMode::ApplyChange()
{
    if ( pOutputImage )
    {
        pSourceImage = pOutputImage;
    }
}

void ImageProcessingMode::ShowOutputImage()
{
    if ( !pOutputImage )
    {
        return;
    }
    vl::ref<vl::Texture> texture = new vl::Texture( pOutputImage.get() );
    pActor->SetTexture( texture.get() );
}