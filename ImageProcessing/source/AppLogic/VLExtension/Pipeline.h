#pragma once

#include <vlCore/Object.hpp>

namespace vl
{
	class Texture;
}

/*
	базовый класс конвейера
*/
class Pipeline : public vl::Object
{
    VL_INSTRUMENT_CLASS(Pipeline, vl::Object)
public:
//    Pipeline(int width, int height);
//    Pipeline(vl::Texture* texture);
//    Pipeline(Pipeline* pipeline);

    Pipeline(int w, int h);
    virtual ~Pipeline();

    virtual void    SetInputTexture(vl::Texture* texture);
    virtual void    SetInputPipeline(Pipeline* pipeline);

	vl::Texture*	RenderOutTexture();
	vl::Texture*	GetLastOutTexture();

	bool			HasInputTexture() const;
	vl::Texture*	GetInputTexture() const;
	bool			HasInputPipeline() const;
    Pipeline*       GetInputPipeline() const;

    void            SetEnable(bool enable);
    bool            Enable() const;

	virtual int		GetWidth() const = 0;
	virtual int		GetHeight() const = 0;

    virtual void	Resize(int width, int height);

protected:

	virtual vl::Texture*	render(vl::Texture* inTexture) = 0;

private:

	vl::Texture*	gocInTexture();

    vl::ref<Pipeline>       pInPipeline;
	vl::ref<vl::Texture>	pInTexture;
	vl::ref<vl::Texture>	pLastOutTexture;
	
	bool	isEnable;
};
