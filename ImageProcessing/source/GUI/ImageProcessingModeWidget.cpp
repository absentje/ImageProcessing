#include "ImageProcessingModeWidget.h"
#include <AppLogic/AppModes/ImageProcessingMode.h>
#include <AppLogic/ImageProcessing/ImageEffect.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>

ImageProcessingModeWidget::ImageProcessingModeWidget( QWidget* parent,
                                                      ImageProcessingMode* imageProcessingMode )
	: QWidget( parent ),
	imageProcessingMode_( imageProcessingMode )
{

    subLayout_ = new QVBoxLayout( this );
    setLayout( subLayout_ );

    processButton_ = new QPushButton( "ProcessImage", this );
    connect( processButton_, SIGNAL( clicked() ),
             this, SLOT( ProcessImage() ) );
    saveImageButton_ = new QPushButton( "SaveImage", this );
    connect( saveImageButton_, SIGNAL( clicked() ),
             this, SLOT( SaveImage() ) );

    applyChange_ = new QPushButton( "ApplyChange", this );
    connect( applyChange_, SIGNAL( clicked() ),
             this, SLOT( ApplyChange() ) );
    discardChange_ = new QPushButton( "DiscardChange", this );
    connect( discardChange_, SIGNAL( clicked() ),
             this, SLOT( DiscardChange() ) );

    subLayout_->addWidget( imageProcessingMode_->currentImageEffect_->CreateWidget( this ), 1 );
    subLayout_->addStretch( 5 );
    subLayout_->addWidget( processButton_ );
    subLayout_->addWidget( saveImageButton_ );
    subLayout_->addWidget( applyChange_ );
    subLayout_->addWidget( discardChange_ );

}

ImageProcessingModeWidget::~ImageProcessingModeWidget()
{
}

void ImageProcessingModeWidget::ProcessImage()
{
    if ( imageProcessingMode_ )
    {
        imageProcessingMode_->ProcessImage();
        imageProcessingMode_->ShowOutputImage();
    }
}

void ImageProcessingModeWidget::SaveImage()
{
    if ( imageProcessingMode_ )
    {
        imageProcessingMode_->SaveOutputImage();
    }
}

void ImageProcessingModeWidget::ApplyChange()
{
    if ( imageProcessingMode_ )
    {
        imageProcessingMode_->ApplyChange();
    }
}

void ImageProcessingModeWidget::DiscardChange()
{
    if ( imageProcessingMode_ )
    {
        imageProcessingMode_->DiscardChange();
    }
}