#include "IEffect.h"
#include "WidgetData/EffectWidget.h"

IEffect::IEffect( const std::wstring& effectName )
	: effectName_( effectName )
{

}

const std::wstring& IEffect::GetEffectName() const
{
	return effectName_;
}

QWidget* IEffect::CreateWidget( QWidget* parent )
{
	EffectWidget* effectWidget = new EffectWidget( parent, this );
	OnCreatedEffectWidget( effectWidget );
	return effectWidget;
}