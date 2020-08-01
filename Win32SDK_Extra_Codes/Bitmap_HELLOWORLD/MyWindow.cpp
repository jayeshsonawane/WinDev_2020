
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
		TEXT("My Application"),
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
	//ShowWindow(hwnd,iCmdShow);


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
	static HDC hdcMem;
	static int cxBitmap, cyBitmap, cxClient, cyClient;
	static TCHAR* szText = TEXT("Omkar DADA ");
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;
	static HINSTANCE hInstance;
	int x, y;
	SIZE size;


	//code

	switch (iMsg) {

	case WM_CREATE:
		hdc = GetDC(hwnd);
		hdcMem = CreateCompatibleDC(hdc);
		GetTextExtentPoint32(hdc, szText, lstrlen(szText), &size);
		cxBitmap = size.cx;
		cyBitmap = size.cy;
		hBitmap = CreateCompatibleBitmap(hdc, cxBitmap, cyBitmap);
		ReleaseDC(hwnd, hdc);
		SelectObject(hdcMem, hBitmap);
		TextOut(hdcMem, 0, 0, szText, lstrlen(szText));
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = LOWORD(lParam);
		break;



	case WM_PAINT:
		
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		//itmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		//cMem = CreateCompatibleDC(NULL);
	//selectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc, 0, 0, rc.right,rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	/*	for(y=0;y<cyClient;y+=cyBitmap)
			for (x = 0; x < cxClient; x += cxBitmap) {
				BitBlt(hdc, x, y, cxBitmap, cyBitmap, hdcMem, 0, 0, SRCCOPY);
			}
	*/

		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		DeleteObject(hBitmap);
		DeleteDC(hdcMem);
		PostQuitMessage(0);
		break;

	}//Switch

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc




