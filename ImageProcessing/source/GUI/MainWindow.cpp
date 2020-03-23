#include "MainWindow.h"
#include <vlCore/Matrix4.hpp>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <vlQt5/Qt5Widget.hpp>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>

#include <AppLogic/AppModes/ImageProcessing.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // qt gui init
    pCanvas = new vlQt5::Qt5Widget(this);
    pCanvas->initGLContext();
    pCanvas->show();
    pCanvas->setPosition(0, 0);

    pMainLayout = new QHBoxLayout(this);
    pMainLayout->addWidget(pCanvas, 5);
    pMainLayout->addSpacing(2);
    pSubLayout = new QVBoxLayout(this);
    pMainLayout->addLayout(pSubLayout, 1);

    setLayout(pMainLayout);

    pBrightnessLabel = new QLabel("Brightness", this);
    pBrightnessSlider = new QSlider(Qt::Orientation::Horizontal, this);
    pBrightnessSlider->setMinimum(-100);
    pBrightnessSlider->setMaximum(100);
    connect(pBrightnessSlider, SIGNAL(valueChanged(int)),
            this, SLOT(BrightnessChanged(int)));

    pContrastLabel = new QLabel("Contrast", this);
    pContrastSlider = new QSlider(Qt::Orientation::Horizontal, this);
    pContrastSlider->setMinimum(-100);
    pContrastSlider->setMaximum(100);

    connect(pContrastSlider, SIGNAL(valueChanged(int)),
            this, SLOT(ContrastChanged(int)));

    pProcessButton = new QPushButton("ProcessImage", this);
    connect(pProcessButton, SIGNAL(clicked()),
            this, SLOT(ProcessImage()));
    pSaveImageButton = new QPushButton("SaveImage", this);
    connect(pSaveImageButton, SIGNAL(clicked()),
            this, SLOT(SaveImage()));

    pProcessTypeBox = new QGroupBox("Image processing type", this);
    pProcessTypeLayout = new QVBoxLayout(pProcessTypeBox);
    pCPUButton = new QRadioButton("CPU", pProcessTypeBox);
    pCPUParallelButton = new QRadioButton("CPU parallel", pProcessTypeBox);
    pGPUButton = new QRadioButton("GPU", pProcessTypeBox);
    connect(pCPUButton, SIGNAL(clicked()),
            this, SLOT(ProcessTypeChanged()));
    connect(pCPUParallelButton, SIGNAL(clicked()),
            this, SLOT(ProcessTypeChanged()));
    connect(pGPUButton, SIGNAL(clicked()),
            this, SLOT(ProcessTypeChanged()));
    pCPUParallelButton->click();

    pProcessTypeLayout->addWidget(pCPUButton);
    pProcessTypeLayout->addWidget(pCPUParallelButton);
    pProcessTypeLayout->addWidget(pGPUButton);
    pProcessTypeBox->setLayout(pProcessTypeLayout);

    pSubLayout->addWidget(pBrightnessLabel, 1);
    pSubLayout->addWidget(pBrightnessSlider, 1);
    pSubLayout->addSpacing(5);
    pSubLayout->addWidget(pContrastLabel, 1);
    pSubLayout->addWidget(pContrastSlider, 1);
    pSubLayout->addWidget(pProcessTypeBox);
    pSubLayout->addStretch(5);
    pSubLayout->addWidget(pProcessButton);
    pSubLayout->addWidget(pSaveImageButton);

    // app logic init
    pViewWindow = new VLExtension::ViewWindow(pCanvas);
    pImageProcessing = new ImageProcessing;
    pImageProcessing->Enable( pViewWindow.get() );
}

void MainWindow::BrightnessChanged(int value)
{
    if (pImageProcessing)
        pImageProcessing->SetBrightness(value);
}

void MainWindow::ContrastChanged(int value)
{
    if (pImageProcessing)
        pImageProcessing->SetContrast(value);
}

void MainWindow::ProcessImage()
{
    if (pImageProcessing)
    {
        pImageProcessing->ProcessImage();
        pImageProcessing->ShowOutputImage();
    }

}

void MainWindow::SaveImage()
{
    if (pImageProcessing)
    {
        pImageProcessing->SaveOutputImage();
    }

}

void MainWindow::ProcessTypeChanged()
{
    if (pImageProcessing)
    {
        EImageProcessingType type;
        if (pCPUButton->isChecked()) type = EImageProcessingType::IPT_CPU;
        if (pCPUParallelButton->isChecked()) type = EImageProcessingType::IPT_PARALLEL_CPU;
        if (pGPUButton->isChecked()) type = EImageProcessingType::IPT_GPU;

        pImageProcessing->SetImageProcessingType(type);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	__super::closeEvent(event);
	pViewWindow = nullptr;
	pImageProcessing = nullptr;

//	pCanvas;
}