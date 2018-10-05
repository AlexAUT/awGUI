#include <aw/gui/renderers/nanovgRenderer.hpp>

#include <aw/utils/log.hpp>

#include "gl.hpp"
#include <nanovg_gl.h>

#include <aw/gui/widgets/window.hpp>

#include "nanovgDrawHelper.hpp"

DEFINE_LOG_CATEGORY(Error, aw::log::Error, "Nanovg Renderer")

namespace aw::gui
{
NanovgRenderer::NanovgRenderer() :
  mContext(nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG))
{
  aw::LOG_INITIALIZE();
  if(!mContext)
    LogError() << "Failed to create nanovg context!";

  mFontRegular = nvgCreateFont(mContext, "sans", "assets/Roboto-Regular.ttf");
  mFontBold = nvgCreateFont(mContext, "sans-bold", "assets/Roboto-Regular.ttf");
}

NanovgRenderer::~NanovgRenderer()
{
  if(mContext)
    nvgDeleteGL3(mContext);
}

void NanovgRenderer::beginRenderScreen(const Screen<NanovgRenderer>& screen, float width, float height, float pixelRatio)
{
  (void)screen;
  nvgBeginFrame(mContext, width, height, pixelRatio); 
}

void NanovgRenderer::endRenderScreen()
{
  nvgEndFrame(mContext);
}

void NanovgRenderer::render(const Window<NanovgRenderer>& window)
{
  auto pos = window.getGlobalPosition();
  auto size = window.getSize();
  auto* title = window.getTitle().c_str();
  drawWindow(mContext, title, pos.x, pos.y, size.x, size.y);
}

}
