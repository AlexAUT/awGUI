#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop

namespace aw::gui
{
template<typename Renderer> class Screen;
template<typename Renderer> class Window;

class NanovgRenderer
{
public:
  NanovgRenderer();
  ~NanovgRenderer();

  void beginRenderScreen(const Screen<NanovgRenderer>& screen, float width, float height, float pixelRatio);
  void endRenderScreen();

  void render(const Window<NanovgRenderer>&);
private:

private:
  NVGcontext* mContext;
  unsigned mFontRegular;
  unsigned mFontBold;
};
}
