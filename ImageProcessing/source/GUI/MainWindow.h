#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "ViewWindow.h"
#include "AppLogic/ImageProcessing.h"

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QSlider;
class QPushButton;
class QGroupBox;
class QRadioButton;
//class ImageProcessing;


namespace vlQt5
{
    class Qt5Widget;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    vl::ref<ViewWindow>         pViewWindow;
    vl::ref<ImageProcessing>    pImageProcessing;

	vlQt5::Qt5Widget*   pCanvas;
    
    QHBoxLayout*        pMainLayout;
    QVBoxLayout*        pSubLayout;
    QLabel*             pBrightnessLabel;
    QSlider*            pBrightnessSlider;
    QLabel*             pContrastLabel;
    QSlider*            pContrastSlider;
    QPushButton*        pProcessButton;
    QPushButton*        pSaveImageButton;

    QGroupBox*          pProcessTypeBox;
    QVBoxLayout*        pProcessTypeLayout;
    QRadioButton*       pCPUButton;
    QRadioButton*       pCPUParallelButton;
    QRadioButton*       pGPUButton;

protected:
	virtual void closeEvent(QCloseEvent *event) override;

private slots:
    void BrightnessChanged(int value);
    void ContrastChanged(int value);
    void ProcessImage();
    void ProcessTypeChanged();
    void SaveImage();
};

#endif // MAINWINDOW_H
