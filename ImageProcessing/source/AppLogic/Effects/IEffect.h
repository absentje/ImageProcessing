#pragma once
#include <vlCore/Object.hpp>
#include <string>

class QWidget;
class EffectWidget;

class IEffect: public vl::Object
{
	VL_INSTRUMENT_CLASS( IEffect, vl::Object );
public:
	IEffect( const std::wstring& effectName );

	const std::wstring& GetEffectName() const;

	virtual void ApplyEffect() = 0;
	virtual void UpdateData() = 0;

	QWidget* CreateWidget( QWidget* parent );

protected:
	// widget-parameters will be attached here
	virtual void OnCreatedEffectWidget( EffectWidget* effectWidget ) = 0;


	std::wstring effectName_;
};

