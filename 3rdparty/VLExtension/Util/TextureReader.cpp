#include "TextureReader.h"
#include <vlGraphics/Texture.hpp>
#include <vlCore/Image.hpp>

namespace TextureReader
{

vl::ref<vl::Image> TextureToImage( vl::Texture* inTexture )
{
	vl::ref<vl::Image> resultValue = new vl::Image;
	TextureToImage( inTexture, resultValue.get() );
	return resultValue;
}

void TextureToImage( const vl::Texture* inTexture, vl::Image* outImage )
{
	if ( !outImage || !inTexture )
		return;
	const int t_w = inTexture->width();
	const int t_h = inTexture->height();
	const int img_w = outImage->width();
	const int img_h = outImage->height();

	if ( t_w != img_w || t_h != img_h || outImage->dimension() != vl::ID_2D || outImage->pixels() == NULL )
		outImage->allocate2D( t_w, t_h, 1, outImage->format(), outImage->type() );
	glBindTexture( GL_TEXTURE_2D, inTexture->handle() );
	glGetTexImage( GL_TEXTURE_2D, 0, outImage->format()/*GL_RGBA8*/, outImage->type()/*GL_UNSIGNED_BYTE*/, const_cast<unsigned char*>( outImage->pixels() ) );
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void IDTextureToImage( const vl::Texture* inTexture, vl::Image* outImage )
{
	if ( !outImage || !inTexture )
		return;
	const int t_w = inTexture->width();
	const int t_h = inTexture->height();
	const int img_w = outImage->width();
	const int img_h = outImage->height();

	if ( t_w != img_w || t_h != img_h || outImage->dimension() != vl::ID_2D || outImage->pixels() == NULL )
		outImage->allocate2D( t_w, t_h, 1, outImage->format(), outImage->type() );
	glBindTexture( GL_TEXTURE_2D, inTexture->handle() );
	glGetTexImage( GL_TEXTURE_2D, 0, GL_RG_INTEGER, GL_UNSIGNED_SHORT, const_cast<unsigned char*>( outImage->pixels() ) );
	glBindTexture( GL_TEXTURE_2D, 0 );
	VL_CHECK_OGL();
}

void FloatTextureToImage( const vl::Texture* inTexture, vl::Image* outImage )
{
	if ( !outImage || !inTexture )
		return;
	const int t_w = inTexture->width();
	const int t_h = inTexture->height();
	const int img_w = outImage->width();
	const int img_h = outImage->height();

	if ( t_w != img_w || t_h != img_h || outImage->dimension() != vl::ID_2D || outImage->pixels() == NULL )
		outImage->allocate2D( t_w, t_h, 1, outImage->format(), outImage->type() );
	glBindTexture( GL_TEXTURE_2D, inTexture->handle() );
	glGetTexImage( GL_TEXTURE_2D, 0, GL_RED, GL_FLOAT, const_cast<unsigned char*>( outImage->pixels() ) );
	glBindTexture( GL_TEXTURE_2D, 0 );
	VL_CHECK_OGL();
}

void saveTexture( vl::Texture* inTexture, const std::wstring& filePath )
{
	auto img = TextureToImage( inTexture );
	vl::saveImage( img.get(), filePath );
}
};