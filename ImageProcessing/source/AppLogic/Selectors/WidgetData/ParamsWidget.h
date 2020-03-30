#pragma once
#include <vlCore/Object.hpp>
#include <string>
#include <QGroupBox>

class ParamsSelector;
class QVBoxLayout;

class ParamsWidget: public QGroupBox
{
	Q_OBJECT
public:
	ParamsWidget( QWidget* parent, ParamsSelector* effect );
	
	void AddParam( const std::wstring& paramName, float& param, float min, float max );
	void AddParam( const std::wstring& paramName, int& param, int min, int max );
//	void AddParam( bool& param );

	void OnUpdate();

private:
	ParamsSelector* effect_;

	QVBoxLayout* mainLayout;
};