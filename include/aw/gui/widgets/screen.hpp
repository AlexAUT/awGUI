#pragma once

#include <aw/gui/widgets/floatingContainer.hpp>

namespace aw::gui
{
template <typename Renderer>
class Screen : public FloatingContainer<Renderer>
{
public:
  using SPtr = std::shared_ptr<Screen>;

public:
  Screen(Vec2 size, Vec2 relativePos = Vec2{0.f});

};

template <typename Renderer>
Screen<Renderer>::Screen(Vec2 size, Vec2 relativePos)
{
  this->setSize(size);
  this->setRelativePosition(relativePos);
}
}
