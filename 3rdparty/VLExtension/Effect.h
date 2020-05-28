#pragma once
#include <vlCore/Object.hpp>
#include <vlGraphics/UniformSet.hpp>
#include <string>

namespace VLExtension
{
class Shader;

/*
	������� ����� �������, ��������� ������� ���� ����������� ���������
	������������ ������� �� �������� 2� �������� (�������� � EffectPipeline)
*/
class Effect: public vl::Object
{
	VL_INSTRUMENT_CLASS( Effect, vl::Object )
public:
	Effect( const std::wstring& fs_path );

	bool		Enable() const;
	void		SetEnable( bool enable );

	// �����, � ������� ���� ��� ��������� �������, ��������� ������/��������� � �.�.
	virtual void onPipelineAdd( Shader* shader, int width, int height );

	// ����� ������� ����� ������� �������
	virtual void preRenderUpdate(Shader* shader, int width, int height, float deltaTime);

	vl::UniformSet*			GetUniformSet();
	const vl::UniformSet*	GetUniformSet() const;

protected:
	std::wstring				fs_path_;
	vl::ref<vl::UniformSet>		uniform_set_;	// ����� �������, ������� ������������
												// � ������������� ������� � onPipelineAdd()
private:
	bool						isEnable_ = true;
};
}