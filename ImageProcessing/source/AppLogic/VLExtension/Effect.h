#pragma once
#include <vlCore/Object.hpp>
#include <vlGraphics/UniformSet.hpp>
#include <string>

namespace VLExtension
{
class Shader;

/*
	базовый класс эффекта, наложение эффекта идет посредством наложения
	фрагментного шейдера на исходную 2д текстуру (задается в EffectPipeline)
*/
class Effect: public vl::Object
{
	VL_INSTRUMENT_CLASS( Effect, vl::Object )
public:
	Effect( const std::wstring& fs_path );

	bool		Enable() const;
	void		SetEnable( bool enable );

	// метод, в котором идет вся настройка эффекта, установка биндов/униформов и т.п.
	virtual void onPipelineAdd( Shader* shader, int width, int height );

	// метод апдейта перед вызовом рендера
	virtual void preRenderUpdate(Shader* shader, int width, int height, float deltaTime);

	vl::UniformSet*			GetUniformSet();
	const vl::UniformSet*	GetUniformSet() const;

protected:
	std::wstring				fs_path_;
	vl::ref<vl::UniformSet>		uniform_set_;	// набор униформ, которые подключаются
												// к передаваемому шейдеру в onPipelineAdd()
private:
	bool						isEnable_ = true;
};
}