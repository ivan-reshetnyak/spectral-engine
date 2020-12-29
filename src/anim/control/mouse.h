/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <array>

#include "../../util/point.h"

namespace spectral {


class mouse {
public:
  enum class button {
    LEFT = 0, MIDDLE = 1, RIGHT = 2
  };
  enum class state {
    UP, CLICK, DOWN
  };

  mouse( const int &Width, const int &Height );
  void Update();
  void Press( button Button );
  void Move( const point<int> &NewCoords );
  void Release( button Button );
  state operator[]( button Button ) const;
  point<int> GetCoordsAbsolute() const;
  point<float> GetCoordsRelative() const;

private:
  std::array<state, 3> Buttons, Previous;
  point<int> Coords;
  const int &Width, &Height;
};


} // End of 'spectral' namespace
