#pragma once
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Geometry.hpp>
#include "Shader.h"

namespace VLExtension
{
class Actor: public vl::Object
{
	VL_INSTRUMENT_CLASS( Actor, vl::Object )
public:
	Actor( vl::Geometry* geom = nullptr, vl::Transform* tr = nullptr );
	virtual ~Actor();

	void setEnabled( bool value = true );

	// методы VLActor() чисто дл€ добавлени€ в вл—цену
	// Ќ≈ юзать дл€ доступа к еффектам/лода и т.п. !!!
	vl::Actor* VLActor();
	const vl::Actor* VLActor() const;

	Shader* AddShaderPass();
	int				GetShaderPassCount() const;
	int				GetMaxShaderPassCount() const;
	void			UpdateAllShaders();

	Shader* GetShader( int pass = 0 );
	const Shader* GetShader( int pass = 0 ) const;

	vl::Geometry* GetGeometry();
	const vl::Geometry* GetGeometry() const;

	vl::Transform* GetTransform();
	const vl::Transform* GetTransform() const;
	void					SetTransform( vl::Transform* tr );

	virtual vl::ref<Actor>	CreateClone();

	void		SetUniform( vl::Uniform* uni );
	void		RemoveUniform( vl::Uniform* uni );

	void		SetRenderRank( int rank );
	int			GetRenderRank() const;

protected:

	vl::ref<vl::Actor>		pActor;
	vl::ref<vl::Geometry>	pGeometry;
	vl::ref<vl::Transform>	pTransform;
};
}