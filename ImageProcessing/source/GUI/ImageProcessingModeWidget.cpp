#include "ImageProcessingModeWidget.h"
#include <AppLogic/AppModes/ImageProcessingMode.h>
#include <AppLogic/SelectTools/Selectable.h>

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
    connect( processButton_, &QPushButton::clicked,
             this, [this] { imageProcessingMode_->ProcessImage(); } );


    saveImageButton_ = new QPushButton( "SaveImage", this );
    connect( saveImageButton_, &QPushButton::clicked,
             this, [this] { imageProcessingMode_->SaveImage(); } );

    applyChange_ = new QPushButton( "ApplyChange", this );
    connect( applyChange_, &QPushButton::clicked,
             this, [this] { imageProcessingMode_->ApplyChange(); } );

    discardChange_ = new QPushButton( "DiscardChange", this );
    connect( discardChange_, &QPushButton::clicked,
             this, [this] { imageProcessingMode_->DiscardChange(); } );

    subLayout_->addWidget( imageProcessingMode_->imageEffectList_->CreateWidget( this ), 1 );
    subLayout_->addStretch( 5 );
    subLayout_->addWidget( processButton_ );
    subLayout_->addWidget( saveImageButton_ );
    subLayout_->addWidget( applyChange_ );
    subLayout_->addWidget( discardChange_ );

}

ImageProcessingModeWidget::~ImageProcessingModeWidget()
{
}