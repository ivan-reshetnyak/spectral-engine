/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "particle_timed.h"

namespace spectral {
namespace particle {


timed::timed( const timer &Timer, float LifeTime ) :
    BirthTime(Timer.Time), LifeTime(LifeTime), Age(0) {
}


timed::timed( const timed &&Other ) :
    BirthTime(Other.BirthTime), LifeTime(Other.LifeTime), Age(Other.Age) {
}


bool timed::IsDead() const {
  return Age >= LifeTime;
}


void timed::Update( const timer &Timer ) {
  Age = Timer.Time - BirthTime;
}


timed & timed::operator=( const timed &&Other ) {
  BirthTime = Other.BirthTime;
  LifeTime = Other.LifeTime;
  Age = Other.Age;
  return *this;
}


} // End of 'particle' namespace
} // End of 'spectral' namespace
