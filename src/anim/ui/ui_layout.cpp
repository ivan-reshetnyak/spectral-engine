/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "ui_layout.h"

namespace spectral {
namespace ui {


void layout::Update() {
  for (auto &Element : Elements)
    Element->Update();
}


void layout::Render() {
  for (auto &Element : Elements)
    Element->Render();
}


layout * layout::Add( std::shared_ptr<element> NewElement ) {
  Elements.push_back(NewElement);
  return this;
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
