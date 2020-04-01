#include "Selectable.h"

Selectable::Selectable( const std::wstring& name )
	: name_( name )
{

}

const std::wstring& Selectable::GetName() const
{
	return name_;
}