#include "TextureRatioViewActor.h"

namespace VLExtension
{
class TextureViewActorEventCallback: public vl::ActorEventCallback
{
	VL_INSTRUMENT_CLASS( TextureViewActorEventCallback, vl::ActorEventCallback );
public:
	TextureViewActorEventCallback() {}

	void onActorRenderStarted(
		vl::Actor* actor,
		vl::real frame_clock,
		const vl::Camera* camera,
		vl::Renderable* renderable,
		const vl::Shader* shader, int pass ) override
	{
		actor->gocUniform( "screen_Size" )->setUniform( vl::vec2( float( camera->viewport()->width() ), float( camera->viewport()->height() ) ) );
		const auto texture = actor->effect()->shader()->gocTextureSampler( 0 )->texture();
		if ( texture )
		{
			actor->gocUniform( "texture_Size" )->setUniform( vl::vec2( float( texture->width() ), float( texture->height() ) ) );
		}

	}
	virtual void onActorDelete( vl::Actor* actor ) override {}
};

TextureRatioViewActor::TextureRatioViewActor( vl::Texture* texture )
	: TextureViewActor( texture )
{
	// каллбек для передачи в шейдер униформов width/height вьюпорта для сохранения пропорции текстур
	vl::ref<TextureViewActorEventCallback> ev_callback = new TextureViewActorEventCallback();
	actorEventCallbacks()->push_back( ev_callback.get() );

	GetShader()->SetVShader( L"resources/glsl/texture_ratio_view.vs" );
}
}