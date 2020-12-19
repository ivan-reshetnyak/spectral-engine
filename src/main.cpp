/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include <windows.h>

#include "util/memhooks.h"
#include "anim/animation.h"
#include "anim/units/unit_triangle.h"
#include "anim/units/unit_signal.h"

using namespace spectral;

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow ) {
  animation Anim;
  float Scale = 1;
  Anim
    // << new units::triangle(&Anim, vec(0, 1, 0) * Scale, vec(1, -1, 0) * Scale, vec(-1, -1, 0) * Scale)
    << new units::triangle(&Anim, vec(-10, 0, -20) * Scale, vec(10, 0, -20) * Scale, vec(0, 0, 20) * Scale)
    << new units::triangle(&Anim, vec(0, 0.1f, 0) * Scale, vec(1, 0.1f, 0) * Scale, vec(0, 1.1f, 0) * Scale)
    << new units::triangle(&Anim, vec(0, 0.1f, 0.5) * Scale, vec(1, 0.1f, 0.5) * Scale, vec(0, 1.1f, 0.5) * Scale)
    << new units::triangle(&Anim, vec(0, 0.1f, 1.5) * Scale, vec(1, 0.1f, 1.5) * Scale, vec(0, 1.1f, 1.5) * Scale)
    << new units::triangle(&Anim, vec(0, 0.1f, 2.5) * Scale, vec(1, 0.1f, 2.5) * Scale, vec(0, 1.1f, 2.5) * Scale)
    // << new units::triangle(&Anim, vec(0, 1, 0) * Scale, vec(1, -1, 0) * Scale, vec(-1, -1, 0 * Scale))
    << new units::signal(&Anim, vec(0, 0, 0) * Scale, vec(0, 0.3f, 0) * Scale);

  Anim.Run();

  return 0;
}
