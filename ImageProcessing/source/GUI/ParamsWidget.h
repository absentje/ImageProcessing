#pragma once
#include <vlCore/Object.hpp>
#include <string>
#include <QGroupBox>
#include <vlGraphics/Texture.hpp>
#include <vlGraphics/Geometry.hpp>

class ParamsSelectable;
class QVBoxLayout;

class ParamsWidget: public QGroupBox
{
	Q_OBJECT
public:
	ParamsWidget( QWidget* parent, ParamsSelectable* effect );
	
	void AddParam( const std::wstring& paramName, float& param, float min, float max );
	void AddParam( const std::wstring& paramName, int& param, int min, int max );
	void AddParam( const std::wstring& paramName, bool& param );
	void AddParam( const std::wstring& paramName, vl::Texture& param );
	void AddParam( const std::wstring& paramName, vl::Geometry& param );

	void OnUpdate();

private:
	ParamsSelectable* effect_;

	QVBoxLayout* mainLayout;
};