/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "window_animation.h"

namespace spectral {


window_animation::window_animation( HINSTANCE hInst ) :
  window(hInst, "AnimationWindowClass", "Animation window", true, 0 /* TODO: Add menu IDR_MENU1 */, true) {
  SetTimer(hWnd, /* NOTE: What is '30', again? */30, 1, NULL);
}


void window_animation::OnCreate() {
  if (IsInitialized) {
    IsInitialized = false;
    Close();
    KillTimer(hWnd, 30);
  }
  PostMessage(hWnd, WM_QUIT, 0, 0);
}


} // End of 'spectral' namespace
