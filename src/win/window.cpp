/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "window.h"

namespace spectral {


int window::InitializationTimer = 303030;


window::window( HINSTANCE hInst,
                const char *className, const char *caption,
                bool control, UINT menu, bool show,
                int width, int height ) :
    IsInitialized(false), hWnd(NULL), hInstance(hInst),
    Width(0), Height(0), IsActive(show), IsFullScreen(false),
    MouseWheel(0) {
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
  wc.lpfnWndProc = WinFunc;
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
  PostMessage(hWnd, WM_TIMER, (WPARAM)InitializationTimer++, 0);
}


int window::Run() {
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
      if (IsInitialized)
        Idle();
  }
  return msg.wParam;
}


LRESULT CALLBACK window::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam ) {
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
        return win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_CLOSE:
      case WM_DESTROY:
        win->OnCreate();
        return 0;
      case WM_SIZE:
        win->OnSize((UINT)wParam, (INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam));
        return 0;
      case WM_ACTIVATE:
        win->OnActivate((UINT)LOWORD(wParam), (HWND)(lParam), (BOOL)HIWORD(wParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)win->OnEraseBackground((HDC)wParam);
      case WM_PAINT:
      case WM_TIMER:
        win->OnPaint();
        win->OnTimer((UINT)wParam);
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        win->OnButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_KEYDOWN:
        win->OnKeyDown(wParam);
        return 0;
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        win->OnButtonUp((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_MOUSEWHEEL:
        win->OnMouseWheel((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (INT)(SHORT)HIWORD(wParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_COMMAND:
        // TODO: Create menu resource
        /* UINT m = LOWORD(wParam);
        if (m == ID_FILE_EXIT)
          win->OnCreate();
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


void window::DoExit() {
  PostMessage(hWnd, WM_CLOSE, 0, 0);
}


void window::SetFullScreen( bool turnOn )
{
  if (!IsFullScreen) {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &SavedRect);                           // Save old window size
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);  // Determine active monitor
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
    SetWindowPos(hWnd, HWND_TOPMOST,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  } else {
    /* Restore window size */
    SetWindowPos(hWnd, HWND_TOPMOST,
      SavedRect.left, SavedRect.top,
      SavedRect.right - SavedRect.left, SavedRect.bottom - SavedRect.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
}


window & window::operator<<( const std::pair<UINT, callback> &callback ) {
  MenuCallbacks.push_back(callback);
  return *this;
}


bool window::OnCreate( CREATESTRUCT *CS ) {
  Init();
  return true;
}


void window::OnCreate() {
  Close();
}


void window::OnSize( UINT state, INT width, INT height ) {
  Resize();
}


bool window::OnEraseBackground( HDC hDC ) {
  Erase(hDC);
  return true;
}


void window::OnPaint() {
  // NOTE: Where is hDC?? paint();
}


void window::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized ) {
  Activate(IsActive);
}


void window::OnTimer( INT Id ) {
  Timer();
}


void window::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) {
}


void window::OnKeyDown( UINT Keys ) {
}


void window::OnButtonUp( INT X, INT Y, UINT Keys ) {
}


void window::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys ) {
}


void window::Init() {
}


void window::Close() {
}


void window::Resize() {
}


void window::Erase( HDC hDC ) {
  HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
  HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));

  /* Default action - draw white rectangle */
  Rectangle(hDC, 0, 0, Width, Height);
  SelectObject(hDC, hOldPen);
  SelectObject(hDC, hOldBrush);
}


void window::Paint( HDC hDC ) {
}


void window::Activate( BOOL IsActive ) {
}


void window::Timer() {
}


void window::Idle() {
}


int window::GetW() {
  return Width;
}


int window::GetH() {
  return Height;
}


void window::Show( void ) {
  ShowWindow(hWnd, SW_SHOW);
}


void window::Hide( void ) {
  ShowWindow(hWnd, SW_HIDE);
}


} // End of 'spectral' namespace
