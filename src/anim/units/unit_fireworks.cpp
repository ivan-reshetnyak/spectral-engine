/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "../render/resource/tex/tex_png.h"
#include "../ui/ui_banner.h"
#include "../ui/ui_clickable_banner.h"
#include "../ui/ui_hideable.h"
#include "unit_fireworks.h"

namespace spectral {
namespace units {


color fireworks::PickColor() const {
  return color::random(ColorRange.first, ColorRange.second);
}


static std::shared_ptr<material> GetMaterial( const std::string &MaterialName, const std::string &TexturePath ) {
  std::shared_ptr<material> Material;
  if (!material::Manager.Exists(MaterialName)) {
    Material = material::Manager.Add(MaterialName, shader::Manager.Get("billboard"));
    Material->Add(std::shared_ptr<texture>(new tex::png("Texture", 0, TexturePath)));
  } else
    Material = material::Manager.Get(MaterialName);
  return Material;
}


fireworks::fireworks( animation *Anim ) :
    unit(Anim), UI(new ui::layout), ColorRange({ color(.5f, .8f, .5f), color(.7f, 1.f, .7f) }) {
  Explosion = std::make_shared<emitter::fireworks>(Anim, &Anim->World, 2.5f, vec(0, 50, 0),
                                                   10.f, 15.f, 250, color(1.f, 1.f, 1.f));
  Anim->World.Wind = vec::random();
  *Anim
    << (FPS = new units::nums(Anim, 0, rect<float>({ point<float>(-1.f, 0.95f), point<float>(-.95f, 1.f) })))
    << (ParticleNum = new units::nums(Anim, 0, rect<float>({ point<float>(-1.f, 0.9f), point<float>(-.9f, 0.95f) })));

  Period = 1.5;
  LastExplosion = Anim->Timer.Time - Period;

  UI->
    Add(std::make_shared<ui::button>(
      Anim->Mouse, rect<float>({ point<float>(0.0f, 0.0f), point<float>(1.0f, 1.0f) }),
      [this](){ Launch(ProjectMouse()); }))->
    Add(std::make_shared<ui::clickable_banner>(
      Anim, rect<float>({ point<float>(0.f, 0.f), point<float>(.3f, .1f) }),
      GetMaterial("unit_fireworks_button_red", "../assets/textures/ui/red.png"),
      [this](){ this->ColorRange = { color(.8f, .5f, .5f), color(1.f, .7f, .7f) }; }))->
    Add(std::make_shared<ui::clickable_banner>(
      Anim, rect<float>({ point<float>(0.f, .1f), point<float>(.3f, .2f) }),
      GetMaterial("unit_fireworks_button_green", "../assets/textures/ui/green.png"),
      [this](){ this->ColorRange = { color(.5f, .8f, .5f), color(.7f, 1.f, .7f) }; }))->
    Add(std::make_shared<ui::clickable_banner>(
      Anim, rect<float>({ point<float>(0.f, .2f), point<float>(.3f, .3f) }),
      GetMaterial("unit_fireworks_button_blue", "../assets/textures/ui/blue.png"),
      [this](){ this->ColorRange = { color(.5f, .5f, .8f), color(.7f, .7f, 1.f) }; }));


  auto ExitButton = std::make_shared<ui::clickable_banner>(
    Anim, rect<float>({ point<float>(0.95f, 0.95f), point<float>(1.0f, 1.0f) }),
    GetMaterial("unit_fireworks_button_cross", "../assets/textures/ui/cross.png"));
  auto ExitButtonHideable = std::make_shared<ui::hideable>(ExitButton, false);

  /* Exit message */
  auto ExitMessageBackground = std::make_shared<ui::banner>(
    Anim, rect<float>({ point<float>(0.7f, 0.7f), point<float>(1.0f, 1.0f) }),
    GetMaterial("unit_fireworks_button_exit_msg_bck", "../assets/textures/ui/exit.png"));
  auto ExitMessageAccept = std::make_shared<ui::clickable_banner>(
    Anim, rect<float>({ point<float>(0.75f, 0.75f), point<float>(0.8f, 0.8f) }),
    GetMaterial("unit_fireworks_button_ok", "../assets/textures/ui/ok.png"),
    [Anim](){ Anim->DoExit(); });
  auto ExitMessageCancel = std::make_shared<ui::clickable_banner>(
    Anim, rect<float>({ point<float>(0.90f, 0.75f), point<float>(0.95f, 0.8f) }),
    GetMaterial("unit_fireworks_button_cross", "../assets/textures/ui/cross.png"));
  auto ExitMessageLayout = std::make_shared<ui::layout>();
  ExitMessageLayout->Add(ExitMessageBackground)->Add(ExitMessageAccept)->Add(ExitMessageCancel);
  auto ExitMessageHideable = std::make_shared<ui::hideable>(ExitMessageLayout, true);

  std::weak_ptr<ui::hideable> ExitButtonHideableWeak(ExitButtonHideable);  // Lambdas will leak with shared ptrs!!!!
  std::weak_ptr<ui::hideable> ExitMessageHideableWeak(ExitMessageHideable);
  ExitButton->Set([ExitButtonHideableWeak, ExitMessageHideableWeak]() {
                    ExitButtonHideableWeak.lock()->Hide();
                    ExitMessageHideableWeak.lock()->Show();
                  });
  ExitMessageCancel->Set([ExitButtonHideableWeak, ExitMessageHideableWeak]() {
                           ExitButtonHideableWeak.lock()->Show();
                           ExitMessageHideableWeak.lock()->Hide();
                         });

  UI->Add(ExitButtonHideable)->Add(ExitMessageHideable);
}


vec fireworks::ProjectMouse() const {
  point<float> MouseCoords = Anim->Mouse.GetCoordsRelative();
  MouseCoords.X = -1.f + MouseCoords.X * 2.f;
  MouseCoords.Y = -1.f + MouseCoords.Y * 2.f;
  vec Ray = Anim->Camera.GetRay(MouseCoords);
  return Anim->Camera.Position + Ray * (-Anim->Camera.Position.Z / Ray.Z);  // (L + R * t).Z = 0 => t = -L.Z / R.Z
}


void fireworks::Launch( const vec &Position ) {
  if (Explosion->IsDead())
    ParticleManager << Explosion;

  Explosion->Set(PickColor())->Set(Position);
  Explosion->Release();
}


void fireworks::Update() {
  if (Anim->Timer.Time - LastExplosion > Period) {
    Launch(vec(random(-20, 20), random(40, 50), random(-5, 5)));
    LastExplosion = Anim->Timer.Time;
    Period = random(.5f, 1.f);
  }
  FPS->Update((int)Anim->Timer.FPS);
  ParticleNum->Update((int)Explosion->NumOfParticles);
  ParticleManager.Update(Anim->Timer);
  UI->Update();
}


void fireworks::Render() {
  ParticleManager.Render();
  UI->Render();
}


} // End of 'units' namespace
} // End of 'spectral' namespace
