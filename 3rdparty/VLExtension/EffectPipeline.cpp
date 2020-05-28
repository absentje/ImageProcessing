#include "EffectPipeline.h"
#include "Effect.h"
#include "FBORender.h"
#include "Actors/TextureViewActor.h"
#include <vlGraphics/Texture.hpp>
#include <vlCore/Time.hpp>

const vl::ivec2 START_SIZE = vl::ivec2(512, 512);

namespace VLExtension
{
EffectPipeline::EffectPipeline()
	: super( START_SIZE.x(), START_SIZE.y() )
{
	pFBO[0] = new FBORender;
	pFBO[1] = new FBORender;
	pFBO[0]->Resize( START_SIZE.x(), START_SIZE.y() );
	pFBO[1]->Resize( START_SIZE.x(), START_SIZE.y() );

	prevRenderTime = vl::Time::currentTime();
}

void EffectPipeline::SetInputTexture( vl::Texture* texture )
{
	Resize( texture->width(), texture->height() );
	super::SetInputTexture( texture );
}

void EffectPipeline::SetInputPipeline( Pipeline* pipeline )
{
	Resize( pipeline->GetWidth(), pipeline->GetHeight() );
	super::SetInputPipeline( pipeline );
}

EffectPipeline::~EffectPipeline()
{}

int		EffectPipeline::GetWidth() const
{
	return pFBO[0]->GetWidth();
}
int		EffectPipeline::GetHeight() const
{
	return pFBO[0]->GetHeight();
}

void	EffectPipeline::Resize( int width, int height )
{
	pFBO[0]->SetTextureFormat( GetTextureFormat() );
	pFBO[1]->SetTextureFormat( GetTextureFormat() );
	pFBO[0]->Resize( width, height );
	pFBO[1]->Resize( width, height );

	super::Resize( width, height );
}

void	EffectPipeline::AddEffect( Effect* effect )
{
	VL_CHECK( effect );

	auto effectActor = new TextureViewActor;
	effect->onPipelineAdd( effectActor->GetShader(), GetWidth(), GetHeight() );
	lEffectActors.push_back( EffectActor{ effect, effectActor } );
}

bool	EffectPipeline::findEffect( Effect* effect, std::list<EffectPipeline::EffectActor>::iterator& it )
{
	for ( it = lEffectActors.begin(); it != lEffectActors.end(); ++it )
	{
		if ( it->pEffect == effect )
		{
			return true;
		}
	}
	return false;
}

void	EffectPipeline::RemoveEffect( Effect* effect )
{
	VL_CHECK( effect )
		auto it = lEffectActors.begin();
	if ( findEffect( effect, it ) )
	{
		it = lEffectActors.erase( it );
	}
}

void	EffectPipeline::MoveToBegin( Effect* effect )
{
	VL_CHECK( effect );
	auto it = lEffectActors.begin();
	if ( findEffect( effect, it ) && it != lEffectActors.begin() )
	{
		auto prev_it = std::prev( it );
		std::swap( it, prev_it );
	}
}

void	EffectPipeline::MoveToEnd( Effect* effect )
{
	VL_CHECK( effect );
	auto it = lEffectActors.begin();
	if ( findEffect( effect, it ) && it != std::prev( lEffectActors.end() ) )
	{
		auto next_it = std::next( it );
		std::swap( it, next_it );
	}
}

void	EffectPipeline::GetEffects( std::list<vl::ref<Effect>>& list ) const
{
	for ( auto& ea : lEffectActors )
	{
		list.push_back( ea.pEffect );
	}
}

void	EffectPipeline::ReloadEffectShaders()
{
	for ( auto& ea : lEffectActors )
	{
		ea.pActor->UpdateAllShaders();
	}
}

vl::Texture* EffectPipeline::render( vl::Texture* inTexture )
{
	VL_CHECK( inTexture );
	if ( lEffectActors.empty() )
	{
		return inTexture;
	}

	float currTime = vl::Time::currentTime();
	float deltaTime = currTime - prevRenderTime;
	prevRenderTime = currTime;

	int FBORenderID = 1;
	int FBOPreviousID = 0;
	int i = 0;

	for ( auto it = lEffectActors.begin(); it != lEffectActors.end(); ++it )
	{
		auto effect = it->pEffect.get();
		if ( !effect->Enable() )
		{
			continue;
		}
		auto actor = it->pActor.get();
		// вначале свап, потом взятие, иначе не тот порядок
		std::swap( FBORenderID, FBOPreviousID );
		auto& currFBO = pFBO[FBORenderID];
		auto& prevFBO = pFBO[FBOPreviousID];

		currFBO->ClearActors();
		currFBO->AddActor( actor );
		// устанавливаем пред. текстуру в качестве входной в 0 семпл
		actor->SetTexture( i++ ? prevFBO->GetRenderTexture() : inTexture );
		// сообщаем эффекту, что его рендят, чтобы он сделал, что ему требуется
		effect->preRenderUpdate( actor->GetShader(), GetWidth(), GetHeight(), deltaTime );

		currFBO->Render();
	}

	return ( i > 0 ) ? pFBO[FBORenderID]->GetRenderTexture() : inTexture;
}
}