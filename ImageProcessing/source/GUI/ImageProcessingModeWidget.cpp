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

    pSubLayout = new QVBoxLayout( this );
    setLayout( pSubLayout );

    pProcessButton = new QPushButton( "ProcessImage", this );
    connect( pProcessButton, SIGNAL( clicked() ),
             this, SLOT( ProcessImage() ) );
    pSaveImageButton = new QPushButton( "SaveImage", this );
    connect( pSaveImageButton, SIGNAL( clicked() ),
             this, SLOT( SaveImage() ) );

    pSubLayout->addWidget( imageProcessingMode_->currentImageEffect_->CreateWidget( this ), 1 );
    pSubLayout->addStretch( 5 );
    pSubLayout->addWidget( pProcessButton );
    pSubLayout->addWidget( pSaveImageButton );
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
