#pragma once
#include <functional>
#include <QSlider>

class Selectable;
class ParamsWidget;

class FloatParamWidget: public QSlider
{
	Q_OBJECT
public:
	FloatParamWidget( float& param, float min, float max, ParamsWidget* paramsWidget );

private:
	float& param_;
	float min_, max_;
	ParamsWidget* effectWidget_;

private slots:
	void sliderValueChanged_( int value );
};

class IntParamWidget: public QSlider
{
	Q_OBJECT
public:
	IntParamWidget( int& param, int min, int max, ParamsWidget* paramsWidget );

private:
	int& param_;
	int min_, max_;
	ParamsWidget* effectWidget_;

private slots:
	void sliderValueChanged_( int value );
};