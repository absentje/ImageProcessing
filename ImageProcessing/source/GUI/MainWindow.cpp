#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vlQt5/Qt5Widget.hpp>
#include <AppLogic/VLExtension/FBORender.h>

#include <AppLogic/AppModes/ImageProcessingMode.h>
#include "ImageProcessingModeWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // qt gui init
    pCanvas = new vlQt5::Qt5Widget(this);
    pCanvas->initGLContext();
    pCanvas->show();
    pCanvas->setPosition(0, 0);
    VLExtension::FBORender::gl_context = pCanvas;

    pMainLayout = new QHBoxLayout( this );
    pMainLayout->addWidget(pCanvas, 5);
    pMainLayout->addSpacing(2);
    pSubLayout = new QVBoxLayout( this );
    pMainLayout->addLayout(pSubLayout, 1);
    setLayout(pMainLayout);

    // app logic init
    pViewWindow = new VLExtension::ViewWindow(pCanvas);
    imageProcessing_ = new ImageProcessingMode;
    imageProcessing_->Enable( pViewWindow.get() );

    imageProcessingModeWidget_ = new ImageProcessingModeWidget( this, imageProcessing_.get() );
    pSubLayout->addWidget( imageProcessingModeWidget_ );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	__super::closeEvent(event);
	pViewWindow = nullptr;
    imageProcessing_ = nullptr;

//	pCanvas;
}