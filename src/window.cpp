/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "win/window.h"

namespace spectral {


int window::initializationTimer = 303030;


window::window( HINSTANCE hInst,
                const char *className, const char *caption,
                bool control, UINT menu, bool show,
                int width, int height ) :
    isInitialized(false), hWnd(NULL), hInstance(hInst),
    width(0), height(0), isActive(show), isFullScreen(false),
    mouseWheel(0) {
  /* Fill and register window class */
  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(VOID *);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIconSm = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON,
    GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
  wc.hIcon = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON,
    GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
  wc.lpszMenuName = (CHAR *)menu;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = winFunc;
  wc.lpszClassName = className;
  if (!RegisterClassEx(&wc)) {
    MessageBox(NULL, "Error registering window class", "ERROR",
      MB_OK | MB_ICONSTOP);
    exit(0);
  }

  /* Window creation */
  hWnd = CreateWindow(className,
                      caption,
                      control ? WS_OVERLAPPEDWINDOW : WS_OVERLAPPED,
                      CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                      NULL, NULL, hInstance, (VOID *)this);
  if (hWnd == NULL) {
    MessageBox(NULL, "Error creating window", "ERROR",
      MB_OK | MB_ICONSTOP);
    exit(0);
  }
  /* Show and update window */
  if (show)
    ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* Send initialization timer message */
  PostMessage(hWnd, WM_TIMER, (WPARAM)initializationTimer++, 0);
}


int window::run() {
  MSG msg;
  /* Message loop */
  while (true) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
      if (isInitialized)
        idle();
  }
  return msg.wParam;
}


LRESULT CALLBACK window::winFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam ) {
  window *win;

  switch (Msg) {
  case WM_CREATE:
    SetWindowLong(hWnd, 0, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams);  // Attach 'this' pointer to window class
    ((window *)((CREATESTRUCT *)lParam)->lpCreateParams)->hWnd = hWnd;       // Store window handle
  default:
    win = (window *)GetWindowLong(hWnd, 0);                                  // Retrieve stored 'this'
    if (win != NULL) {
      switch (Msg)
      {
      case WM_CREATE:
        return win->onCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_CLOSE:
      case WM_DESTROY:
        win->onDestroy();
        return 0;
      case WM_SIZE:
        win->onSize((UINT)wParam, (INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam));
        return 0;
      case WM_ACTIVATE:
        win->onActivate((UINT)LOWORD(wParam), (HWND)(lParam), (BOOL)HIWORD(wParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)win->onEraseBackground((HDC)wParam);
      case WM_PAINT:
      case WM_TIMER:
        win->onPaint();
        win->onTimer((UINT)wParam);
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        win->onButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_KEYDOWN:
        win->onKeyDown(wParam);
        return 0;
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        win->onButtonUp((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_MOUSEWHEEL:
        win->onMouseWheel((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (INT)(SHORT)HIWORD(wParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_COMMAND:
        // TODO: Create menu resource
        /* UINT m = LOWORD(wParam);
        if (m == ID_FILE_EXIT)
          win->OnDestroy();
        else
          for (auto &i : win->MenuCallbacks)
            if (i.first == m)
              i.second(); */
        return 0;
      }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'tcg::window::WinFunc' function */


void window::doExit() {
  PostMessage(hWnd, WM_CLOSE, 0, 0);
}


void window::setFullScreen( bool turnOn )
{
  if (!isFullScreen) {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &savedRect);                           // Save old window size
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);  // Determine active monitor
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
    SetWindowPos(hWnd, HWND_TOPMOST,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
    isFullScreen = TRUE;
  } else {
    /* Restore window size */
    SetWindowPos(hWnd, HWND_TOPMOST,
      savedRect.left, savedRect.top,
      savedRect.right - savedRect.left, savedRect.bottom - savedRect.top,
      SWP_NOOWNERZORDER);
    isFullScreen = FALSE;
  }
}


window & window::operator<<( const std::pair<UINT, callback> &callback ) {
  menuCallbacks.push_back(callback);
  return *this;
}


bool window::onCreate( CREATESTRUCT *CS ) {
  init();
  return true;
}


void window::onDestroy() {
  close();
}


void window::onSize( UINT state, INT width, INT height ) {
  resize();
}


bool window::onEraseBackground( HDC hDC ) {
  erase(hDC);
  return true;
}


void window::onPaint() {
  // TODO: Where is hDC?? paint();
}


void window::onActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized ) {
  activate(isActive);
}


void window::onTimer( INT Id ) {
  timer();
}


void window::onButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) {
}


void window::onKeyDown( UINT Keys ) {
}


void window::onButtonUp( INT X, INT Y, UINT Keys ) {
}


void window::onMouseWheel( INT X, INT Y, INT Z, UINT Keys ) {
}


void window::init() {
}


void window::close() {
}


void window::resize() {
}


void window::erase( HDC hDC ) {
  HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
  HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));

  /* Default action - draw white rectangle */
  Rectangle(hDC, 0, 0, width, height);
  SelectObject(hDC, hOldPen);
  SelectObject(hDC, hOldBrush);
}


void window::paint( HDC hDC ) {
}


void window::activate( BOOL IsActive ) {
}


void window::timer() {
}


void window::idle() {
}


int window::getW() {
  return width;
}


int window::getH() {
  return height;
}


void window::show( void ) {
  ShowWindow(hWnd, SW_SHOW);
}


void window::hide( void ) {
  ShowWindow(hWnd, SW_HIDE);
}


} // End of 'spectral' namespace
