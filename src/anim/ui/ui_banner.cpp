/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "../render/vertex.h"
#include "ui_banner.h"

#include "util/memhooks.h"

namespace spectral {
namespace ui {


class banner_vertex : public vertex {
public:
  point<float> V0, V1;


  banner_vertex() = default;


  banner_vertex( const point<float> &V0, const point<float> &V1 ) : V0(V0), V1(V1) {
  }


  std::vector<location> GetLayout() override {
    std::vector<location> Layout;
    Layout.push_back(location({ 0, 2, GL_FLOAT, false, sizeof(banner_vertex), OFFSET(banner_vertex, V0) }));
    Layout.push_back(location({ 1, 2, GL_FLOAT, false, sizeof(banner_vertex), OFFSET(banner_vertex, V1) }));
    return Layout;
  }


  int GetSize() override {
    return sizeof(banner_vertex);
  }
};


banner::banner( animation *Anim, const rect<float> &BoundBox,
                std::shared_ptr<material> Material ) :
    bounded(BoundBox), Material(Material) {
  Primitive.Set(Anim);
  Primitive.Set(std::shared_ptr<geometry>(
    new geometry(1, new banner_vertex[1]{ banner_vertex(BoundBox[0] * 2.f + point<float>(-1.f, -1.f),
                                                        BoundBox[1] * 2.f + point<float>(-1.f, -1.f)) },
                 1, { 0 })), Material);
}


void banner::Render() {
  glDepthMask(false);
  Primitive.Draw();
  glDepthMask(true);
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
