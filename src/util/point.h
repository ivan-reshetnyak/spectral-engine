/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

namespace spectral {


template<class type>
class point {
public:
  type X, Y;

  point() {
  }


  point( const type &X, const type &Y ) : X(X), Y(Y) {
  }


  point operator+( const point &Other ) const {
    return point(X + Other.X, Y + Other.Y);
  }

  point operator*( const type &Multiplier ) const {
    return point(X * Multiplier, Y * Multiplier);
  }
};


} // End of 'spectral' namespace
