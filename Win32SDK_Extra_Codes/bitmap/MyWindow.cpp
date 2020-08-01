
//Headers
#include<Windows.h>
#include "MyWindow.h"


//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	//variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	TCHAR str[255];

	//code
	//intialization of WNDCLASSEX

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

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("OmKAr I Love you"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,		//100 ,100 ,100 ,100
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,                //HWND_DESKTOP
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);



	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}//while
	return((int)msg.wParam);
}//WinMain


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {


	static HBITMAP hBitmap;
	HDC hdc;
	HDC hdcMem;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;
	static HINSTANCE hInstance;


	//code

	switch (iMsg) {

	case WM_CREATE:
		hInstance = GetModuleHandle(NULL);
		break;

	case WM_PAINT:
		
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		hdcMem = CreateCompatibleDC(NULL);
		SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		DeleteObject(hBitmap);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	}//Switch

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc




