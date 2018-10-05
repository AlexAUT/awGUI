#pragma once

#include <aw/gui/widgets/widget.hpp>

#include <vector>

namespace aw::gui
{
template<typename Renderer>
class Container : public Widget<Renderer>
{
public:
  using ChildVector = std::vector<typename Widget<Renderer>::SPtr>;
public:
  virtual ~Container() = default;

  const ChildVector& getChildren() const { return mChildren; }

  virtual void render(Renderer& renderer, Vec2 parentPosition) override;

  virtual bool handleLeftClick(Vec2 position) override;
  virtual bool handleRightClick(Vec2 position) override;
  virtual bool handleLeftRelease(Vec2 position) override;
  virtual bool handleRightRelease(Vec2 position) override;

  virtual bool handleMouseMove(Vec2 position) override;

protected:
  ChildVector mChildren; 
};

template<typename Renderer>
void Container<Renderer>::render(Renderer& renderer, Vec2 parentPosition)
{
  Widget<Renderer>::render(renderer, parentPosition);
  auto globalPos = this->getGlobalPosition();
  for(auto& child : mChildren)
    child->render(renderer, globalPos);
}

template<typename Renderer>
bool Container<Renderer>::handleLeftClick(Vec2 position)
{
  auto localPos = position - this->getRelativePosition();
  bool consumed = false;
  for(auto& child : mChildren)
    consumed = child->handleLeftClick(localPos) || consumed;

  return consumed;
}

template<typename Renderer>
bool Container<Renderer>::handleRightClick(Vec2 position)
{
  auto localPos = position - this->getRelativePosition();
  bool consumed = false;
  for(auto& child : mChildren)
    consumed = child->handleRightClick(localPos) || consumed;

  return consumed;
}

template<typename Renderer>
bool Container<Renderer>::handleLeftRelease(Vec2 position)
{
  auto localPos = position - this->getRelativePosition();
  bool consumed = false;
  for(auto& child : mChildren)
    consumed = child->handleLeftRelease(localPos) || consumed;

  return consumed;
}

template<typename Renderer>
bool Container<Renderer>::handleRightRelease(Vec2 position)
{
  auto localPos = position - this->getRelativePosition();
  bool consumed = false;
  for(auto& child : mChildren)
    consumed = child->handleRightRelease(localPos) || consumed;

  return consumed;
}


template<typename Renderer>
bool Container<Renderer>::handleMouseMove(Vec2 position)
{
  auto localPos = position - this->getRelativePosition();
  bool consumed = false;
  for(auto& child : mChildren)
    consumed = child->handleMouseMove(localPos) || consumed;

  return consumed;
}

}
