//Headers
#include<windows.h>
#include<stdlib.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
DWORD WINAPI ThreadProcThree(LPVOID);
DWORD WINAPI ThreadProcFour(LPVOID);

//global variable declarations
BOOL gbDone = FALSE;
RECT gRect;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdline, int iCmdShow) {

  //variable declarations
  WNDCLASSEX wndclass;
  HWND hwnd;
  MSG msg;
  TCHAR szAppName[] = TEXT("My App");

  //code
  //initialization of WNDCLASSEX
  wndclass.cbSize = sizeof(WNDCLASSEX);
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.lpfnWndProc = WndProc;
  wndclass.hInstance = hInstance;
  wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wndclass.lpszClassName = szAppName;
  wndclass.lpszMenuName = NULL;
  wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  //register above class
  RegisterClassEx(&wndclass);

  //CreateWindow
  hwnd = CreateWindow(szAppName,
      TEXT("Aditya's Application"),
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      NULL,
      NULL,
      hInstance,
      NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    //message loop
    while (GetMessage(&msg, NULL, 0, 0)) {

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

  //Local variables
  static HANDLE hThreadOne = NULL;
  static HANDLE hThreadTwo = NULL;
  static HANDLE hThreadThree = NULL;
  static HANDLE hThreadFour = NULL;

  //code
  switch (iMsg) {

    case WM_CREATE:

      GetClientRect(hwnd, &gRect);
      hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
      hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
      hThreadThree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcThree, (LPVOID)hwnd, 0, NULL);
      hThreadFour = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcFour, (LPVOID)hwnd, 0, NULL);
      break;

    case WM_SIZE:

      GetClientRect(hwnd, &gRect);
      break;

    case WM_DESTROY:

      if(hThreadOne) {

        CloseHandle(hThreadOne);
        hThreadOne = NULL;
      }
      if(hThreadTwo) {

        CloseHandle(hThreadTwo);
        hThreadTwo = NULL;
      }
      if(hThreadThree) {

        CloseHandle(hThreadThree);
        hThreadThree = NULL;
      }
      if(hThreadFour) {

        CloseHandle(hThreadFour);
        hThreadFour = NULL;
      }
      PostQuitMessage(0);
      break;

    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
  }
}

//Function definitions
DWORD WINAPI ThreadProcOne(LPVOID param) {

  //variable
  HDC hdc;
  long i;
  TCHAR str[255];

  //Code
  hdc = GetDC((HWND)param);
  SetBkColor(hdc, RGB(0, 0, 0));
  SetTextColor(hdc, RGB(0, 255, 0));
  for(i = 0; i<42947295; i++) {

    wsprintf(str, TEXT("Thread One: %ul"), i);
    TextOut(hdc, 5, 5, str, wcslen(str));

    wsprintf(str, TEXT("Thread Two: %ul"),42947295-i);
    TextOut(hdc, 5, 20, str, wcslen(str));
  }
  ReleaseDC((HWND)param, hdc);
  return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {

  //variable
  HDC hdc;
  HBRUSH hBrush;
  RECT rc;

  //Code
  hdc = GetDC((HWND)param);
  while (gbDone == FALSE) {

    rc.left = gRect.right / 2 + (rand() % gRect.right) / 2;
    rc.top = (rand() % gRect.bottom) / 2;
    rc.right = gRect.right / 2 + (rand() % gRect.right) / 2;
    rc.bottom = (rand() % gRect.bottom) / 2;

    hBrush = CreateSolidBrush(RGB(rand() % 256 , rand() % 256, rand() % 256));
    FillRect(hdc, &rc, hBrush);
    DeleteObject(hBrush);
  }
  ReleaseDC((HWND)param, hdc);
  return 0;
}

DWORD WINAPI ThreadProcThree(LPVOID param) {

  //variable
  HDC hdc;
  HBRUSH hBrush;
  RECT rc;

  //Code
  hdc = GetDC((HWND)param);
  while (gbDone == FALSE) {

    rc.left = gRect.right / 2 + (rand() % gRect.right) / 2;
    rc.top = gRect.bottom/2 + (rand() % gRect.bottom) / 2;
    rc.right = gRect.right / 2 + (rand() % gRect.right) / 2;
    rc.bottom = gRect.bottom / 2;

    hBrush = CreateSolidBrush(RGB(rand() % 256 , rand() % 256, rand() % 256));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
    DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));
  }
  ReleaseDC((HWND)param, hdc);
  return 0;
}

DWORD WINAPI ThreadProcFour(LPVOID param) {

  //variable
  HDC hdc;
  HBRUSH hBrush;
  RECT rc;

  //Code
  hdc = GetDC((HWND)param);
  while (gbDone == FALSE) {

    rc.left = gRect.left / 2 + (rand() % gRect.right) / 2;
    rc.top = gRect.bottom/2 + (rand() % gRect.bottom) / 2;
    rc.right = gRect.left / 2 + (rand() % gRect.right) / 2;
    rc.bottom = gRect.bottom / 2;

    hBrush = CreateSolidBrush(RGB(rand() % 256 , rand() % 256, rand() % 256));
    SelectObject(hdc, hBrush);
    RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom, rand()%20, rand()%20);
    DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));
  }
  ReleaseDC((HWND)param, hdc);
  return 0;
}
