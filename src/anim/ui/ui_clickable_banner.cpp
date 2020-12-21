/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "../render/vertex.h"
#include "ui_clickable_banner.h"

namespace spectral {
namespace ui {


clickable_banner::clickable_banner( animation *Anim, const rect<float> &BoundBox,
                std::shared_ptr<material> Material,
                const callback &Callback ) :
    button(Anim->Mouse, BoundBox, Callback), Banner(Anim, BoundBox, Material) {
}


void clickable_banner::Render() {
  Banner.Render();
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
