#include "VST.h"

#include <nengine.h>
#include <editor/window/SDLWindow.h>

#include <editor/imgui/imguiWindow.h>
#include <editor/imgui/imguiSceneWindow.h>
#include <editor/imgui/imguiTextEditor.h>

using namespace ns::editor;


namespace vst
{



VST* VST::g_vst = nullptr;

void SceneRenderTargetResizeEvent::execute()
{
	VST::g_vst->initScene(resolution_);
}

void VST::initScene(const ns::Resolution& res) 
{
	sceneRenderTarget_ = ns::GlRenderTarget::gen(
		ns::GlRenderTarget::Spec{
			.colorFormat = {ns::ColorFormat::RGBA8},
			.depthFormat = ns::DepthFormat::DEPTH24_STENCIL8,
			.resolution = res
		}
	);
}

uint64_t VST::getSceneImage()
{
	if(VST::g_vst->sceneRenderTarget_ == nullptr) return 0u;
	return VST::g_vst->sceneRenderTarget_->getColorTexture();
}

void VST::preProcessEvent() 
{
	for(auto& event: events_)
	{
		event->execute();
	}
	events_.clear();
}

void VST::initEnd()
{
	g_vst = this;
	initScene(ns::Resolution{.width=appContext_.width, .height= appContext_.height});
}

void VST::draw()
{
	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, sceneRenderTarget_->getFbo()));
	auto rect = sceneRenderTarget_->getViewport();
	GLCHECK(glViewport(rect.x, rect.y, rect.w, rect.h));
	GLCHECK(glClearColor(1.0f, 1.0, 0, 1.0f));
	GLCHECK(glClear(GL_COLOR_BUFFER_BIT));

	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void VST::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiTextEditor>());
	sdlWindow_->addImguiModule(std::make_unique<ImguiSceneWindow>(ImguiSceneWindow::Context{
		.title="scene",
		.resolution = sceneRenderTarget_->getresolution(),
		.resizeCallback = [](const ns::Resolution& res){
			if(VST::g_vst)
			{
				VST::g_vst->pushEvent(std::make_unique<SceneRenderTargetResizeEvent>(res));
			}
		},
		.getImage = [](){
			return VST::g_vst->getSceneImage();
		}
	}));
}

}	 // namespace vst