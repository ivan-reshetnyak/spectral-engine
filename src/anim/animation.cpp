/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "animation.h"

namespace spectral {


animation::animation( HINSTANCE hInstance ) :
    window(hInstance, "AnimationWindowClass", "Animation window",
           true, 0 /* TODO: Add menu IDR_MENU1 */, true),
    Render(window::hWnd,
           window::Width,
           window::Height),
    Camera(0.001f, 500,
           window::Width, window::Height,
           vec(0.0, 0.0, 5.0), vec(0.0, 0.0, 0.0), vec(0, 1, 0)) {
}


animation::~animation() {
}


void animation::RenderFrame() {
  AnimTimer.Update();
  AnimTimer.IncrFrameCount();

  // TODO: Add input update when it's done
  /*
  input::Response(IsActive);
  input::Scroll(window_animation::MouseWheel);
  */

  UnitManager.Update();

  Render.StartFrame();

  UnitManager.Render();

  Render.EndFrame();
  Render.CopyFrame();
}


animation & animation::operator<<( unit *Unit ) {
  UnitManager << Unit;
  return *this;
}


animation & animation::operator<<( const std::pair<UINT, window::callback> &Callback ) {
  window::operator<<(Callback);
  return *this;
}


void animation::OnSize( unsigned, int NewWidth, int NewHeight ) {
  window::OnSize(0, NewWidth, NewHeight);
  Render.Resize();
  Camera.Set(Width, Height);
}


void animation::OnPaint() {
  RenderFrame();
}


const timer & animation::GetTimer() const {
  return AnimTimer;
}


} // End of 'spectral' namespace
