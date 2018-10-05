#pragma once

#include <aw/utils/math/vector.hpp>

#include <memory>

namespace aw::gui
{
template<typename Renderer>
class Widget
{
public:
  using SPtr = std::shared_ptr<Widget>;

  template<template <typename _> class WidgetType, typename... Params>
  static std::shared_ptr<WidgetType<Renderer>> create(Params&&... params)
  {
    return std::make_shared<WidgetType<Renderer>>(std::forward<Params>(params)...);
  }

public:
  virtual ~Widget() = default;

  void setPreferedSize(Vec2 size) { mPreferedSize = size; invalidateLayout(); }

  Vec2 getSize() const { return mSize; }
  Vec2 getPreferedSize() const { return mPreferedSize; }
  Vec2 getRelativePosition() const { return mRelativePosition; }
  Vec2 getGlobalPosition() const { return mGlobalPosition; }

  virtual void update(float delta) {};
  virtual void render(Renderer& renderer, Vec2 parentPosition) { mGlobalPosition = parentPosition + mRelativePosition; }

  virtual bool handleLeftClick(Vec2 position) { (void)position; return false; }
  virtual bool handleRightClick(Vec2 position) { (void)position; return false; }
  virtual bool handleLeftRelease(Vec2 position) { (void)position; return false; }
  virtual bool handleRightRelease(Vec2 position) { (void)position; return false; }

  virtual bool handleMouseMove(Vec2 position);

public:
  //Should be called by the parent widget, user should only set the preferedSize
  void setSize(Vec2 size) { mSize = size; }
  void setRelativePosition(Vec2 pos) { mRelativePosition = pos; }

private:
  virtual void childChangedLayout(Widget* child) {}
  virtual void invalidateLayout() { if(mParent) mParent->childChangedLayout(this); }

private:
  Widget* mParent{nullptr};

  Vec2 mPreferedSize{0.f};
  Vec2 mSize{0.f};

  Vec2 mRelativePosition{0.f};
  Vec2 mGlobalPosition{0.f};
};
}
