
//Headers
#include<Windows.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

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
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	//ShowWindow(hwnd, SW_MAXIMIZE);
	//ShowWindow(hwnd, SW_MINIMIZE);
	//ShowWindow(hwnd, SW_HIDE);


	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}//while
	return((int)msg.wParam);
}//WinMain


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;


	TCHAR str[255];

	//code

	switch (iMsg) {


	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);

		break;
	case WM_LBUTTONDOWN:
		//MessageBox(hwnd, TEXT("WM_LBUTTONDOWN RECIVIED"), TEXT("MESSAGE"), MB_YESNO | MB_TOPMOST);
		MessageBox(hwnd, TEXT("This Is A MultiThreading Application"), TEXT("MESSAGE OF MULTITHREADING"), MB_SYSTEMMODAL);
		break;

	case WM_DESTROY:
		if (hThreadOne) {
			CloseHandle(hThreadOne);
			hThreadOne = NULL;
		}
		if (hThreadTwo) {
			CloseHandle(hThreadTwo);
			hThreadTwo = NULL;
		}
		PostQuitMessage(0);
		break;

	}//Switch

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc

DWORD WINAPI ThreadProcOne(LPVOID Param) {
	//local variABLES
	HDC hdc;
	unsigned long i;
	TCHAR str[255];

	//code
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 0, 0));
	hdc = GetDC((HWND)Param);
	for (i = 0; i < ULLONG_MAX; i++) {
		wsprintf(str, TEXT("Thread-1:IncreasingOrder:%ul"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));

	}
	ReleaseDC((HWND)Param, hdc)
		return 0;

}
DWORD WINAPI ThreadProcTwo(LPVOID Param) {
	//local variABLES
	HDC hdc;
	unsigned long i;
	TCHAR str[255];

	//code
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	hdc = GetDC((HWND)Param);
	for (i = ULLONG_MAX; i >= 0; i--) {
		wsprintf(str, TEXT("Thread-2:DecreasingOrder:%ul"), i);
		TextOut(hdc, 5, 25, str, wcslen(str));

	}
	ReleaseDC((HWND)Param, hdc)
		return 0;

}





