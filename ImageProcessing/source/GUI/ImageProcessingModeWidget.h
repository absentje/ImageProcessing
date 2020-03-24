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

    QVBoxLayout* pSubLayout;
    QLabel* pBrightnessLabel;
    QSlider* pBrightnessSlider;
    QLabel* pContrastLabel;
    QSlider* pContrastSlider;
    QPushButton* pProcessButton;
    QPushButton* pSaveImageButton;

    QGroupBox* pProcessTypeBox;
    QVBoxLayout* pProcessTypeLayout;
    QRadioButton* pCPUButton;
    QRadioButton* pCPUParallelButton;
    QRadioButton* pGPUButton;

private slots:
    void BrightnessChanged( int value );
    void ContrastChanged( int value );
    void ProcessImage();
    void ProcessTypeChanged();
    void SaveImage();
};
