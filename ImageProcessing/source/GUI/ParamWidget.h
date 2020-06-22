#pragma once
#include <functional>
#include <QSlider>
#include <QCheckBox>
#include <QPushButton>
#include <QString>
#include <vlGraphics/Texture.hpp>
#include <vlGraphics/Geometry.hpp>

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
	ParamsWidget* paramsWidget_;

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
	ParamsWidget* paramsWidget_;

private slots:
	void sliderValueChanged_( int value );
};

class BoolParamWidget : public QCheckBox
{
	Q_OBJECT
public:
	BoolParamWidget( bool& param, ParamsWidget* paramsWidget );

private:
	bool& param_;
	ParamsWidget* paramsWidget_;

	void setValue_( bool value );

private slots:
	void checkBoxValueChanged_( int value );
};

class FileParamWidget: public QPushButton
{
	Q_OBJECT
public:
	FileParamWidget( ParamsWidget* paramsWidget );
	void SetFileFilter( const QString& fileFilter );

protected:
	virtual void onFileNameChanged() = 0;
	std::wstring file_name_;
private:
	void onClicked_();

private:
	ParamsWidget* paramsWidget_;
	QString fileFilter_;
};

class TextureParamWidget: public FileParamWidget
{
	Q_OBJECT
public:
	TextureParamWidget( vl::Texture& param, ParamsWidget* paramsWidget );
	void SetTextureFormat( vl::ETextureFormat format );

protected:
	virtual void onFileNameChanged() override final;

private:
	vl::Texture&		param_;
	vl::ETextureFormat	tex_format_;
};

class GeometryParamWidget: public FileParamWidget
{
	Q_OBJECT
public:
	GeometryParamWidget( vl::Geometry& param, ParamsWidget* paramsWidget );

protected:
	virtual void onFileNameChanged() override final;

private:
	vl::Geometry& param_;
};