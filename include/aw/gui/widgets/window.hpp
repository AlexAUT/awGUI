#pragma once

#include <aw/gui/widgets/floatingContainer.hpp>

#include <string>

namespace aw::gui
{
template<typename Renderer>
class Window : public Widget<Renderer>
{
public:
  Window(std::string title) : mTitle(std::move(title)) {}

  void render(Renderer& renderer, Vec2 parentPosition) override final;

  void setTitle(std::string title) { mTitle = std::move(title); }
  const std::string& getTitle() const { return mTitle; }

  bool handleLeftClick(Vec2 pos) override;
  bool handleLeftRelease(Vec2 pos) override;
  bool handleMouseMove(Vec2 pos) override;
private:

private:
  std::string mTitle; 

  bool mDrag{false};
  Vec2 mDragOffset;
};

template<typename Renderer>
void Window<Renderer>::render(Renderer& renderer, Vec2 parentPosition)
{
  Widget<Renderer>::render(renderer, parentPosition);
  renderer.render(*this);
}

template<typename Renderer>
bool Window<Renderer>::handleLeftClick(Vec2 pos)
{
  auto relPos = this->getRelativePosition();
  auto size = this->getSize();
  if(pos.x >= relPos.x && pos.x < (relPos.x + size.x))
  {
    if(pos.y >= relPos.y && pos.y < (relPos.y + 30))
    {
      mDrag = true;
      mDragOffset = pos - relPos;
      return true;
    }
  }
  return false;
}

template<typename Renderer>
bool Window<Renderer>::handleLeftRelease(Vec2 pos)
{
  if(mDrag)
  {
    handleMouseMove(pos);
    mDrag = false;
    return true;
  }
  return false;
}

template<typename Renderer>
bool Window<Renderer>::handleMouseMove(Vec2 pos)
{
  if(mDrag)
  {
    this->setRelativePosition(pos - mDragOffset); 
    return true;
  }
  return false;
}
}
