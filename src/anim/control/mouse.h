/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <array>

namespace spectral {


class mouse {
public:
  enum class button {
    LEFT = 0, MIDDLE = 1, RIGHT = 2
  };
  enum class state {
    UP, CLICK, DOWN
  };

  mouse();
  void Update();
  void Press( button Button );
  void Move( int NewX, int NewY );
  void Release( button Button );
  state operator[]( button Button ) const;

private:
  std::array<state, 3> Buttons, Previous;
  int X, Y;
};


} // End of 'spectral' namespace
