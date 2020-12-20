/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <windows.h>

#include "../win/window.h"
#include "control/mouse.h"
#include "render/render.h"
#include "camera.h"
#include "timer.h"
#include "unit.h"
#include "world.h"

namespace spectral {


class animation : public window {
public:
  camera Camera;
  mouse Mouse;
  timer Timer;
  world World;

  animation( HINSTANCE hInstance = GetModuleHandle(NULL) );
  ~animation();
  void RenderFrame();
  animation & operator<<( unit *Unit );
  animation & operator<<( const std::pair<UINT, window::callback> &Callback );
  void OnButtonDown( bool IsDoubleClick, int X, int Y, unsigned Keys ) override;
  void OnButtonUp( int X, int Y, unsigned Keys ) override;
  void OnPaint() override;
  void OnSize( unsigned, int NewWidth, int NewHeight ) override;

private:
  unit_manager UnitManager;
  render Render;
};


} // End of 'spectral' namespace
