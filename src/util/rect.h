/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <array>

#include "point.h"

namespace spectral {


template<class type>
class rect {
public:
  using vertex = point<type>;

  rect( const std::array<vertex, 2> &Data ) : Vertices(Data) {
    if (Vertices[0].X > Vertices[1].X)
      std::swap(Vertices[0].X, Vertices[1].X);
    if (Vertices[0].Y > Vertices[1].Y)
      std::swap(Vertices[0].Y, Vertices[1].Y);
  }

  const vertex & operator[]( int Index ) const {
    return Vertices[Index];
  }


  vertex & operator[]( int Index ) {
    return Vertices[Index];
  }


  bool IsInside( const vertex &Point ) {
    return
      Point.X >= Vertices[0].X && Point.X <= Vertices[1].X &&
      Point.Y >= Vertices[0].Y && Point.Y <= Vertices[1].Y;
  }


protected:
  std::array<point<type>, 2> Vertices;
};


} // End of 'spectral' namespace
