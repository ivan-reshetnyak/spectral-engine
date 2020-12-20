/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <memory>
#include <string>

namespace spectral {


class texture {
public:
  texture( const std::string &Name, int SamplerNumber );
  const std::string &GetName() const;
  unsigned GetSamplerNumber() const;
  void Apply() const;

private:
  const std::string Name;

protected:
  static unsigned LastAppliedTextureID;
  unsigned ID;
  int
    Width, Height,
    Sampler;

  static unsigned SAMPLER( int N );
};


} // End of 'spectral' namespace
