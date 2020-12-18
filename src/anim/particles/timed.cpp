/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "timed.h"

namespace spectral {
namespace particle {


timed::timed( const timer &Timer, float LifeTime ) :
    BirthTime((float)Timer.GetTime()), LifeTime(LifeTime) {
}


bool timed::IsDead() const {
  return Age >= LifeTime;
}


void timed::Update( const timer &Timer ) {
  Age = (float)Timer.GetTime() - BirthTime;
}


} // End of 'particles' namespace
} // End of 'spectral' namespace
