#include "Selector.h"

Selector::Selector( const std::wstring& name )
	: name_( name )
{

}

const std::wstring& Selector::GetName() const
{
	return name_;
}