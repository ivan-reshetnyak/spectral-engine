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
    Render(window::hWnd, window::Width, window::Height),
    Camera(0.5f, 1000,
           window::Width, window::Height,
           vec(0.0, 1.75, -100), vec(0.0, 0.0, 0.0), vec(0, 1, 0)),
    Mouse(window::Width, window::Height) {
}


animation::~animation() {
}


void animation::RenderFrame() {
  Timer.Update();
  Timer.IncrFrameCount();
  Mouse.Update();
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


void animation::OnButtonDown( bool IsDoubleClick, int X, int Y, unsigned Keys ) {
  if (Keys & MK_LBUTTON)
    Mouse.Press(mouse::button::LEFT);
  if (Keys & MK_MBUTTON)
    Mouse.Press(mouse::button::MIDDLE);
  if (Keys & MK_RBUTTON)
    Mouse.Press(mouse::button::RIGHT);
  Mouse.Move(point<int>(X, Y));
}


void animation::OnButtonUp( int X, int Y, unsigned Keys ) {
  if (!(Keys & MK_LBUTTON))
    Mouse.Release(mouse::button::LEFT);
  if (!(Keys & MK_MBUTTON))
    Mouse.Release(mouse::button::MIDDLE);
  if (!(Keys & MK_RBUTTON))
    Mouse.Release(mouse::button::RIGHT);
  Mouse.Move(point<int>(X, Y));
}


} // End of 'spectral' namespace
