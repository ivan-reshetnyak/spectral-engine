/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include <windows.h>

#include "timer.h"

namespace spectral {


timer::timer() : FrameCount(0), GlobalTime(0), GlobalDeltaTime(0),
                 Time(0), DeltaTime(0), PauseTime(0), Paused(false), FPS(0) {
  LARGE_INTEGER CurrentTime;
  QueryPerformanceCounter(&CurrentTime);
  StartTime = OldTime = LastTime = CurrentTime.QuadPart;
  QueryPerformanceFrequency(&CurrentTime);
  TimesPerSecond = CurrentTime.QuadPart;
}


void timer::Update() {
  LARGE_INTEGER CurrentTime;
  QueryPerformanceCounter(&CurrentTime);

  /* Update global time */
  GlobalTime =
    (double)(CurrentTime.QuadPart - StartTime) / TimesPerSecond;
  GlobalDeltaTime =
    (double)(CurrentTime.QuadPart - OldTime) / TimesPerSecond;

  /* Update FPS */
  if (CurrentTime.QuadPart - LastTime > TimesPerSecond) {
    FPS = (double)FrameCount / (CurrentTime.QuadPart - LastTime) * TimesPerSecond;
    LastTime = CurrentTime.QuadPart;
    FrameCount = 0;
  }

  /* Update local time */
  Time = (double)(CurrentTime.QuadPart - StartTime - PauseTime) / TimesPerSecond;
  if (IsPaused())
    DeltaTime = 0, PauseTime += CurrentTime.QuadPart - OldTime;
  else
    DeltaTime = GlobalDeltaTime;

  OldTime = CurrentTime.QuadPart;
}


void timer::IncrFrameCount( void ) {
  FrameCount++;
}


bool timer::IsPaused() const {
  return Paused;
}


void timer::Pause() {
  Paused = true;
}


void timer::Unpause() {
  Paused = false;
}


void timer::TogglePause() {
  Paused = !Paused;
}


} // End of 'spectral' namespace
