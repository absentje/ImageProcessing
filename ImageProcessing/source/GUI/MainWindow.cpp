#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vlQt5/Qt5Widget.hpp>
#include <AppLogic/VLExtension/FBORender.h>
#include <AppLogic/AppModes/AppModeList.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // qt gui init
    pCanvas = new vlQt5::Qt5Widget( this );
    pCanvas->initGLContext();
    pCanvas->show();
    pCanvas->setPosition( 0, 0 );
    pCanvas->setFocusPolicy( Qt::FocusPolicy::StrongFocus );

    VLExtension::FBORender::gl_context = pCanvas;

    pMainLayout = new QHBoxLayout( this );
    pMainLayout->addWidget( pCanvas, 5 );
    pMainLayout->addSpacing( 2 );
    pSubLayout = new QVBoxLayout( this );
    pMainLayout->addLayout( pSubLayout, 1 );
    setLayout( pMainLayout );

    // app logic init
    pViewWindow = new VLExtension::ViewWindow( pCanvas );
    VLExtension::ViewWindow::currentViewWindow = pViewWindow.get();

    appModeList_ = new AppModeList;
    pSubLayout->addWidget( appModeList_->CreateWidget( this ) );
    pSubLayout->addStretch( 0 );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	__super::closeEvent(event);
	pViewWindow = nullptr;
}