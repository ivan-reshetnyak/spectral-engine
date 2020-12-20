/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "mouse.h"

namespace spectral {


mouse::mouse() : Buttons({state::UP, state::UP, state::UP}), Previous({state::UP, state::UP, state::UP}) {
}


void mouse::Update() {
  Previous = Buttons;
}

void mouse::Press( button Button ) {
  if (Previous[(int)Button] == state::UP)
    Buttons[(int)Button] = state::CLICK;
  else
    Buttons[(int)Button] = state::DOWN;
}


void mouse::Release( button Button ) {
  Buttons[(int)Button] = state::UP;
}


void mouse::Move( int NewX, int NewY ) {
  X = NewX;
  Y = NewY;
}


mouse::state mouse::operator[]( button Button ) const {
  return Buttons[(int)Button];
}


} // End of 'spectral' namespace
