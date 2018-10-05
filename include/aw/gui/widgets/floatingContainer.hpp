#pragma once

#include <aw/gui/widgets/container.hpp>

#include <aw/utils/math/vector.hpp>

#include <vector>

namespace aw::gui
{
template<typename Renderer>
class FloatingContainer : public Container<Renderer>
{
public:
  struct Slot
  {
    Vec2 size;
    Vec2 relativePos;
  };

public:
  virtual ~FloatingContainer() = default;

  void addChild(typename Widget<Renderer>::SPtr child, Slot slot);
private:

private:
  std::vector<Slot> mSlots;
};

template<typename Renderer>
void FloatingContainer<Renderer>::addChild(typename Widget<Renderer>::SPtr child, Slot slot)
{
  this->mChildren.push_back(child);
  this->mChildren.back()->template setSize(slot.size);
  this->mChildren.back()->template setRelativePosition(slot.relativePos);
}
}
