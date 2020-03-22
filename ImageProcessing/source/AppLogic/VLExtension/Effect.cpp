#include "Effect.h"

namespace VLExtension
{
Effect::Effect()
	: isEnable( true )
{

}

bool	Effect::Enable() const
{
	return isEnable;
}

void	Effect::SetEnable( bool enable )
{
	isEnable = enable;
}
}