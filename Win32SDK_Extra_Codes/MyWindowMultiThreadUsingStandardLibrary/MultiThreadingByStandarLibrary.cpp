
//Headers
#include<Windows.h>
#include<process.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void  __cdecl ThreadProcOne(void*);
void  __cdecl ThreadProcTwo(void*);

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

	//uintptr_t ulThreadOne = 0;
//	uintptr_t ulThreadTwo = 0;
	unsigned int ulThreadOne = 0;
	unsigned int ulThreadTwo = 0;

	TCHAR str[255];

	//code

	switch (iMsg) {


	case WM_CREATE:
		ulThreadOne = _beginthread(ThreadProcOne, 0, (void*)hwnd);
		ulThreadTwo = _beginthread(ThreadProcTwo, 0, (void*)hwnd);

		break;
	case WM_LBUTTONDOWN:
		//MessageBox(hwnd, TEXT("WM_LBUTTONDOWN RECIVI), TEXT("MESSAGE"), );
		MessageBox(hwnd, TEXT("This Is A MultiThreading Application Using Standard Library"), TEXT("MESSAGE OF MULTITHREADING"), MB_YESNO | MB_TOPMOST);
		break;
	case WM_DESTROY:
		
		PostQuitMessage(0);
		break;

	}//Switch

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc

void __cdecl ThreadProcOne(void* Param) {
	//local variABLES
	HDC hdc;
	unsigned long i;
	TCHAR str[255];

	//code

	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 0, 0));
	for (i = 0; i < ULLONG_MAX; i++) {
		wsprintf(str, TEXT("Thread-1:IncreasingOrder:%ul"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));

	}
	ReleaseDC((HWND)Param, hdc);
	_endthread();

}
void __cdecl ThreadProcTwo(void* Param) {
	//local variABLES
	HDC hdc;
	unsigned long i;
	TCHAR str[255];

	//code

	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = ULLONG_MAX; i >= 0; i--) {
		wsprintf(str, TEXT("Thread-2:DecreasingOrder:%ul"), i);
		TextOut(hdc, 5, 25, str, wcslen(str));

	}
	ReleaseDC((HWND)Param, hdc);
	_endthread();

}





