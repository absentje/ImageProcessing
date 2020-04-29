#include "FPSActor.h"
#include <vlGraphics/Text.hpp>
#include <vlGraphics/FontManager.hpp>
#include <vlCore/Colors.hpp>
#include <vlCore/Time.hpp>
#include <vlCore/Say.hpp>

using namespace vl;

namespace
{
ref<Text> CreateTextRenderableObj()
{
	ref<Text> renderable_obj = new Text;
	renderable_obj->setFont( defFontManager()->acquireFont( "resources/fonts/consolai.ttf", 12 ) );
	renderable_obj->setTextAlignment( TextAlignCenter );
	renderable_obj->setAlignment( AlignHCenter | AlignBottom );
	renderable_obj->setViewportAlignment( AlignHCenter | AlignBottom );
	renderable_obj->translate( 0, 5, 0 );
	renderable_obj->setBackgroundEnabled( true );
	renderable_obj->setBackgroundColor( fvec4( 0, 0, 0, 0.75 ) );
	renderable_obj->setColor( vl::white );
	return renderable_obj;
}

ref<Effect> CreateTextEffect()
{
	ref<Effect> effect = new Effect;
	effect->shader()->enable( EN_BLEND );
	return effect;
}

class FPSValueUpdater: public vl::ActorEventCallback
{
	VL_INSTRUMENT_CLASS( FPSValueUpdater, vl::ActorEventCallback );
public:
	FPSValueUpdater( vl::ref<vl::Text> FPS_Text ) :
		fps_text( FPS_Text )
	{
	}

	virtual void onActorRenderStarted(
		vl::Actor* actor,
		vl::real frame_clock,
		const vl::Camera* cam,
		vl::Renderable* renderable,
		const vl::Shader* shader, int pass ) override
	{
		if ( pass != 0 ) return;
		const double dt_FPS = Time::currentTime() - mLastFPSTime;
		// update fps
		if ( dt_FPS > 0.1f )
		{
			double secs = dt_FPS;
			double FPS = mFrameCount / secs;
			mFrameCount = 0;
			mLastFPSTime = Time::currentTime();
			if ( FPS > 0 )
			{
				if ( fps_text )
				{
					fps_text->setText( Say( "fps = %n" ) << FPS );
				}
			}
		}
		mFrameCount++;
	}

	/** Event notifying that an Actor is being deleted. */
	virtual void onActorDelete( vl::Actor* actor ) override {}

private:
	vl::ref<vl::Text>	fps_text;
	double				mLastFPSTime;
	int					mFrameCount;
};
}

namespace VLExtension
{


FPSActor::FPSActor()
	: Actor( CreateTextRenderableObj().get(), CreateTextEffect().get() )
{
	auto text = static_cast<vl::Text*>( lod( 0 ) );
	actorEventCallbacks()->push_back( new FPSValueUpdater( text ) );
}

}