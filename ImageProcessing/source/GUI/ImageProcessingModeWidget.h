#pragma once
#include <QWidget>
#include <functional>

class ImageEffectList;

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
	ImageProcessingModeWidget( QWidget* parent, ImageEffectList* imageEffectList );
    void SetSaveImageCallback( std::function<void()> callback );
    void SetImageEffectListWidget( QWidget* widget );

private:
    QVBoxLayout* subLayout_;
    QPushButton* saveImageButton_;
};
