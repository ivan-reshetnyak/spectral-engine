/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "../render/resource/tex/tex_png.h"
#include "../ui/ui_banner.h"
#include "../ui/ui_button.h"
#include "../ui/ui_hideable.h"
#include "unit_fireworks.h"

namespace spectral {
namespace units {


static std::shared_ptr<material> GetMaterial( const std::string &MaterialName, const std::string &TexturePath ) {
  std::shared_ptr<material> Material;
  if (!material::Manager.Exists(MaterialName)) {
    Material = material::Manager.Add(MaterialName, shader::Manager.Get("button"));
    Material->Add(std::shared_ptr<texture>(new tex::png("Texture", 0, TexturePath)));
  } else
    Material = material::Manager.Get(MaterialName);
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

  UI->Add(std::make_shared<ui::button>(
    Anim, rect<float>({ point<float>(0.0f, 0.0f), point<float>(0.3f, 0.2f) }),
    GetMaterial("unit_fireworks_button_launch", "../assets/textures/ui/launch.png"),
    [this](){ Launch(); }));

  auto ExitButton = std::make_shared<ui::button>(
    Anim, rect<float>({ point<float>(0.95f, 0.95f), point<float>(1.0f, 1.0f) }),
    GetMaterial("unit_fireworks_button_cross", "../assets/textures/ui/cross.png"));
  auto ExitButtonHideable = std::make_shared<ui::hideable>(ExitButton, false);

  /* Exit message */
  auto ExitMessageBackground = std::make_shared<ui::banner>(
    Anim, rect<float>({ point<float>(0.7f, 0.7f), point<float>(1.0f, 1.0f) }),
    GetMaterial("unit_fireworks_button_exit_msg_bck", "../assets/textures/ui/exit.png"));
  auto ExitMessageAccept = std::make_shared<ui::button>(
    Anim, rect<float>({ point<float>(0.75f, 0.75f), point<float>(0.8f, 0.8f) }),
    GetMaterial("unit_fireworks_button_ok", "../assets/textures/ui/ok.png"),
    [Anim](){ Anim->DoExit(); });
  auto ExitMessageCancel = std::make_shared<ui::button>(
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
