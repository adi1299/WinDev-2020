//Header Files
#include<windows.h>
#include"MyDialougeWindow.h"

// global declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE ghInstance;

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

  // local variables
  ghInstance = hInstance;
  HMENU hMenu;
  hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(MYMENU));

  MSG msg;
  HWND hwnd;
  TCHAR szAppName[] = TEXT("MyApp");
  WNDCLASSEX wndclass;

  wndclass.cbSize = sizeof(wndclass);
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.lpfnWndProc = WndProc;
  wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.lpszClassName = szAppName;
  wndclass.lpszMenuName = NULL;
  wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  // Register this class
  RegisterClassEx(&wndclass);

  // create window
  hwnd = CreateWindow(
    szAppName,
    TEXT("Aditya's application"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    hMenu,
    hInstance,
    NULL
  );

  ShowWindow(hwnd, SW_MAXIMIZE);
  UpdateWindow(hwnd);

  // message loop
  while (GetMessage(&msg, NULL, 0, 0)) {

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return((int)msg.wParam);
}

// WndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

  // local variables
  HBRUSH hBrush;
  static int idColor[] = {WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH};

  //code
  switch(iMsg) {

    case WM_COMMAND:
        switch(LOWORD(wParam)) {

          case IDM_WHITE:
          case IDM_LTGRAY:
          case IDM_GRAY:
          case IDM_DKGRAY:
          case IDM_BLACK:

              hBrush = (HBRUSH) GetStockObject(idColor[LOWORD(wParam) - IDM_WHITE]);
              SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)hBrush);
              InvalidateRect(hwnd, NULL, TRUE);
              break;

          case IDM_APP_ABOUT:

              DialogBox(ghInstance, TEXT("About"), hwnd, AboutDlgProc);
              break;
        }
      break;

    case WM_DESTROY:

      PostQuitMessage(0);
      break;
  }
  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

// AboutDlgProc Function
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

    switch(iMsg) {

      case WM_INITDIALOG:
          return TRUE;

      case WM_COMMAND:

          switch (LOWORD(wParam)) {

              case IDOK:
              case IDCANCEL:

                  EndDialog(hDlg, false);
                  return TRUE;
          }
          break;
    }

    return FALSE;
}
