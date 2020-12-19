/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "../texture.h"

namespace spectral {
namespace tex {


class png : public texture {
public:
  png( const std::string &Name, int SamplerNumber );
  png( const std::string &Name, int SamplerNumber, const std::string &FileName );
  void Load( const std::string &FileName );
};


} // End of 'tex' namespace
} // End of 'spectral' namespace
