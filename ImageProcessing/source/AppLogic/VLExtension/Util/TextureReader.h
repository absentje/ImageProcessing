#pragma once
#include <vlCore/Image.hpp>
#include <string>

namespace vl
{
class Image;
class Texture;
}

namespace TextureReader
{
void TextureToImage( const vl::Texture* inTexture, vl::Image* outImage );
void IDTextureToImage( const vl::Texture* inTexture, vl::Image* outImage );
void FloatTextureToImage( const vl::Texture* inTexture, vl::Image* outImage );

vl::ref<vl::Image> TextureToImage( vl::Texture* inTexture );
void saveTexture( vl::Texture* inTexture, const std::wstring& filePath );
};