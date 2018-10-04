#pragma once

#include <aw/utils/math/vector.hpp>

namespace aw::gui
{
class Widget
{
public:
  virtual ~Widget() = default;

  void setPreferedSize(Vec2 size) { mPreferedSize = size; invalidateLayout(); }

  Vec2 getSize() const { return mSize; }
  Vec2 getPreferedSize() const { return mPreferedSize; }
  Vec2 getLocalPosition() const { return mLocalPosition; }
  Vec2 getGlobalPosition() const { return mGlobalPosition; }

protected:
  //Should be called by the parent widget, user can onlz set the preferedSize
  void setSize(Vec2 size) { mSize = size; }

private:
  virtual void childChangedLayout(Widget* child);
  virtual void invalidateLayout() { if(mParent) mParent->childChangedLayout(this); }

private:
  Widget* mParent{nullptr};

  Vec2 mPreferedSize{0.f};
  Vec2 mSize{0.f};

  Vec2 mLocalPosition{0.f};
  Vec2 mGlobalPosition{0.f};
};
}
