/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "anim/render/resource/tex/tex_png.h"
#include "anim/render/vertex.h"
#include "unit_nums.h"

namespace spectral {
namespace units {


class nums_vertex : public vertex {
public:
  point<float> V0, V1;
  float Value;

  nums_vertex() = default;


  nums_vertex( const point<float> &V0, const point<float> &V1, float Value ) : V0(V0), V1(V1), Value(Value) {
  }


  std::vector<location> GetLayout() override {
    std::vector<location> Layout;
    Layout.push_back(location({ 0, 2, GL_FLOAT, false, sizeof(nums_vertex), OFFSET(nums_vertex, V0) }));
    Layout.push_back(location({ 1, 2, GL_FLOAT, false, sizeof(nums_vertex), OFFSET(nums_vertex, V1) }));
    Layout.push_back(location({ 2, 1, GL_FLOAT, false, sizeof(nums_vertex), OFFSET(nums_vertex, Value) }));
    return Layout;
  }


  int GetSize() override {
    return sizeof(nums_vertex);
  }
};


nums::nums( animation *Anim, int What, const rect<float> &Where ) :
    unit(Anim), Num(What), Position(Where), Primitive(Anim) {
  RebuildPrim();
}


void nums::Update( int NewNum ) {
  Num = NewNum;
  RebuildPrim();
}


void nums::Update( const rect<float> &NewPos ) {
  Position = NewPos;
  RebuildPrim();
}


void nums::Render() {
  glDepthMask(false);
  Primitive.Draw();
  glDepthMask(true);
}


static std::shared_ptr<material> GetMaterial( const std::string &MaterialName, const std::string &TexturePath ) {
  std::shared_ptr<material> Material;
  if (!material::Manager.Exists(MaterialName)) {
    Material = material::Manager.Add(MaterialName, shader::Manager.Get("nums"));
    Material->Add(std::shared_ptr<texture>(new tex::png("Texture", 0, TexturePath)));
  } else
    Material = material::Manager.Get(MaterialName);
  return Material;
}


void nums::RebuildPrim() {
  Num = std::abs(Num);
  int NC = Num, Length = 0;
  do {
    ++Length;
    NC /= 10;
  } while (NC > 0);
  nums_vertex *Vertices = new nums_vertex[Length];
  int *Indices = new int[Length];

  NC = Num;
  int Digit;
  float W = Position.Width() / Length, H = Position.Height();
  for (int i = Length - 1; i >= 0; --i) {
    Digit = NC % 10;
    NC /= 10;
    Vertices[i].V0 = Position[0] + point<float>(W * i, 0);
    Vertices[i].V1 = Position[0] + point<float>(W * (i + 1), H);
    Vertices[i].Value = (float)Digit;
    Indices[i] = i;
  }
  Primitive.Set(std::make_shared<geometry>(Length, Vertices, Length, Indices),
                GetMaterial("nums", "../assets/textures/num.png"));
}


} // End of 'units' namespace
} // End of 'spectral' namespace
