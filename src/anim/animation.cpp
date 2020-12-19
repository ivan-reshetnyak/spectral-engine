/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "animation.h"

namespace spectral {


animation::animation( HINSTANCE hInstance ) :
    window_animation(hInstance),
    Render(window_animation::hWnd,
           window_animation::Width,
           window_animation::Height),
    Camera(0.001f, 500,
           window_animation::Width, window_animation::Height,
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
  window_animation::operator<<(Callback);
  return *this;
}


void animation::Init() {
}


void animation::Resize( int NewWidth, int NewHeight ) {
  window_animation::Resize(NewWidth, NewHeight);
  Render.Resize();
  Camera.Set(Width, Height);
}


void animation::Paint( HDC hDC ) {
  RenderFrame();
}


void animation::Timer() {
  RenderFrame();
}


void animation::Idle() {
}


const timer & animation::GetTimer() const {
  return AnimTimer;
}


} // End of 'spectral' namespace
