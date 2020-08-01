
//Headers
#include<Windows.h>
#include "MyWindow.h"
#define timer 102
int iPaintFlag;



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
		TEXT("My Application1"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,		//100 ,100 ,100 ,100
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL ,                //HWND_DESKTOP
		NULL,
		hInstance,
		NULL);

	//ShowWindow(hwnd, iCmdShow);
	ShowWindow(hwnd, SW_MAXIMIZE);


	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}//while
	return((int)msg.wParam);
}//WinMain


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){

	//static  HBRUSH brush[8];

	
	
	static HBITMAP hBitmap[8];
	HDC hdc;
	HDC hdcMem;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;
	static HINSTANCE hInstance;
	//TCHAR str[] = TEXT("Hello World !!!");

	//code

	switch (iMsg) {

		case WM_CREATE:
			hInstance = GetModuleHandle(NULL);
			hBitmap[0] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP1));
			hBitmap[1] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP2));
			hBitmap[2] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP3));
			hBitmap[3] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP4));
			hBitmap[4] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP5));
			hBitmap[5] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP6));
			hBitmap[6] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP7));
			
			SetTimer(hwnd, timer, 1000, NULL);
			break;

		case WM_TIMER:
			KillTimer(hwnd, timer);
			iPaintFlag++;
			if (iPaintFlag > 7) {
				iPaintFlag = 0;
			}
			InvalidateRect(hwnd, NULL, true);
			SetTimer(hwnd, timer, 1000, NULL);
			break;

		case WM_PAINT:
			


			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			
			hdcMem = CreateCompatibleDC(NULL);
			SelectObject(hdcMem, hBitmap[iPaintFlag]);
			GetObject(hBitmap[iPaintFlag], sizeof(BITMAP), &bitmap);
			StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			DeleteObject(hBitmap[iPaintFlag]);
			DeleteDC(hdcMem);
			EndPaint(hwnd, &ps);
			break;
	
		case WM_DESTROY:
		//	MessageBox(hwnd, TEXT("WM_DESTROY RECIVIED"), TEXT("MESSAGE"), MB_OK);
			PostQuitMessage(0);
			break;
		
	}//Switch

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc







