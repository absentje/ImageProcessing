#include "Actor.h"
#include <vlGraphics/GLSL.hpp>

namespace VLExtension
{
Actor::Actor( vl::Geometry* geom, vl::Transform* tr )
{
	pGeometry = geom ? geom : new vl::Geometry;
	setLod( 0, pGeometry.get() );

	pTransform = tr ? tr : new vl::Transform;
	setTransform( pTransform.get() );

	// создаем эффект и подменяем вл шейдеры своими обертками
	setEffect( new vl::Effect );
	effect()->lod( 0 )->clear();
	AddShaderPass();
}

Actor::~Actor()
{

}

vl::ref<Actor>	Actor::CreateClone()
{
	vl::ref<Actor> clone = new Actor( pGeometry.get_writable() );
	clone->setTransform( pTransform.get_writable() );
//	clone->setUniformSet( getUniformSet() );
	return clone;
}

void	Actor::UpdateAllShaders()
{
	int count = GetShaderPassCount();
	for ( int i = 0; i < count; ++i )
	{
		GetShader( i )->ReloadShaders();
	}
}

Shader* Actor::AddShaderPass()
{
	auto count = effect()->lod( 0 )->size();
	if ( count >= VL_MAX_EFFECT_LOD )
		return nullptr;

	vl::ref<Shader> uShader = new Shader;
	uShader->enable( vl::EN_DEPTH_TEST );
	effect()->lod( 0 )->push_back( uShader.get() );
	return uShader.get();
}

Shader* Actor::GetShader( int pass )
{
	int count = GetShaderPassCount();
	if ( pass >= 0 && pass < count )
		return static_cast<Shader*>( ( *effect()->lod( 0 ) )[pass].get() );
	else
		return nullptr;
}

const Shader* Actor::GetShader( int pass ) const
{
	int count = GetShaderPassCount();
	if ( pass >= 0 && pass < count )
		return static_cast<const Shader*>( ( *effect()->lod( 0 ) )[pass].get() );
	else
		return nullptr;
}

int		Actor::GetShaderPassCount() const
{
	return effect()->lod( 0 )->size();
}

int		Actor::GetMaxShaderPassCount() const
{
	return VL_MAX_EFFECT_LOD;
}

vl::Geometry* Actor::GetGeometry()
{
	return pGeometry.get();
}
const vl::Geometry* Actor::GetGeometry() const
{
	return pGeometry.get();
}
}