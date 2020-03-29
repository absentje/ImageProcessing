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
    
    //pBrightnessLabel = new QLabel( "Brightness", this );
    //pBrightnessSlider = new QSlider( Qt::Orientation::Horizontal, this );
    //pBrightnessSlider->setMinimum( -100 );
    //pBrightnessSlider->setMaximum( 100 );
    //connect( pBrightnessSlider, SIGNAL( valueChanged( int ) ),
    //         this, SLOT( BrightnessChanged( int ) ) );

    //pContrastLabel = new QLabel( "Contrast", this );
    //pContrastSlider = new QSlider( Qt::Orientation::Horizontal, this );
    //pContrastSlider->setMinimum( -100 );
    //pContrastSlider->setMaximum( 100 );

    //connect( pContrastSlider, SIGNAL( valueChanged( int ) ),
    //         this, SLOT( ContrastChanged( int ) ) );

    pProcessButton = new QPushButton( "ProcessImage", this );
    connect( pProcessButton, SIGNAL( clicked() ),
             this, SLOT( ProcessImage() ) );
    pSaveImageButton = new QPushButton( "SaveImage", this );
    connect( pSaveImageButton, SIGNAL( clicked() ),
             this, SLOT( SaveImage() ) );

    //pSubLayout->addWidget( pBrightnessLabel, 1 );
    //pSubLayout->addWidget( pBrightnessSlider, 1 );
    //pSubLayout->addSpacing( 5 );
    //pSubLayout->addWidget( pContrastLabel, 1 );
    //pSubLayout->addWidget( pContrastSlider, 1 );
    //pSubLayout->addStretch( 5 );
    pSubLayout->addWidget( imageProcessingMode_->currentImageEffect_->CreateWidget( this ) );

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
