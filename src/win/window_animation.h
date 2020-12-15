/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "window.h"

namespace spectral {


class window_animation : public window {
public:
  window_animation( HINSTANCE hInst = GetModuleHandle(NULL) );
  void onDestroy() override;
};


} // End of 'spectral' namespace
