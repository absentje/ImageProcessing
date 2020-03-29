#pragma once
#include <functional>
#include <QSlider>

class IEffect;
class EffectWidget;

class FloatWidgetParam: public QSlider
{
	Q_OBJECT
public:
	FloatWidgetParam( float& param, float min, float max, EffectWidget* effectWidget );

private:
	float& param_;
	float min_, max_;
	EffectWidget* effectWidget_;

private slots:
	void sliderValueChanged_( int value );
};

class IntWidgetParam: public QSlider
{
	Q_OBJECT
public:
	IntWidgetParam( int& param, int min, int max, EffectWidget* effectWidget );

private:
	int& param_;
	int min_, max_;
	EffectWidget* effectWidget_;

private slots:
	void sliderValueChanged_( int value );
};