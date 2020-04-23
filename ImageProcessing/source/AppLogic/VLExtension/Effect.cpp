#include "Effect.h"
#include <AppLogic/VLExtension/Shader.h>

namespace VLExtension
{

Effect::Effect( const std::wstring& fs_path )
	: fs_path_( fs_path ), uniform_set_( new vl::UniformSet )
{

}

bool	Effect::Enable() const
{
	return isEnable_;
}

void	Effect::SetEnable( bool enable )
{
	isEnable_ = enable;
}

void	Effect::onPipelineAdd( Shader* shader, int width, int height )
{
	shader->SetFShader( fs_path_ );
	shader->setUniformSet( uniform_set_.get() );
}

vl::UniformSet* Effect::GetUniformSet()
{
	return uniform_set_.get();
}

const vl::UniformSet* Effect::GetUniformSet() const
{
	return uniform_set_.get();
}

}