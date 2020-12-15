/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <windows.h>

namespace spectral {


class timer {
public:
  timer();
  void Update();
  void IncrFrameCount( void );  // NOTE: Do I even need this now?
  bool IsPaused();
  void Pause();
  void Unpause();
  void TogglePause();

private:
  UINT64
    StartTime,       // Time from program start
    OldTime,         // Time of last frame
    LastTime,        // Time of last FPS measure
    PauseTime,       // Total pause time
    TimesPerSecond,  // Timer sensitivity
    FrameCount;
  double
    GlobalTime,      // Time from program start
    GlobalDeltaTime, // Delta time from last frame
    Time,            // Time from prgram start (with pause)
    DeltaTime,       // Delta time from last frame (with pause)
    FPS;
  bool paused;
};


} // End of 'spectral' namespace
