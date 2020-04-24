#pragma once
#include <QWidget>

class ImageProcessingMode;

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QSlider;
class QPushButton;
class QGroupBox;
class QRadioButton;

class ImageProcessingModeWidget : public QWidget
{
	Q_OBJECT

public:
	ImageProcessingModeWidget( QWidget* parent,
                               ImageProcessingMode* imageProcessingMode );
	~ImageProcessingModeWidget();

private:
    ImageProcessingMode* imageProcessingMode_;

    QVBoxLayout* subLayout_;
    QPushButton* saveImageButton_;
};
