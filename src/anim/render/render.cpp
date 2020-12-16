/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#ifndef GLEW_STATIC
#  define GLEW_STATIC
#endif /* GLEW_STATIC */
#include <gl/glew.h>

#pragma comment(lib, "opengl32")
// #pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")

#include "render.h"

namespace spectral {


render::render( HWND &hWndUsed, int &W, int &H ) :
    hWnd(hWndUsed), Width(W), Height(H) {
    // , Camera(vec(0, 40, 40), vec(0, 0, 0), vec(0, 1, 0), 1, 1, 1, 1.5, 10000.0, W, H)
  PIXELFORMATDESCRIPTOR pfd = {0};
  hDC = GetDC(hWnd);

  /***********************
   * OpenGL initialization
   ***********************/

  /* Describe pixel format */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  int i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  hRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hRC);  // Set context active

  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)) {
    // Failed to initialize GLEW
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    exit(0);
  }

  /* Setup default settings */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.3f, 0.5f, 0.7f, 1.f);
}


render::~render() {
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hRC);
  ReleaseDC(hWnd, hDC);
}


void render::Resize() {
  glViewport(0, 0, Width, Height);

  /* TODO: Update camera
  Camera.ScreenWidth = Width;
  Camera.ScreenHeight = Height;
  Camera.UpdateProjData();
  */
}


void render::StartFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void render::EndFrame() {
  glFinish();
}


void render::CopyFrame() {
  SwapBuffers(hDC);
}


} // End of 'spectral' namespace
