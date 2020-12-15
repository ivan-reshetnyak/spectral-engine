/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "pch.h"

#include <functional>
#include <vector>

namespace spectral {

class window {
public:
  using callback = std::function<void( void )>;

  window( HINSTANCE hInst = GetModuleHandle(NULL),
          const char *className = "MyWindowClass",
          const char *caption = "Window",
          bool control = true,
          UINT menu = 0,
          bool show = false,
          int width = CW_USEDEFAULT, int height = CW_USEDEFAULT );

  // New menu callback add function
  window & operator<<( const std::pair<UINT, callback> &callback );

  int run();
  static LRESULT CALLBACK winFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
  void doExit();
  void setFullScreen( bool turnOn );

  /***
   * Cracked message handle functions
   ***/
  virtual bool onCreate( CREATESTRUCT *CS );
  virtual void onDestroy();
  virtual void onSize( UINT state, INT width, INT height );
  virtual bool onEraseBackground( HDC hDC );
  virtual void onPaint();
  virtual void onActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
  virtual void onTimer( INT Id );
  virtual void onButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
  virtual void onKeyDown( UINT Keys );
  virtual void onButtonUp( INT X, INT Y, UINT Keys );
  virtual void onMouseWheel( INT X, INT Y, INT Z, UINT Keys );

  /***
   * Virtual functions for window customization
   ***/
  virtual void init();
  virtual void close();
  virtual void resize();
  virtual void erase( HDC hDC );
  virtual void paint( HDC hDC );
  virtual void activate( BOOL IsActive );
  virtual void timer();
  virtual void idle();

  int getW();
  int getH();

  void show( void );
  void hide( void );

protected:
  static int initializationTimer;
  RECT savedRect;                                        // Rectangle saved for fullscreen mode
  bool isInitialized;
  HWND hWnd;
  HINSTANCE hInstance;
  int
    width, height,
    mouseWheel;
  bool isActive, isFullScreen;
  std::vector<std::pair<UINT, callback>> menuCallbacks;  // WinAPI menu custom callbacks
};

} // End of 'spectral' namespace
