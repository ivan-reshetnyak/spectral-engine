/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <windows.h>

namespace spectral {


class render {
public:
  render( HWND &hWndUsed, int &W, int &H );
  ~render();
  void Resize();
  void StartFrame();
  void EndFrame();
  void CopyFrame();
  // TODO: void Draw( prim &P ); Do I even need it?


private:
  HWND &hWnd;           // Window handle
  HDC hDC;              // Window device context
  HGLRC hRC;            // OpenGL rendering context
  int &Width, &Height;
  // TODO: camera Camera;
  // TODO: matr World;
};


} // End of 'spectral' namespace
