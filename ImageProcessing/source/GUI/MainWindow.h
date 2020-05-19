#pragma once
#include <QWidget>
#include <VLExtension/ViewWindow.h>

class QHBoxLayout;
class QVBoxLayout;
class AppModeList;

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
    vl::ref<VLExtension::ViewWindow>    pViewWindow;
    vl::ref<AppModeList>                appModeList_;

	vlQt5::Qt5Widget*   pCanvas;
    
    QHBoxLayout*        pMainLayout;
    QVBoxLayout*        pSubLayout;
protected:
	virtual void closeEvent(QCloseEvent *event) override;
};