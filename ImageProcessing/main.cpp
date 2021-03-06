#include "GUI/MainWindow.h"
#include <QApplication>
#include <vlCore/VisualizationLibrary.hpp>
#include <vlCore/Log.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
	vl::VisualizationLibrary::init();
	QApplication a(argc, argv);
	int qapp_result;
	MainWindow* w = new MainWindow;
	w->show();
	w->resize(800, 600);
	qapp_result = a.exec();
	vl::VisualizationLibrary::shutdown();
	return qapp_result;
}
