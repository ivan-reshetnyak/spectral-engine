/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <windows.h>

#include "timer.h"
#include "unit.h"
#include "../win/window_animation.h"

namespace spectral {


class animation : public window_animation {
public:
  animation( HINSTANCE hInstance = GetModuleHandle(NULL) );
  ~animation();
  void Render();
  animation & operator<<( unit *Unit );
  animation & operator<<( const std::pair<UINT, window::callback> &Callback );
  void Init() override;
  void Resize() override;
  void Paint( HDC hDC ) override;
  void Timer() override;
  void Idle() override;

private:
  unit_manager UnitManager;
  timer AnimTimer;
};


} // End of 'spectral' namespace
