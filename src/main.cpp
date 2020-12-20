/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include <windows.h>

#include "util/memhooks.h"
#include "anim/animation.h"
#include "anim/units/unit_fireworks.h"
#include "anim/units/unit_triangle.h"
#include "anim/units/unit_signal.h"

using namespace spectral;

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow ) {
  animation Anim;
  float Scale = 1;
  Anim
    //<< new units::signal(&Anim, vec(0, 0, 0) * Scale, vec(0, 0.3f, 0) * Scale)
    << new units::fireworks(&Anim);

  Anim.Run();

  return 0;
}
