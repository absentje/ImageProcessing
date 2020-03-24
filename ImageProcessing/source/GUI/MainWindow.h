#pragma once
#include <QWidget>
#include <AppLogic/VLExtension/ViewWindow.h>

class QHBoxLayout;
class QVBoxLayout;
class ImageProcessingMode;
class ImageProcessingModeWidget;

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
    vl::ref<VLExtension::ViewWindow>         pViewWindow;
    vl::ref<ImageProcessingMode>    imageProcessing_;

	vlQt5::Qt5Widget*   pCanvas;
    
    QHBoxLayout*        pMainLayout;
    QVBoxLayout*        pSubLayout;
    ImageProcessingModeWidget* imageProcessingModeWidget_;

protected:
	virtual void closeEvent(QCloseEvent *event) override;
};