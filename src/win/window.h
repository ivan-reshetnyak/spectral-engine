/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

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

  int Run();
  static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
  void DoExit();
  void SetFullScreen( bool turnOn );

  /***
   * Cracked message handle functions
   ***/
  virtual bool OnCreate( CREATESTRUCT *CS );
  virtual void OnCreate();
  virtual void OnSize( UINT state, INT width, INT height );
  virtual bool OnEraseBackground( HDC hDC );
  virtual void OnPaint();
  virtual void OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
  virtual void OnTimer( INT Id );
  virtual void OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
  virtual void OnKeyDown( UINT Keys );
  virtual void OnButtonUp( INT X, INT Y, UINT Keys );
  virtual void OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );

  /***
   * Virtual functions for window customization
   ***/
  virtual void Init();
  virtual void Close();
  virtual void Resize();
  virtual void Erase( HDC hDC );
  virtual void Paint( HDC hDC );
  virtual void Activate( BOOL IsActive );
  virtual void Timer();
  virtual void Idle();

  int GetW();
  int GetH();

  void Show( void );
  void Hide( void );

protected:
  static int InitializationTimer;
  RECT SavedRect;                                        // Rectangle saved for fullscreen mode
  bool IsInitialized;
  HWND hWnd;
  HINSTANCE hInstance;
  int
    Width, Height,
    MouseWheel;
  bool IsActive, IsFullScreen;
  std::vector<std::pair<UINT, callback>> MenuCallbacks;  // WinAPI menu custom callbacks
};


} // End of 'spectral' namespace
