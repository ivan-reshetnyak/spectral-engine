/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "animation.h"

namespace spectral {


// TODO: Add 'render' as parent (or field)
animation::animation( HINSTANCE hInstance ) :
    window_animation(hInstance) {
}


animation::~animation() {
}


void animation::Render() {
  AnimTimer.Update();
  AnimTimer.IncrFrameCount();

  // TODO: Add input update when it's done
  /*
  input::Response(IsActive);
  input::Scroll(window_animation::MouseWheel);
  */

  UnitManager.Update();

  // TODO: render::StartFrame();

  UnitManager.Render();

  /*
  TODO: render::EndFrame();
  TODO: render::CopyFrame();
  */
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


void animation::Resize() {
  // TODO: render::Resize();
}


void animation::Paint( HDC hDC ) {
  Render();
}


void animation::Timer() {
  Render();
}


void animation::Idle() {
}


} // End of 'spectral' namespace
