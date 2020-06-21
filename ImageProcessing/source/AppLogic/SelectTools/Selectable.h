#pragma once
#include <vlCore/Object.hpp>
#include <string>

class QWidget;
class ParamsWidget;

class Selectable: public vl::Object
{
	VL_INSTRUMENT_CLASS( Selectable, vl::Object );
public:
	Selectable( const std::wstring& name );

	const std::wstring& GetName() const;

	virtual void Enable( bool value ) = 0;

	virtual QWidget* CreateWidget( QWidget* parent ) = 0;

private:
	std::wstring name_;
};

