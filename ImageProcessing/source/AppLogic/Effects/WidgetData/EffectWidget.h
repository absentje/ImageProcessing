#pragma once
#include <vlCore/Object.hpp>
#include <string>
#include <QWidget>

class IEffect;
class QVBoxLayout;

class EffectWidget: public QWidget
{
	Q_OBJECT
public:
	EffectWidget( QWidget* parent, IEffect* effect );
	
	void AddParam( const std::wstring& paramName, float& param, float min, float max );
	void AddParam( const std::wstring& paramName, int& param, int min, int max );
//	void AddParam( bool& param );

	void OnUpdate();

private:
	IEffect* effect_;

	QVBoxLayout* mainLayout;
};