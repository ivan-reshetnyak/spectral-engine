/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>

namespace spectral {


class texture {
public:
  texture( int SamplerNumber );
  texture( int SamplerNumber, const std::string &FileName );
  texture( int SamplerNumber, int W, int H, const float *Pixels );
  void Load( const std::string &FileName );
  void Load( int Width, int Height, const float *Pixels );

private:
  static unsigned LastAppliedTextureID;

  int
    Width, Height,
    Sampler;
  unsigned ID;
};


} // End of 'spectral' namespace
