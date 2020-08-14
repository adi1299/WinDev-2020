// Headers
#include<windows.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register above class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("Tiranga"),
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

	RECT rc, rcTemp;
	static HBRUSH hBrush[3];
	PAINTSTRUCT ps;
	HDC hdc;
	int left, top, right, bottom;
	//code
	switch (iMsg) {

	case WM_CREATE:

		hBrush[0] = CreateSolidBrush(RGB(255,128,0));
		hBrush[1] = CreateSolidBrush(RGB(0,255,0));
		hBrush[2] = CreateSolidBrush(RGB(0,0,255));
		InvalidateRect(hwnd, NULL, TRUE);
		//MessageBox(hwnd, TEXT("WM_CREATE is recieved."), TEXT("MESSAGE"), MB_OK);
		break;

	case WM_PAINT:
		// Initializing rc with the client area window
		GetClientRect(hwnd, &rc);
		// Setting the coordinates for Ellipse
		left = (rc.right/2) - 148;
		top = (rc.bottom/2) - 148;
		right = (rc.right/2) + 148;
		bottom = (rc.bottom/2) + 148;
		// Initializing the hdc
		hdc = BeginPaint(hwnd, &ps);
		// Selecting Orange color for the flag
		SelectObject(hdc, hBrush[0]);
		rc.bottom = 250;
		FillRect(hdc , &rc, hBrush[0]);
		// Selecting Green color for the flag
		SelectObject(hdc, hBrush[1]);
		rcTemp.top = rc.top+550;
		FillRect(hdc, &rcTemp, hBrush[1]);
		// Selecting Blue color for the flag
		SelectObject(hdc, hBrush[2]);
		Ellipse(hdc, left,top,right,bottom);

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:

		//MessageBox(hwnd, TEXT("WM_DESTROY is recieved"), TEXT("MESSAGE"), MB_OK);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
