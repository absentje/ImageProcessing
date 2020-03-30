#pragma once
#include <vlCore/Object.hpp>
#include <string>

class QWidget;
class ParamsWidget;

class Selector: public vl::Object
{
	VL_INSTRUMENT_CLASS( Selector, vl::Object );
public:
	Selector( const std::wstring& name );

	const std::wstring& GetName() const;

	virtual void Apply() = 0;
	virtual QWidget* CreateWidget( QWidget* parent ) = 0;

private:
	std::wstring name_;
};

