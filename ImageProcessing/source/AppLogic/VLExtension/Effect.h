#pragma once
#include <vlCore/Object.hpp>

namespace VLExtension
{
class Shader;

/*
	������� ����� �������, ��������� ������� ���� ����������� ���������
	������������ ������� �� �������� 2� �������� (�������� � EfffectPipeline)
*/
class Effect: public vl::Object
{
	VL_INSTRUMENT_CLASS( Effect, vl::Object )
public:
	Effect();
	virtual ~Effect() {}

	bool		Enable() const;
	void		SetEnable( bool enable );

	// ����� � ������� ���� ��� ��������� �������, ��������� ������/��������� � �.�.
	virtual void	onPipelineAdd( Shader* shader, int width, int height ) {}

	// ����� ��� ������� ��������� ��������� ����� ������� �������
	virtual void	preRenderUpdate( Shader* shader, int width, int height, float deltaTime ) {}

protected:

private:
	bool	isEnable;
};
}