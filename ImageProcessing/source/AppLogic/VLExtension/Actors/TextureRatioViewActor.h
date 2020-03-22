#pragma once
#include "TextureViewActor.h"

/*
	јктор, к. рендрит заданную текстуру(-ы) сохран€€ пропорции текстуры
*/
namespace VLExtension
{
class TextureRatioViewActor: public TextureViewActor
{
	VL_INSTRUMENT_CLASS( TextureRatioViewActor, TextureViewActor );
public:
	TextureRatioViewActor( vl::Texture* texture = nullptr );
};
}