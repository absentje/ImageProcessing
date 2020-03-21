#pragma once
#include <Pipeline.h>
#include <list>

class Effect;
class FBORender;
class TextureViewActor;

namespace vl
{
	class Texture;
    class OpenGLContext;
}

/*
	класс конвейер эффектов, которые накладываются на заданную текстуру один за другим
*/
class EffectPipeline : public Pipeline
{
    VL_INSTRUMENT_CLASS(EffectPipeline, Pipeline)
public:
    EffectPipeline(vl::OpenGLContext* context);

    virtual void    SetInputTexture(vl::Texture* texture) override;
    virtual void    SetInputPipeline(Pipeline* pipeline) override;

    virtual ~EffectPipeline();

    virtual void	AddEffect(Effect* effect);
    virtual void	RemoveEffect(Effect* effect);
    void			MoveToBegin(Effect* effect);
    void			MoveToEnd(Effect* effect);
    void			GetEffects(std::list<vl::ref<Effect>>& list) const;

	virtual int		GetWidth() const override;
	virtual int		GetHeight() const override;

	virtual void	Resize(int width, int height) override;

	virtual void	ReloadEffectShaders();

protected:

	virtual vl::Texture*	render(vl::Texture* inTexture) override;

	vl::ref<FBORender>		pFBO[2];

private:

	struct EffectActor
	{
        vl::ref<Effect>			pEffect;
		vl::ref<TextureViewActor>	pActor;
	};

    bool	findEffect(Effect* effect, std::list<EffectPipeline::EffectActor>::iterator& it);

	std::list<EffectActor>	lEffectActors;
	
	float	prevRenderTime;
};
