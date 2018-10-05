#pragma once

#include <aw/gui/widgets/screen.hpp>

#include <aw/utils/math/vector.hpp>
  
#include <memory>
#include <vector>

namespace aw::gui
{
template<typename Renderer>
class GUI
{
public:
  using ScreenImpl = Screen<Renderer>;  

  typename ScreenImpl::SPtr addScreen(Vec2 size, Vec2 position = Vec2{0.f});

  void update(float delta);
  void render(float windowWith, float windowHeight, float pixelRatio);

  bool handleLeftClick(Vec2 position);
  bool handleRightClick(Vec2 position);
  bool handleLeftRelease(Vec2 position);
  bool handleRightRelease(Vec2 position);

  bool handleMouseMove(Vec2 position);

private:

private:
  Renderer mRenderer;
  
  std::vector<typename ScreenImpl::SPtr> mScreens;
};

template<typename Renderer>
auto GUI<Renderer>::addScreen(Vec2 size, Vec2 position) -> typename GUI::ScreenImpl::SPtr
{
  mScreens.push_back(std::make_shared<ScreenImpl>(size, position));
  return mScreens.back();
}

template<typename Renderer>
void GUI<Renderer>::update(float delta)
{
  for(auto& screen : mScreens)
    screen->update(delta);
}

template<typename Renderer>
void GUI<Renderer>::render(float windowWidth, float windowHeight, float pixelRatio)
{
  for(auto& screen : mScreens)
  {
    mRenderer.beginRenderScreen(*screen, windowWidth, windowHeight, pixelRatio);
    screen->render(mRenderer, {0.f, 0.f});
    mRenderer.endRenderScreen();
  }
}

template<typename Renderer>
bool GUI<Renderer>::handleLeftClick(Vec2 position)
{
  for(auto& screen : mScreens)
    screen->handleLeftClick(position);
}

template<typename Renderer>
bool GUI<Renderer>::handleRightClick(Vec2 position)
{
  for(auto& screen : mScreens)
    screen->handleRightClick  (position);
}

template<typename Renderer>
bool GUI<Renderer>::handleLeftRelease(Vec2 position)
{
  for(auto& screen : mScreens)
    screen->handleLeftRelease(position);
}

template<typename Renderer>
bool GUI<Renderer>::handleRightRelease(Vec2 position)
{
  for(auto& screen : mScreens)
    screen->handleRightRelease(position);
}

template<typename Renderer>
bool GUI<Renderer>::handleMouseMove(Vec2 position)
{
  for(auto& screen : mScreens)
    screen->handleMouseMove(position);
}

}
