/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <windows.h>

#include "../win/window.h"
#include "camera.h"
#include "timer.h"
#include "unit.h"
#include "render/render.h"

namespace spectral {


class animation : public window {
public:
  camera Camera;
  matrix World;
  timer AnimTimer;

  animation( HINSTANCE hInstance = GetModuleHandle(NULL) );
  ~animation();
  void RenderFrame();
  animation & operator<<( unit *Unit );
  animation & operator<<( const std::pair<UINT, window::callback> &Callback );
  void OnSize( unsigned, int NewWidth, int NewHeight ) override;
  void OnPaint() override;
  // void OnTimer( int ID ) override;
  const timer & GetTimer() const;

private:
  unit_manager UnitManager;
  render Render;
};


} // End of 'spectral' namespace
