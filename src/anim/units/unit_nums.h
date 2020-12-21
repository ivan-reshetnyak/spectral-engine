/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "util/rect.h"
#include "../animation.h"
#include "../unit.h"
#include "../render/prim/points.h"

namespace spectral {
namespace units {


class nums : public unit {
public:
  nums( animation *Anim, int What, const rect<float> &Where );
  void Update( int NewNum );
  void Update( const rect<float> &NewPos );
  void Render() override;

private:
  int Num;
  rect<float> Position;
  prim::points Primitive;

  void RebuildPrim();
};


} // End of 'units' namespace
} // End of 'spectral' namespace
