#include "TextureViewActor.h"
#include <vlGraphics/Geometry.hpp>

namespace VLExtension
{
TextureViewActor::TextureViewActor( vl::Texture* texture, bool prepare_effect )
{
	prepareGeometry();
	if ( prepare_effect )
		prepareEffect();
	if ( texture )
		SetTexture( texture, 0, "texture0" );
}

void TextureViewActor::prepareGeometry()
{
	auto geom = GetGeometry();
	vl::ref<vl::ArrayFloat3> vertex_array = new vl::ArrayFloat3;
	vl::ref<vl::ArrayFloat2> textureUV_array = new vl::ArrayFloat2;
	vertex_array->resize( 4 );
	textureUV_array->resize( 4 );

	geom->setVertexArray( vertex_array.get() );
	geom->setTexCoordArray( 0, textureUV_array.get() );
	geom->setBufferObjectDirty();

	const float LEFT_BORDER = -1.f, RIGHT_BORDER = 1.f, TOP_BORDER = 1.f, BOTTOM_BORDER = -1.f;	// default values

	SetScreenBorders( LEFT_BORDER, RIGHT_BORDER, TOP_BORDER, BOTTOM_BORDER );

	( *textureUV_array )[0] = vl::vec2( 0.f, 0.f );
	( *textureUV_array )[1] = vl::vec2( 1.f, 0.f );
	( *textureUV_array )[2] = vl::vec2( 1.f, 1.f );
	( *textureUV_array )[3] = vl::vec2( 0.f, 1.f );
	textureUV_array->setBufferObjectDirty();


	vl::ref<vl::DrawElementsUInt> triangles_draw_element = new vl::DrawElementsUInt( vl::PT_QUADS );// vl::PT_TRIANGLES);

	triangles_draw_element->indexBuffer()->resize( 4 );
	geom->drawCalls().push_back( triangles_draw_element.get() );

	triangles_draw_element->indexBuffer()->at( 0 ) = 0;
	triangles_draw_element->indexBuffer()->at( 1 ) = 1;
	triangles_draw_element->indexBuffer()->at( 2 ) = 2;
	triangles_draw_element->indexBuffer()->at( 3 ) = 3;
}

void TextureViewActor::prepareEffect()
{
	auto shader = GetShader();
	shader->SetVShader( L"resources/glsl/texture_view.vs" );
	shader->SetFShader( L"resources/glsl/texture_view.fs" );
	shader->disable( vl::EN_DEPTH_TEST );
}

void	TextureViewActor::SetTexture( vl::Texture* texture )
{
	SetTexture( texture, 0, nullptr );
}

void	TextureViewActor::SetTexture( vl::Texture* texture, int index, const char* name )
{
	auto shader = GetShader();
	shader->gocTextureSampler( index )->setTexture( texture ? texture : ( new vl::Texture( 8, 8, vl::ETextureFormat::TF_RGBA ) ) );
	if ( name )
		shader->gocUniform( name )->setUniformI( index );
}

void	TextureViewActor::SetScreenBorders( float left, float right, float top, float bottom )
{
	auto vertex_array = static_cast<vl::ArrayFloat3*>( GetGeometry()->vertexArray() );
	( *vertex_array )[0] = vl::vec3( left, bottom, 1 );
	( *vertex_array )[1] = vl::vec3( right, bottom, 1 );
	( *vertex_array )[2] = vl::vec3( right, top, 1 );
	( *vertex_array )[3] = vl::vec3( left, top, 1 );
	vertex_array->setBufferObjectDirty();
	GetGeometry()->setBufferObjectDirty();
}

void	TextureViewActor::SetScreenPositions( const vl::vec2& p0, const vl::vec2& p1, const vl::vec2& p2, const vl::vec2& p3 )
{
	auto vertex_array = static_cast<vl::ArrayFloat3*>( GetGeometry()->vertexArray() );
	( *vertex_array )[0] = vl::vec3( p0, 1 );
	( *vertex_array )[1] = vl::vec3( p1, 1 );
	( *vertex_array )[2] = vl::vec3( p2, 1 );
	( *vertex_array )[3] = vl::vec3( p3, 1 );
	vertex_array->setBufferObjectDirty();
	GetGeometry()->setBufferObjectDirty();
}
}