/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <vector>

namespace spectral {


class animation;  // Forward declaration


class unit {
public:
  unit( animation *Anim );
  virtual ~unit();
  virtual void Update();
  virtual void Render();

protected:
  animation *Anim;
};


class unit_manager {
public:
  unit_manager();
  ~unit_manager();
  unit_manager & operator<<( unit *newUnit );
  unit_manager & Update();
  unit_manager & Render();

private:
  std::vector<unit *> Units;
};


} // End of 'spectral' namespace
