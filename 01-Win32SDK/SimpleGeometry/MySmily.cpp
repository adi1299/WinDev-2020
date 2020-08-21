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

	// local variables
	HDC  hdc;
	PAINTSTRUCT ps;
	static RECT rc;
	static HBRUSH hBrush;
	static HPEN hPen, hPen1;
	int hSpacing = 400, vSpacing = 100;
	int lEyeLeft = 600, lEyeTop = 300, lEyeRight = 100, lEyeBottom = 200;
	int rEyeLeft = 100, rEyeTop = 300, rEyeRight = 600, rEyeBottom = 200;
	int leftOuterCircle, topOuterCircle, rightOuterCircle, bottomOuterCircle;
	int leftInnerCircle, topInnerCircle, rightInnerCircle, bottomInnerCircle;
	int flag = 50;
	POINT ptArray[3];
	int pt1X = 150, pt1Y = 50, pt2Y = 100, pt3X = 150;
	//code
	switch (iMsg) {

	case WM_CREATE:

		//MessageBox(hwnd, TEXT("WM_CREATE is recieved."), TEXT("MESSAGE"), MB_OK);
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:

		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		hPen = CreatePen(PS_SOLID, 15, RGB(255, 255, 0));
		hPen1 = CreatePen(PS_SOLID, 5, RGB(255, 128, 0));
		//hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hPen);
		//Ellipse(hdc, rc.left+flag, rc.top+flag, rc.right-flag, rc.bottom-flag);
		leftOuterCircle = (rc.left)+hSpacing;
		topOuterCircle =  (rc.top)+vSpacing;
		rightOuterCircle = (rc.right)-hSpacing;
		bottomOuterCircle = (rc.bottom)-vSpacing;
		Ellipse(hdc, leftOuterCircle, topOuterCircle, rightOuterCircle, bottomOuterCircle);

		SelectObject(hdc, hPen1);
		leftInnerCircle = rc.left + lEyeLeft;
		topInnerCircle = rc.top + lEyeTop;
		rightInnerCircle = (rc.right/2) - lEyeRight;
		bottomInnerCircle = (rc.bottom/2) - lEyeBottom;
		Ellipse(hdc, leftInnerCircle, topInnerCircle, rightInnerCircle, bottomInnerCircle);

		leftInnerCircle = (rc.right/2) + rEyeLeft;
		topInnerCircle = (rc.top) + rEyeTop;
		rightInnerCircle = (rc.right) - rEyeRight;
		bottomInnerCircle = (rc.bottom/2) - rEyeBottom;
		Ellipse(hdc, leftInnerCircle, topInnerCircle, rightInnerCircle, bottomInnerCircle);

		ptArray[0] = {(rc.right/2)-pt1X, (rc.bottom/2)+pt1Y};
		ptArray[1] = {(rc.right/2), (rc.bottom/2)+pt2Y};
		ptArray[2] = {(rc.right/2)+pt3X, (rc.bottom/2)+pt1Y};
		Polyline(hdc, ptArray, 3);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:

		//MessageBox(hwnd, TEXT("WM_DESTROY is recieved"), TEXT("MESSAGE"), MB_OK);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
