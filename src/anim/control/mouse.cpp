/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "mouse.h"

namespace spectral {


mouse::mouse( const int &Width, const int &Height ) :
    Width(Width), Height(Height),
    Buttons({state::UP, state::UP, state::UP}),
    Previous({state::UP, state::UP, state::UP}) {
}


void mouse::Update() {
  for (unsigned i = 0; i < Buttons.size(); ++i) {
    if (Buttons[i] == state::DOWN && Previous[i] == state::UP)
      Buttons[i] = state::CLICK;
    else if (Buttons[i] == state::CLICK)
      Buttons[i] = state::DOWN;
  }
  Previous = Buttons;
}

void mouse::Press( button Button ) {
  Buttons[(int)Button] = state::DOWN;
}


void mouse::Release( button Button ) {
  Buttons[(int)Button] = state::UP;
}


void mouse::Move( const point<int> &NewCoords ) {
  Coords = NewCoords;
}


mouse::state mouse::operator[]( button Button ) const {
  return Buttons[(int)Button];
}


point<int> mouse::GetCoordsAbsolute() const {
  return Coords;
}


point<float> mouse::GetCoordsRelative() const {
  return { Coords.X / (float)Width, 1.0f - Coords.Y / (float)Height };
}


} // End of 'spectral' namespace
