/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "../render/vertex.h"
#include "ui_button.h"

namespace spectral {
namespace ui {


class button_vertex : public vertex {
public:
  point<float> V0, V1;


  button_vertex() = default;


  button_vertex( const point<float> &V0, const point<float> &V1 ) : V0(V0), V1(V1) {
  }


  std::vector<location> GetLayout() override {
    std::vector<location> Layout;
    Layout.push_back(location({ 0, 2, GL_FLOAT, false, sizeof(button_vertex), OFFSET(button_vertex, V0) }));
    Layout.push_back(location({ 1, 2, GL_FLOAT, false, sizeof(button_vertex), OFFSET(button_vertex, V1) }));
    return Layout;
  }


  int GetSize() override {
    return sizeof(button_vertex);
  }
};



button::button( animation *Anim, const clickable &Base,
                std::shared_ptr<material> Material,
                const callback &Callback ) :
    clickable(Base), Callback(Callback), Material(Material) {
  Primitive.Set(Anim);
  Primitive.Set(std::shared_ptr<geometry>(
    new geometry(1, new button_vertex[1]{ button_vertex(BoundBox[0] * 2.f + point<float>(-1.f, -1.f),
                                                        BoundBox[1] * 2.f + point<float>(-1.f, -1.f)) },
                 1, { 0 })), Material);
}


button * button::Set( const callback &NewCallback ) {
  Callback = NewCallback;
}


button::~button() {
}


void button::Render() {
  glDepthMask(false);
  Primitive.Draw();
  glDepthMask(true);
}


void button::OnClick() {
  Callback();
}


} // End of 'ui' namespace
} // End of 'spectral' namespace
