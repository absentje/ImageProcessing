#pragma once
#include <QWidget>

class Editor3DMode;

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QSlider;
class QPushButton;
class QGroupBox;
class QRadioButton;

class Editor3DModeWidget : public QWidget
{
	Q_OBJECT

public:
    Editor3DModeWidget( QWidget* parent,
                        Editor3DMode* editor3DMode );
private:
    Editor3DMode* editor3DMode_;
    QVBoxLayout* subLayout_;
};
