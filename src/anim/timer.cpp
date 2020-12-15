/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include <windows.h>

#include "timer.h"

namespace spectral {


timer::timer() : frameCount(0), globalTime(0), globalDeltaTime(0),
                 time(0), deltaTime(0), pauseTime(0), paused(false), FPS(0) {
  LARGE_INTEGER CurrentTime;
  QueryPerformanceCounter(&CurrentTime);
  startTime = oldTime = lastTime = CurrentTime.QuadPart;
  QueryPerformanceFrequency(&CurrentTime);
  timesPerSecond = CurrentTime.QuadPart;
}


void timer::update() {
  LARGE_INTEGER CurrentTime;
  QueryPerformanceCounter(&CurrentTime);

  /* Update global time */
  globalTime =
    (double)(CurrentTime.QuadPart - startTime) / timesPerSecond;
  globalDeltaTime =
    (double)(CurrentTime.QuadPart - oldTime) / timesPerSecond;

  /* Update FPS */
  if (CurrentTime.QuadPart - lastTime > timesPerSecond) {
    FPS = (double)frameCount / (CurrentTime.QuadPart - lastTime) * timesPerSecond;
    lastTime = CurrentTime.QuadPart;
    frameCount = 0;
  }

  /* Update local time */
  time = (double)(CurrentTime.QuadPart - startTime - pauseTime) / timesPerSecond;
  if (isPaused())
    deltaTime = 0, pauseTime += CurrentTime.QuadPart - oldTime;
  else
    deltaTime = globalDeltaTime;

  oldTime = CurrentTime.QuadPart;
}


// NOTE: Do I even need this now?
void timer::incrFrameCount( void ) {
  frameCount++;
}


bool timer::isPaused() {
  return paused;
}


void timer::pause() {
  paused = true;
}


void timer::unpause() {
  paused = false;
}


void timer::togglePause() {
  paused = !paused;
}


} // End of 'spectral' namespace
