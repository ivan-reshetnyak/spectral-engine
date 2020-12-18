/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include <windows.h>

#include "util/memhooks.h"
#include "anim/animation.h"
#include "anim/units/triangle.h"

using namespace spectral;

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow ) {
  animation Anim;
  float Scale = 1;
  Anim << new units::triangle(&Anim, vec(0, 1, 0) * Scale, vec(1, -1, 0) * Scale, vec(-1, -1, 0 * Scale));

  Anim.Run();

  return 0;
}
