/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "anim/animation.h"
#include "unit_fireworks.h"

#include <windows.h>

using namespace spectral;

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow ) {
  animation Anim;
  float Scale = 1;
  Anim << new units::fireworks(&Anim);

  Anim.Run();

  return 0;
}
