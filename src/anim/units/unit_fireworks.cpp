/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "../render/resource/tex/tex_png.h"
#include "../ui/ui_button.h"
#include "unit_fireworks.h"

namespace spectral {
namespace units {


static std::shared_ptr<material> GetLaunchButtonMaterial() {
  std::shared_ptr<material> Material;
  if (!material::Manager.Exists("unit_fireworks_button")) {
    Material = material::Manager.Add("unit_fireworks_button", shader::Manager.Get("button"));
    Material->Add(std::shared_ptr<texture>(new tex::png("Texture", 0, "../assets/textures/ui/launch.png")));
  } else
    Material = material::Manager.Get("unit_fireworks_button");
  return Material;
}

fireworks::fireworks( animation *Anim ) : unit(Anim), UI(new ui::layout) {
  Explosion = std::shared_ptr<emitter::fireworks>(
    new emitter::fireworks(Anim, &Anim->World, 2.5f, vec(0, 50, 0),
                           10.f, 15.f, 250, color(1.f, 1.f, 1.f)));
  Anim->World.Wind = vec::random();
  ParticleManager << Explosion;
  LastExplosion = Anim->Timer.Time;
  Period = 1.5;

  UI->Add(std::shared_ptr<ui::button>(
    new ui::button(Anim, ui::clickable(Anim->Mouse, rect<float>({ point<float>(0.0f, 0.0f),
                                                                  point<float>(0.3f, 0.2f) })),
                   [this](){ Launch(); }, GetLaunchButtonMaterial())));
}


void fireworks::Launch() {
  if (Explosion->IsDead())
      ParticleManager << Explosion;
    Explosion->Set(color(random(0.7f, 1), random(0.7f, 1), random(0.7f, 1)))->
      Set(vec(random(-20, 20), random(40, 50), random(-5, 5)));
    Explosion->Release();
    LastExplosion = Anim->Timer.Time;
    Period = random(0.5f, 1.0f);
}

void fireworks::Update() {
  ParticleManager.Update(Anim->Timer);
  UI->Update();
  /*
  if (Anim->Timer.Time - LastExplosion > Period) {
    if (Explosion->IsDead())
      ParticleManager << Explosion;
    Explosion->Set(color(random(0.7f, 1), random(0.7f, 1), random(0.7f, 1)))->
      Set(vec(random(-20, 20), random(40, 50), random(-5, 5)));
    Explosion->Release();
    LastExplosion = Anim->Timer.Time;
    Period = random(0.5f, 1.0f);
  }
  */

  /*
  if (Anim->Mouse[mouse::button::LEFT] == mouse::state::CLICK) {
    if (Explosion->IsDead())
      ParticleManager << Explosion;
    Explosion->Set(color(random(0.7f, 1), random(0.7f, 1), random(0.7f, 1)))->
      Set(vec(random(-20, 20), random(40, 50), random(-5, 5)));
    Explosion->Release();
    LastExplosion = Anim->Timer.Time;
    Period = random(0.5f, 1.0f);
  }
  */
}


void fireworks::Render() {
  ParticleManager.Render();
  UI->Render();
}


} // End of 'units' namespace
} // End of 'spectral' namespace
