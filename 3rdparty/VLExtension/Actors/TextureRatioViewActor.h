#pragma once
#include "TextureViewActor.h"

/*
	�����, �. ������� �������� ��������(-�) �������� ��������� ��������
*/
namespace VLExtension
{
class TextureRatioViewActor: public TextureViewActor
{
	VL_INSTRUMENT_CLASS( TextureRatioViewActor, TextureViewActor );
public:
	TextureRatioViewActor( vl::Texture* texture = nullptr );
};
}