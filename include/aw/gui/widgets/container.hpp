#pragma once

#include <aw/gui/widgets/widget.hpp>

#include <vector>

namespace aw::gui
{
class Container : public Widget
{
public:
  using ChildVector = std::vector<Widget*>;
public:
  virtual ~Container() = default;

  const ChildVector& getChildren() const; 

private:

private:
  ChildVector mChildren; 
};
}
