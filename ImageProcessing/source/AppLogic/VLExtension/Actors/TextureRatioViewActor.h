#pragma once
#include "TextureViewActor.h"

/*
	�����, �. ������� �������� ��������(-�) �������� ��������� ��������
*/
class TextureRatioViewActor : public TextureViewActor
{
	VL_INSTRUMENT_CLASS(TextureRatioViewActor, TextureViewActor);
public:
	TextureRatioViewActor(vl::Texture* texture = nullptr);
};