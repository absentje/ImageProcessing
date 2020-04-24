#include "ImageProcessingMode.h"
#include <vlCore/Image.hpp>
#include <Actors/TextureRatioViewActor.h>
#include <vector>
#include <FBORender.h>
#include <EffectPipeline.h>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/UIEventListener.hpp>

#include <AppLogic/ImageProcessing/ImageEffectList.h>
#include <AppLogic/VLExtension/Util/TextureReader.h>
#include <GUI/ImageProcessingModeWidget.h>

class ImageProcessingUIListener: public vl::UIEventListener
{
    VL_INSTRUMENT_CLASS( ImageProcessingUIListener, vl::UIEventListener );
public:
    ImageProcessingUIListener( ImageProcessingMode* ptr )
        : pImageProcessing( ptr ) {}

    virtual void initEvent() override {}
    virtual void destroyEvent() override {}
    virtual void updateEvent() override
    {
        pImageProcessing->RenderImage();
    }
    virtual void enableEvent( bool enable ) override {}
    virtual void removedListenerEvent( vl::OpenGLContext* openglContext ) override {}
    virtual void mouseMoveEvent( int x, int y ) override {}
    virtual void mouseUpEvent( vl::EMouseButton but, int x, int y ) override {}
    virtual void mouseDownEvent( vl::EMouseButton but, int x, int y ) override {}
    virtual void mouseWheelEvent( int delta ) override {}
    virtual void keyPressEvent( unsigned short unicode, vl::EKey key ) override
    {
        switch ( key )
        {
        case vl::EKey::Key_U :
        {
            pImageProcessing->imageEffectList_->GetImageEffectsPipeline()->ReloadEffectShaders();
            break;
        }
        }
    }
    virtual void keyReleaseEvent( unsigned short unicode, vl::EKey key ) override {}
    virtual void resizeEvent( int x, int y ) override {}
    virtual void visibilityEvent( bool visible ) override {}


    virtual void fileDroppedEvent( const std::vector<vl::String>& files ) override
    {
        if ( !pImageProcessing || files.empty() ) return;
        pImageProcessing->LoadImage( files[0].toStdWString() );
    }

    virtual void addedListenerEvent( vl::OpenGLContext* openglContext ) override {}
private:
    ImageProcessingMode* pImageProcessing;
};

ImageProcessingMode::ImageProcessingMode()
    : super( L"Image processing mode" )
{
    scene_->setCullingEnabled( false );
    viewActor_ = new VLExtension::TextureRatioViewActor;
    scene_->tree()->addActor( viewActor_.get() );

    UIEventListeners_.push_back( new ImageProcessingUIListener( this ) );
    imageEffectList_ = new ImageEffectList;
}

void ImageProcessingMode::LoadImage( const std::wstring& file_path )
{
    sourceImage_ = vl::loadImage( file_path );
    imageFilePath_ = file_path;
    auto pipe = imageEffectList_->GetImageEffectsPipeline();
    pipe->SetInputTexture( vl::ref<vl::Texture>( new vl::Texture( sourceImage_.get() ) ).get() );
}

void ImageProcessingMode::SaveImage()
{
    if ( !sourceImage_ )
    {
        return;
    }
    std::wstring fileName = imageFilePath_.extractFileName().toStdWString();
    std::wstring fileType = imageFilePath_.extractFileExtension().toStdWString();
    auto iter = fileName.find(L'.');
    fileName.erase(iter);

    std::wstring newFilePath = L"resources/images/" + fileName + L"_обработано." + fileType;

    auto pipe = imageEffectList_->GetImageEffectsPipeline();
    TextureReader::saveTexture( imageEffectList_->GetImageEffectsPipeline()->GetLastOutTexture(), newFilePath );
}

void ImageProcessingMode::RenderImage()
{
    auto pipe = imageEffectList_->GetImageEffectsPipeline();
    viewActor_->SetTexture( pipe->RenderOutTexture() );
}

QWidget* ImageProcessingMode::CreateWidget( QWidget* parent )
{
    return new ImageProcessingModeWidget( parent, this );
}