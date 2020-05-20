#include "Editor3DModeWidget.h"
#include <AppLogic/AppModes/Editor3DMode.h>
#include <AppLogic/SelectTools/Selectable.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>

Editor3DModeWidget::Editor3DModeWidget( QWidget* parent,
                                        Editor3DMode* editor3DMode )
	: QWidget( parent ), editor3DMode_( editor3DMode )
{

    subLayout_ = new QVBoxLayout( this );
    setLayout( subLayout_ );

//    subLayout_->addWidget( imageProcessingMode_->imageEffectList_->CreateWidget( this ), 1 );
    subLayout_->addStretch( 5 );
}