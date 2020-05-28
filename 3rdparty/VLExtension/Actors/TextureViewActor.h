#pragma once
#include <VLExtension/Actor.h>

namespace vl
{
	class Texture;
}

/*
	Актор, к. рендрит заданную текстуру(-ы) по вьюпорту
*/
namespace VLExtension
{
class TextureViewActor: public Actor
{
	VL_INSTRUMENT_CLASS( TextureViewActor, Actor );
public:
	TextureViewActor( vl::Texture* texture = nullptr, bool prepare_effect = true );

	void		SetTexture( vl::Texture* texture );
	void		SetTexture( vl::Texture* texture, int index, const char* name );

	void	SetScreenBorders( float left, float right, float top, float bottom );
	void	SetScreenPositions( const vl::vec2& p0, const vl::vec2& p1, const vl::vec2& p2, const vl::vec2& p3 );

private:
	void	prepareGeometry();
	void	prepareEffect();
};
}