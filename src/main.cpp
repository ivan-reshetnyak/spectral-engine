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
  Anim << new units::triangle(&Anim, { 0,  1, 0}, { 1, -1, 0}, {-1, -1, 0});

  Anim.Run();

  return 0;
}
