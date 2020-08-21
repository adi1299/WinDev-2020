// Headers
#include<windows.h>
#include<stdlib.h>
#include<Synchapi.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	static HANDLE hMutex = NULL;
	static TCHAR str[] = TEXT("AYD Mutex");
	// code
	if (hMutex == NULL) { // To check whether Mutex is previously created or not for creating single instance of our program.

		hMutex = CreateMutex(NULL, FALSE, str); //Named Mutex created of name AYD
	}
	else
		exit(0);

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

	//code
	switch (iMsg) {

	case WM_CREATE:

		MessageBox(hwnd, TEXT("WM_CREATE is recieved."), TEXT("MESSAGE"), MB_OK);
		break;

	case WM_KEYDOWN:

		MessageBox(hwnd, TEXT("WM_KEYDOWN is recieved"), TEXT("MESSAGE"), MB_OKCANCEL | MB_SYSTEMMODAL);
		break;

	case WM_LBUTTONDOWN:

		MessageBox(hwnd, TEXT("WM_LBUTTONDOWN is recieved"), TEXT("MESSAGE"), MB_OK);
		break;

	case WM_RBUTTONDOWN:

		MessageBox(hwnd, TEXT("WM_RBUTTONDOWN is recieved"), TEXT("MESSAGE"), MB_OK);
		break;

	case WM_DESTROY:

		MessageBox(hwnd, TEXT("WM_DESTROY is recieved"), TEXT("MESSAGE"), MB_OK);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
