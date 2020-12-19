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
          const char *ClassName = "MyWindowClass",
          const char *Caption = "Window",
          bool Control = true,
          UINT Menu = 0,
          bool Show = false,
          int Width = CW_USEDEFAULT, int Height = CW_USEDEFAULT );

  // New menu callback add function
  window & operator<<( const std::pair<UINT, callback> &Callback );

  int Run();
  static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
  void DoExit();
  void SetFullScreen( bool TurnOn );

  /***
   * Cracked message handle functions
   ***/
  virtual bool OnCreate( CREATESTRUCT *CS );
  virtual void OnDestroy();
  virtual void OnSize( unsigned State, int Width, int Height );
  virtual bool OnEraseBackground( HDC hDC );
  virtual void OnPaint();
  virtual void OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
  virtual void OnTimer( INT Id );
  virtual void OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
  virtual void OnKeyDown( UINT Keys );
  virtual void OnButtonUp( INT X, INT Y, UINT Keys );
  virtual void OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
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
