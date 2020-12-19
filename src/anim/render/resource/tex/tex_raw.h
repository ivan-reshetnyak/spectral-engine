/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "../texture.h"

namespace spectral {
namespace tex {


class raw : public texture {
public:
  raw( const std::string &Name, int SamplerNumber );
  raw( const std::string &Name, int SamplerNumber, int W, int H, std::shared_ptr<float> Pixels );
  void Load( int Width, int Height, std::shared_ptr<float> Pixels );
};


} // End of 'tex' namespace
} // End of 'spectral' namespace
