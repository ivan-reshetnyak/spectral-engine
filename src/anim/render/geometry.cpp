/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include "geometry.h"

namespace spectral {


geometry::geometry( void ) {
}


geometry::geometry( int NumOfV, vertex * Vertices, int NumOfI, int *Indices ) :
    NumOfV(NumOfV), Vertices(Vertices),
    NumOfI(NumOfI), Indices(Indices) {
}


geometry::~geometry( void ) {
  delete[] Vertices;
  delete[] Indices;
}


} // End of 'spectral' namespace
