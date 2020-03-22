#include "Pipeline.h"
#include <vlGraphics/Texture.hpp>

namespace VLExtension
{
Pipeline::Pipeline( int w, int h )
	: pInPipeline( nullptr ), pInTexture( nullptr ), pLastOutTexture( nullptr ), isEnable( true )
{
	pInTexture = new vl::Texture( w, h );
}

void Pipeline::SetInputTexture( vl::Texture* texture )
{
	VL_CHECK( texture )
		pInTexture = texture;
}

void Pipeline::SetInputPipeline( Pipeline* pipeline )
{
	VL_CHECK( pipeline )
		pInPipeline = pipeline;
}

Pipeline::~Pipeline()
{
}

void	Pipeline::SetEnable( bool enable )
{
	isEnable = enable;
}

bool	Pipeline::Enable() const
{
	return isEnable;
}

bool	Pipeline::HasInputTexture() const
{
	return pInTexture;
}

vl::Texture* Pipeline::GetInputTexture() const
{
	return pInTexture.get_writable();
}

bool	Pipeline::HasInputPipeline() const
{
	return pInPipeline;
}

Pipeline* Pipeline::GetInputPipeline() const
{
	return pInPipeline.get_writable();
}

vl::Texture* Pipeline::gocInTexture()
{
	if ( pInTexture )
		return pInTexture.get();
	else
		return pInPipeline->RenderOutTexture();
}

vl::Texture* Pipeline::RenderOutTexture()
{
	auto inTexture = gocInTexture();
	pLastOutTexture = Enable() ? render( inTexture ) : inTexture;
	return pLastOutTexture.get();
}

vl::Texture* Pipeline::GetLastOutTexture()
{
	return pLastOutTexture.get();
}

void	Pipeline::Resize( int width, int height )
{
	if ( pInPipeline )
		pInPipeline->Resize( width, height );
}
}