#pragma once
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Geometry.hpp>
#include "Shader.h"

namespace VLExtension
{
class Actor: public vl::Actor
{
	VL_INSTRUMENT_CLASS( Actor, vl::Actor )
public:
	Actor( vl::Geometry* geom = nullptr, vl::Transform* tr = nullptr );
	virtual ~Actor();

	Shader* AddShaderPass();
	int		GetShaderPassCount() const;
	int		GetMaxShaderPassCount() const;
	void	UpdateAllShaders();

	Shader*			GetShader( int pass = 0 );
	const Shader*	GetShader( int pass = 0 ) const;

	vl::Geometry*		GetGeometry();
	const vl::Geometry*	GetGeometry() const;

	virtual vl::ref<Actor>	CreateClone();

protected:
	vl::ref<vl::Geometry>	pGeometry;
	vl::ref<vl::Transform>	pTransform;
};
}