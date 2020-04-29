#pragma once
#include <vlGraphics/Actor.hpp>

namespace VLExtension
{

class FPSActor: public vl::Actor
{
	VL_INSTRUMENT_CLASS( FPSActor, vl::Actor );
public:
	FPSActor();
};

}