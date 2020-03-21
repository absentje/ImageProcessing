#include "Effect.h"


Effect::Effect()
    : isEnable(true)
{
	
}

bool	Effect::Enable() const
{
	return isEnable;
}

void	Effect::SetEnable(bool enable)
{
	isEnable = enable;
}
