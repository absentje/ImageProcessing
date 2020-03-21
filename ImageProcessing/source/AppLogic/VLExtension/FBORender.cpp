#include "FBORender.h"
#include <vlGraphics/ReadPixels.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/Camera.hpp>
#include <vlGraphics/FramebufferObject.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/Texture.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <Actor.h>

FBORender::FBORender(vl::OpenGLContext* context) : gl_context(context)
{
	fboWidth = 0;
	fboHeight = 0;

    static const int START_W = 512;
    static const int START_H = 512;

	createRenderingAndScene();
    createFBO(START_W, START_H);
	createTexture(vl::ETextureFormat::TF_RGBA, vl::EAttachmentPoint::AP_COLOR_ATTACHMENT0);
	resizeCamera();
}

FBORender::~FBORender()
{
    VL_CHECK(gl_context)
	gl_context->destroyFramebufferObject(pFBO.get());
}

void	FBORender::createRenderingAndScene()
{
	pRendering = new vl::Rendering;
    pScene = new vl::SceneManagerActorTree;
	pScene->setCullingEnabled(false);
	pRendering->sceneManagers()->push_back(pScene.get());
}

void	FBORender::SetTextureFormat(vl::ETextureFormat tex_format, vl::EAttachmentPoint ap)
{
	auto af = mAttachTextures.find(ap);
	if (af != mAttachTextures.end())
	{
		if (af->second->internalFormat() == tex_format)
			return;
	}
	createTexture(tex_format, ap);

	setDrawBuffers();
}

vl::Texture*	FBORender::GetRenderTexture(vl::EAttachmentPoint ap)
{
	return mAttachTextures[ap].get();
}

void	FBORender::SetCamera(vl::Camera* camera)
{
    VL_CHECK(camera)
	pRendering->setCamera(camera);
	resizeCamera();
}

void	FBORender::SetClearColor(const vl::vec4& clr)
{
	pRendering->camera()->viewport()->setClearColor(clr);
}

void	FBORender::Render()
{
	pRendering->render();
}
void	FBORender::Render(vl::Image& saveScreen)
{
	vl::ref<vl::ReadPixels> rp = new vl::ReadPixels;
	rp->setup(0, 0, 
		pRendering->camera()->viewport()->width(), 
		pRendering->camera()->viewport()->height(),
		vl::RDB_COLOR_ATTACHMENT0, false);
	pRendering->onFinishedCallbacks()->push_back(rp.get());
	rp->setRemoveAfterCall(true);
	rp->setImage(&saveScreen);
	Render();
}

void	FBORender::AddSceneManager(vl::SceneManager* sceneManager)
{
    VL_CHECK(sceneManager)
	pRendering->sceneManagers()->push_back(sceneManager);
}
void	FBORender::ClearAdditionalScenes()
{
	pRendering->sceneManagers()->clear();
	if (pScene)
	{
		pRendering->sceneManagers()->push_back(pScene.get());
	}
}

void	FBORender::AddActor(Actor* actor)
{
    pScene->tree()->addActor(actor->VLActor());
}

void	FBORender::ClearActors()
{
	pScene->tree()->actors()->clear();
}

int		FBORender::GetWidth() const
{
	return fboWidth;
}

int		FBORender::GetHeight() const
{
	return fboHeight;
}

void	FBORender::createFBO(int w, int h)
{
	fboWidth = w;
	fboHeight = h;

	if (pFBO)
	{
		gl_context->destroyFramebufferObject(pFBO.get());
	}
	pFBO = gl_context->createFramebufferObject(w, h);

    auto fbo_depth_attachm = new vl::FBODepthBufferAttachment(vl::DBF_DEPTH_COMPONENT32);
	pFBO->addDepthAttachment(fbo_depth_attachm);

	pRendering->renderer()->setFramebuffer(pFBO.get());
}

void	FBORender::createTexture(vl::ETextureFormat tex_format, vl::EAttachmentPoint ap)
{
	// create texture
    vl::ref<vl::Texture> pRenderTexture = new vl::Texture(GetWidth(), GetHeight(), tex_format);
	pRenderTexture->getTexParameter()->setWrap(vl::ETexParamWrap::TPW_CLAMP_TO_EDGE);
	mAttachTextures[ap] = pRenderTexture;

	// check/remove prev fbo attachment
	auto af = pFBO->mFBOAttachments.find(ap);
	if (af != pFBO->mFBOAttachments.end())
	{
		pFBO->removeAttachment(ap);
	}
	
	auto textureAtata = new vl::FBOTexture2DAttachment(pRenderTexture.get(), 0, vl::T2DT_TEXTURE_2D);
	pFBO->addTextureAttachment(ap, textureAtata);
}

void	FBORender::setDrawBuffers()
{
	std::vector<vl::EReadDrawBuffer> buffs;
	for (auto& at : mAttachTextures)
	{
		vl::EReadDrawBuffer rdb = vl::RDB_COLOR_ATTACHMENT0;
		switch (at.first)
		{
		case vl::AP_COLOR_ATTACHMENT0: rdb = vl::RDB_COLOR_ATTACHMENT0; break;
		case vl::AP_COLOR_ATTACHMENT1: rdb = vl::RDB_COLOR_ATTACHMENT1; break;
		case vl::AP_COLOR_ATTACHMENT2: rdb = vl::RDB_COLOR_ATTACHMENT2; break;
		case vl::AP_COLOR_ATTACHMENT3: rdb = vl::RDB_COLOR_ATTACHMENT3; break;
		case vl::AP_COLOR_ATTACHMENT4: rdb = vl::RDB_COLOR_ATTACHMENT4; break;
		case vl::AP_COLOR_ATTACHMENT5: rdb = vl::RDB_COLOR_ATTACHMENT5; break;
		case vl::AP_COLOR_ATTACHMENT6: rdb = vl::RDB_COLOR_ATTACHMENT6; break;
		case vl::AP_COLOR_ATTACHMENT7: rdb = vl::RDB_COLOR_ATTACHMENT7; break;
		case vl::AP_COLOR_ATTACHMENT8: rdb = vl::RDB_COLOR_ATTACHMENT8; break;
		case vl::AP_COLOR_ATTACHMENT9: rdb = vl::RDB_COLOR_ATTACHMENT9; break;
		case vl::AP_COLOR_ATTACHMENT10: rdb = vl::RDB_COLOR_ATTACHMENT10; break;
		case vl::AP_COLOR_ATTACHMENT11: rdb = vl::RDB_COLOR_ATTACHMENT11; break;
		case vl::AP_COLOR_ATTACHMENT12: rdb = vl::RDB_COLOR_ATTACHMENT12; break;
		case vl::AP_COLOR_ATTACHMENT13: rdb = vl::RDB_COLOR_ATTACHMENT13; break;
		case vl::AP_COLOR_ATTACHMENT14: rdb = vl::RDB_COLOR_ATTACHMENT14; break;
		case vl::AP_COLOR_ATTACHMENT15: rdb = vl::RDB_COLOR_ATTACHMENT15; break;
        default: VL_TRAP() break;
		}
		buffs.push_back(rdb);
	}
	pFBO->setDrawBuffers(buffs);
}

void	FBORender::resizeCamera()
{
	pRendering->camera()->viewport()->setWidth(fboWidth);
	pRendering->camera()->viewport()->setHeight(fboHeight);

	// перерасчитываем вью-матрицы камеры
	if (pRendering->camera()->projectionMatrixType() == vl::EProjectionMatrixType::PMT_OrthographicProjection)
		pRendering->camera()->setProjectionOrtho();
	else
		pRendering->camera()->setProjectionPerspective();
}

void	FBORender::Resize(int width, int height)
{
    VL_CHECK(width > 0)
    VL_CHECK(height > 0)
	if (width != fboWidth || height != fboHeight)
	{
		if (width > fboWidth || height > fboHeight)
		{// надо пересоздавать фбо, когда размер больше стартового
			createFBO(width, height);
			setDrawBuffers();
		}
		else
		{
			pFBO->setWidth(width);
			pFBO->setHeight(height);
		}
		fboWidth = width;
		fboHeight = height;

		for (auto& att : mAttachTextures)
		{
			createTexture(att.second->internalFormat(), att.first);
		}

		resizeCamera();
	}
}
