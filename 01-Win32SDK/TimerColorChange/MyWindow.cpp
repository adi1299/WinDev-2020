// Headers
#include<windows.h>
#include"MyWindow.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int iPaintFlag;

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
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// register above class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
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

	// message loop
	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	//local variables
	HDC hdc;
	static HBRUSH brush[8];
	static RECT rc;
	PAINTSTRUCT ps;
	//code
	switch (iMsg) {

	case WM_CREATE:

		brush[0] = CreateSolidBrush(RGB(255, 0, 0)); //red
		brush[1] = CreateSolidBrush(RGB(0, 255, 0)); //green
		brush[2] = CreateSolidBrush(RGB(0, 0, 255)); //blue
		brush[3] = CreateSolidBrush(RGB(0, 255, 255)); //cyan
		brush[4] = CreateSolidBrush(RGB(128, 0, 128)); // magenta
		brush[5] = CreateSolidBrush(RGB(255, 0, 255)); // yellow
		brush[6] = CreateSolidBrush(RGB(255, 128, 0)); //orange
		brush[7] = CreateSolidBrush(RGB(255, 255, 255));//white

		SetTimer(hwnd, 110, 2000, NULL);
		//MessageBox(hwnd, TEXT("WM_CREATE is recieved"), TEXT("MESSAGE"), MB_OK);
		break;

	case WM_TIMER:

		KillTimer(hwnd, 110);
		iPaintFlag++;
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, 110, 2000, NULL);
		if(iPaintFlag > 7)
			iPaintFlag = 0;
		break;

	case WM_PAINT:

		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, brush[iPaintFlag]);
		FillRect(hdc, &rc, brush[iPaintFlag]);
		//SetTextColor(hdc, RGB(255, 255, 255));
		//DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
