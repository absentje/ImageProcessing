#include "Actor.h"
#include <vlGraphics/GLSL.hpp>

namespace VLExtension
{
Actor::Actor( vl::Geometry* geom, vl::Transform* tr )
{
	pActor = new vl::Actor;
	pGeometry = geom ? geom : new vl::Geometry;
	pActor->setLod( 0, pGeometry.get() );

	pTransform = tr ? tr : new vl::Transform;
	pActor->setTransform( pTransform.get() );

	// создаем эффект и подменяем вл шейдеры своими обертками
	pActor->setEffect( new vl::Effect );
	pActor->effect()->lod( 0 )->clear();
	AddShaderPass();
}

Actor::~Actor()
{

}

void Actor::setEnabled( bool value )
{
	pActor->setEnabled( value );
}

vl::ref<Actor>	Actor::CreateClone()
{
	vl::ref<Actor> clone = new Actor( pGeometry.get_writable() );
	clone->SetTransform( pTransform.get_writable() );
	//clone->VLActor()->setUniformSet(pActor->getUniformSet());
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
	auto count = pActor->effect()->lod( 0 )->size();
	if ( count >= VL_MAX_EFFECT_LOD )
		return nullptr;

	vl::ref<Shader> uShader = new Shader;
	uShader->enable( vl::EN_DEPTH_TEST );
	pActor->effect()->lod( 0 )->push_back( uShader.get() );
	return uShader.get();
}

Shader* Actor::GetShader( int pass )
{
	int count = GetShaderPassCount();
	if ( pass >= 0 && pass < count )
		return static_cast<Shader*>( ( *pActor->effect()->lod( 0 ) )[pass].get() );
	else
		return nullptr;
}

const Shader* Actor::GetShader( int pass ) const
{
	int count = GetShaderPassCount();
	if ( pass >= 0 && pass < count )
		return static_cast<const Shader*>( ( *pActor->effect()->lod( 0 ) )[pass].get() );
	else
		return nullptr;
}

int		Actor::GetShaderPassCount() const
{
	return pActor->effect()->lod( 0 )->size();
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

vl::Transform* Actor::GetTransform()
{
	return pTransform.get();
}
const vl::Transform* Actor::GetTransform() const
{
	return pTransform.get();
}

vl::Actor* Actor::VLActor()
{
	return pActor.get();
}
const vl::Actor* Actor::VLActor() const
{
	return pActor.get();
}

void	Actor::SetTransform( vl::Transform* tr )
{
	pActor->setTransform( tr );
}

void	Actor::SetUniform( vl::Uniform* uni )
{
	pActor->setUniform( uni );
}

void	Actor::RemoveUniform( vl::Uniform* uni )
{
	pActor->eraseUniform( uni );
}

void	Actor::SetRenderRank( int rank )
{
	pActor->setRenderRank( rank );
}
int		Actor::GetRenderRank() const
{
	return pActor->renderRank();
}
}