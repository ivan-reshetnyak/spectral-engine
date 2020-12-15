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
  void update();
  void incrFrameCount( void );  // TODO: Do I even need this now?
  bool isPaused();
  void pause();
  void unpause();
  void togglePause();

private:
  UINT64
    startTime,       // Time from program start
    oldTime,         // Time of last frame
    lastTime,        // Time of last FPS measure
    pauseTime,       // Total pause time
    timesPerSecond,  // Timer sensitivity
    frameCount;
  double
    globalTime,      // Time from program start
    globalDeltaTime, // Delta time from last frame
    time,            // Time from prgram start (with pause)
    deltaTime,       // Delta time from last frame (with pause)
    FPS;
  bool paused;
};


} // End of 'spectral' namespace
