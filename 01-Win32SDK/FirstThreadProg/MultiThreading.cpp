

// Headers
#include<windows.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	// code
	// initialization of class WNDCLASSEX
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

	// register above class
	RegisterClassEx(&wndclass);

	// create window
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

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

  static HANDLE hThread1 = NULL;
  static HANDLE hThread2 = NULL;
  TCHAR str[255];

	//code
	switch (iMsg) {

	case WM_CREATE:

    hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
    hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
    //wsprintf(str, TEXT("The sum of %d and %d is %d"), num1, num2, num3);
		//MessageBox(hwnd, str, TEXT("MESSAGE"), MB_OK);
		//(LPCREATESTRUCTA)lParam->
		break;

	/*case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("WM_KEYDOWN is recieved"), TEXT("MESSAGE"), MB_OKCANCEL | MB_SYSTEMMODAL);
		break;*/

  case WM_LBUTTONDOWN:

		MessageBox(hwnd, TEXT("This is a MultiThreaded application."), TEXT("MESSAGE"), MB_OK);
		break;

	/*case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_RBUTTONDOWN is recieved"), TEXT("MESSAGE"), MB_OK);
		break;*/

	case WM_DESTROY:
    //Safe release
    if(hThread1) {

      CloseHandle(hThread1);
      hThread1 = NULL;
    }
    if(hThread2) {

      CloseHandle(hThread2);
      hThread2 = NULL;
    }
    //CloseHandle(hThread1);
    //CloseHandle(hThread2);
    //MessageBox(hwnd, TEXT("WM_DESTROY is recieved"), TEXT("MESSAGE"), MB_OK);
		PostQuitMessage(0);
		break;

  }
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {

    //local variables
    HDC hdc;
    long i;
    TCHAR str[255];

    //code
    SetBkColor(hdc, RGB(255, 255, 255));
    SetTextColor(hdc, RGB(0, 255, 0));
    hdc = GetDC((HWND)param);
    for(i=0; i<42947259; i++) {

        wsprintf(str, TEXT("Thread1: Increasing order: %d"), i);
        TextOut(hdc, 5, 5, str, wcslen(str));
    }
    ReleaseDC((HWND)param, hdc);
    return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {

    //local variables
    HDC hdc;
   	long i;
    TCHAR str[255];

    //code
    SetBkColor(hdc, RGB(255, 255, 255));
    SetTextColor(hdc, RGB(255, 255, 0));
    hdc = GetDC((HWND)param);
    for(i=42947259; i>0; i--) {

        wsprintf(str, TEXT("Thread2: Decreasing order: %d"), i);
        TextOut(hdc, 5, 25, str, wcslen(str));
    }
    ReleaseDC((HWND)param, hdc);
    return 0;
}
