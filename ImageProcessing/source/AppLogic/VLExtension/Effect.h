#pragma once
#include <vlCore/Object.hpp>

namespace VLExtension
{
class Shader;

/*
	базовый класс эффекта, наложение эффекта идет посредством наложения
	фрагментного шейдера на исходную 2д текстуру (задается в EfffectPipeline)
*/
class Effect: public vl::Object
{
	VL_INSTRUMENT_CLASS( Effect, vl::Object )
public:
	Effect();
	virtual ~Effect() {}

	bool		Enable() const;
	void		SetEnable( bool enable );

	// метод в котором идет вся настройка еффекта, установка биндов/униформов и т.п.
	virtual void	onPipelineAdd( Shader* shader, int width, int height ) {}

	// метод для упдейта различных униформов перед вызовом рендера
	virtual void	preRenderUpdate( Shader* shader, int width, int height, float deltaTime ) {}

protected:

private:
	bool	isEnable;
};
}