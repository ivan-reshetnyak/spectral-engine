/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "ui_hideable.h"

namespace spectral {
namespace ui {


hideable::hideable( std::shared_ptr<element> Base, bool Hidden ) :
    Base(Base), Hidden(Hidden) {
}


void hideable::Update() {
  if (!IsHidden())
    Base->Update();
}


void hideable::Render() {
  if (!IsHidden())
    Base->Render();
}


bool hideable::IsHidden() const {
  return Hidden;
}


void hideable::Hide() {
  Hidden = true;
}


void hideable::Show() {
  Hidden = false;
}


void hideable::Toggle() {
  Hidden = !Hidden;
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
