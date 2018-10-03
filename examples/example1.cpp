#include <iostream>

#include <aw/engine/engine.hpp>
#include <aw/utils/log.hpp>

#include <aw/engine/runtime/state.hpp>

#include <aw/opengl/opengl.hpp>

#include <nanovg/nanovg.h>

#ifndef NANOVG_GL3_IMPLEMENTATION
#define NANOVG_GL3_IMPLEMENTATION
#endif
#include <nanovg/nanovg_gl.h>

#include <cassert>

class ExampleState : public aw::State
{
public:
  ExampleState(aw::Engine& engine) : aw::State(engine.getStateMachine()), mEngine(engine)
  {
    mContext = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    assert(mContext);

    mListenerId = mEngine.getWindow().registerEventListener([this](auto event) { processEvent(event); });

    auto font = nvgCreateFont(mContext, "sans-bold", "examples/Roboto-Regular.ttf");
    LogTemp() << "FOnt: " << font;
  }

  ~ExampleState()
  {
    mEngine.getWindow().unregisterEventListener(mListenerId);
  }

  void update(float delta) override
  {
    if (delta > 10000)
      std::cout << "Unused";
  }

  void processEvent(aw::WindowEvent event)
  {
    if (event.type == aw::WindowEvent::Closed)
      mEngine.terminate();
    if (event.type == aw::WindowEvent::KeyReleased)
    {
      if (event.key.code == sf::Keyboard::Escape)
        mEngine.terminate();
    }
  }
  void drawWindow(NVGcontext* vg, const char* title, float x, float y, float w, float h)
  {
    float cornerRadius = 3.0f;
    NVGpaint shadowPaint;
    NVGpaint headerPaint;

    nvgSave(vg);
    //	nvgClearState(vg);

    // Window
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x, y, w, h, cornerRadius);
    nvgFillColor(vg, nvgRGBA(28, 30, 34, 192));
    //	nvgFillColor(vg, nvgRGBA(0,0,0,128));
    nvgFill(vg);

    // Drop shadow
    shadowPaint = nvgBoxGradient(vg, x, y + 2, w, h, cornerRadius * 2, 10, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
    nvgBeginPath(vg);
    nvgRect(vg, x - 10, y - 10, w + 20, h + 30);
    nvgRoundedRect(vg, x, y, w, h, cornerRadius);
    nvgPathWinding(vg, NVG_HOLE);
    nvgFillPaint(vg, shadowPaint);
    nvgFill(vg);

    // Header
    headerPaint = nvgLinearGradient(vg, x, y, x, y + 15, nvgRGBA(255, 255, 255, 8), nvgRGBA(0, 0, 0, 16));
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x + 1, y + 1, w - 2, 30, cornerRadius - 1);
    nvgFillPaint(vg, headerPaint);
    nvgFill(vg);
    nvgBeginPath(vg);
    nvgMoveTo(vg, x + 0.5f, y + 0.5f + 30);
    nvgLineTo(vg, x + 0.5f + w - 1, y + 0.5f + 30);
    nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 32));
    nvgStroke(vg);

    nvgFontSize(vg, 18.0f);
    nvgFontFace(vg, "sans-bold");
    nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

    nvgFontBlur(vg, 2);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));
    nvgText(vg, x + w / 2, y + 16 + 1, title, NULL);

    nvgFontBlur(vg, 0);
    nvgFillColor(vg, nvgRGBA(220, 220, 220, 160));
    nvgText(vg, x + w / 2, y + 16, title, NULL);

    nvgRestore(vg);
  }

  void render() override
  {
#ifdef AW_USE_OPENGL
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#endif
    float width = mEngine.getWindow().getSize().x;
    float height = mEngine.getWindow().getSize().y;
    nvgBeginFrame(mContext, width, height, 1.0f);

    drawWindow(mContext, "Hallo Welt", 100, 100, 200, 150);

    nvgEndFrame(mContext);
  }

private:
private:
  aw::Engine& mEngine;
  NVGcontext* mContext{nullptr};
  unsigned mListenerId;
};

int main()
{
  aw::LOG_INITIALIZE(aw::log::Debug, aw::log::Error);
  aw::Engine engine;
  engine.getStateMachine().pushState(std::make_shared<ExampleState>(engine));

  return engine.run();
}
