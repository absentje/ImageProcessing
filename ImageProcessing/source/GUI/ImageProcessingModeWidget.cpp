#include "ImageProcessingModeWidget.h"
#include <AppLogic/AppModes/ImageProcessingMode.h>
#include <AppLogic/SelectTools/Selectable.h>
#include <AppLogic/ImageProcessing/ImageEffectList.h>

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

    saveImageButton_ = new QPushButton( "SaveImage", this );
    connect( saveImageButton_, &QPushButton::clicked,
             this, [this] { imageProcessingMode_->SaveImage(); } );

    subLayout_->addWidget( imageProcessingMode_->imageEffectList_->CreateWidget( this ), 1 );
    subLayout_->addStretch( 5 );
    subLayout_->addWidget( saveImageButton_ );

}

ImageProcessingModeWidget::~ImageProcessingModeWidget()
{
}