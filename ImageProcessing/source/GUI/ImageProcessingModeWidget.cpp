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
                                                      ImageEffectList* imageEffectList )
	: QWidget( parent )
{
    subLayout_ = new QVBoxLayout( this );
    setLayout( subLayout_ );
    saveImageButton_ = new QPushButton( "SaveImage", this );
}

void ImageProcessingModeWidget::SetImageEffectListWidget( QWidget* widget )
{
    subLayout_->addWidget( widget, 1 );
    subLayout_->addStretch( 5 );
    subLayout_->addWidget( saveImageButton_ );
}


void ImageProcessingModeWidget::SetSaveImageCallback( std::function<void()> callback )
{
    connect( saveImageButton_, &QPushButton::clicked, this, callback );
}