/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <windows.h>

#include "../win/window_animation.h"
#include "timer.h"
#include "unit.h"
#include "render/render.h"

namespace spectral {


class animation : public window_animation {
public:
  animation( HINSTANCE hInstance = GetModuleHandle(NULL) );
  ~animation();
  void RenderFrame();
  animation & operator<<( unit *Unit );
  animation & operator<<( const std::pair<UINT, window::callback> &Callback );
  void Init() override;
  void Resize() override;
  void Paint( HDC hDC ) override;
  void Timer() override;
  void Idle() override;
  const timer & GetTimer() const;

private:
  unit_manager UnitManager;
  timer AnimTimer;
  render Render;
};


} // End of 'spectral' namespace
