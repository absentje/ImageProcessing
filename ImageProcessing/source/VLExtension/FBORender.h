#pragma once
#include <vlCore/Object.hpp>
#include <vlCore/vlnamespace.hpp>
#include <vlCore/Vector4.hpp>
#include <string>
#include <map>

namespace vl
{
	class Rendering;
	class Camera;
	class FramebufferObject;
	class SceneManagerActorTree;
	class SceneManager;
	class Texture;
	class Image;
    class OpenGLContext;
}

namespace VLExtension
{
class Actor;

class FBORender: public vl::Object
{
	VL_INSTRUMENT_CLASS( FBORender, vl::Object );
public:
	FBORender();
	~FBORender();

	void		 SetTextureFormat( vl::ETextureFormat tex_format, vl::EAttachmentPoint ap = vl::AP_COLOR_ATTACHMENT0 );
	vl::Texture* GetRenderTexture( vl::EAttachmentPoint ap = vl::AP_COLOR_ATTACHMENT0 );

	void		Render();
	void		Render( vl::Image& saveScreen );

	void		SetCamera( vl::Camera* camera );
	void		SetClearColor( const vl::vec4& clr );

	void		AddSceneManager( vl::SceneManager* sceneManager );
	void		ClearAdditionalScenes();

	void		AddActor( Actor* actor );
	void		ClearActors();

	int			GetWidth() const;
	int			GetHeight() const;

	void		Resize( int width, int height );

	static vl::OpenGLContext* gl_context;

private:
	void	createFBO( int w, int h );
	void	createTexture( vl::ETextureFormat tex_format, vl::EAttachmentPoint ap );
	void	createRenderingAndScene();
	void	setDrawBuffers();
	void	resizeCamera();

	vl::ref<vl::Rendering>		pRendering;
	vl::ref<vl::FramebufferObject>		pFBO;
	vl::ref<vl::SceneManagerActorTree>	pScene;
	std::map<vl::EAttachmentPoint, vl::ref<vl::Texture>>	mAttachTextures;
	int		fboWidth;
	int		fboHeight;
};
}