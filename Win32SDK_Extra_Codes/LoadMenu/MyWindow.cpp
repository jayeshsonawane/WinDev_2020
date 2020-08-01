
//Headers
#include<Windows.h>
#include "MyWindow.h"



//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDLGProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE ghInstance;
//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	//variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	TCHAR str[255];

	HMENU hMenu;

	//codes
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

	ghInstance = hInstance;
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(MYMENU));

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
		NULL,                //HWND_DESKTOP
		hMenu,                         //menu sathi
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);



	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}//while
	return((int)msg.wParam);
}//WinMain


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static int idColor[5] = { WHITE_BRUSH,LTGRAY_BRUSH,DKGRAY_BRUSH,GRAY_BRUSH,BLACK_BRUSH };
	HBRUSH hBrush;


	//code

	switch (iMsg) {

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_WHITE:
		case IDM_LTGRAY:
		case IDM_DKGRAY:
		case IDM_GRAY:
		case IDM_BLACK:
			hBrush = (HBRUSH)GetStockObject(idColor[(LOWORD(wParam) - IDM_WHITE)]);
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)hBrush);
			InvalidateRect(hwnd, NULL, true);
			break;

		case IDM_APPABOUT:
			DialogBox(ghInstance, TEXT("ABOUT"), hwnd, AboutDLGProc);
			break;

		}//Internal Switch

		break;				//WM_COMMAND



	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	}//Switch

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc

BOOL  CALLBACK AboutDLGProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	switch (iMsg) {
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, false);
			return true;

		}//Inner switch
		break;			//WM_COMMAND


	}//Outer Switch
	return false;


}//callback







