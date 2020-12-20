/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "unit.h"

namespace spectral {


class animation;  // Forward declaration


unit::unit( animation *Anim ) : Anim(Anim) {
}


unit::~unit() {
}


void unit::Update() {
}


void unit::Render() {
}


unit_manager::unit_manager() {
}


unit_manager::~unit_manager() {
  for (unit *Unit : Units)
    delete Unit;
}


unit_manager & unit_manager::operator<<( unit *NewUnit ) {
  Units.push_back(NewUnit);
  return *this;
}


unit_manager & unit_manager::Update() {
  for (unit *Unit : Units)
    Unit->Update();
  return *this;
}


unit_manager & unit_manager::Render() {
  for (unit *Unit : Units)
    Unit->Render();
  return *this;
}


} // End of 'spectral' namespace
