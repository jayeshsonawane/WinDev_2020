//Headers
#include<Windows.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	//variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

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
	//HGDIOBJ GetStockObject(
	//int i
		//);

	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);        //The GetStockObject function retrieves a handle to one of the stock pens, brushes, fonts, or palettes.
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



	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}//while
	return((int)msg.wParam);
}//WinMain


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	int num1 = 25;
	int num2 = 100;
	TCHAR str[255];

	//code

	switch (iMsg) {
	case WM_CREATE:
		wsprintf(str, TEXT("For Addition Press + \nFor Subtraction Press - \nFor Multiplication Press * \nFor Division Press / \nFor Modulus Press %%  "));
		MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
		break;
	case WM_CHAR:
		switch (wParam) {
		case '+':
			TextBox()
			wsprintf(str, TEXT("The Addition Of %d and %d is : %d"), num1,num2,(num1+num2));
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;
		case '-':
			wsprintf(str, TEXT("The Subtraction Of %d and %d is : %d"), num1, num2, (num1 - num2));
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;
		case '*':
			wsprintf(str, TEXT("The Multiplication Of %d and %d is : %d"), num1, num2, (num1 * num2));
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;
		case '/':
			wsprintf(str, TEXT("The division Of %d and %d is : %d"), num1, num2, (num1 / num2));
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;
		case '%':
			wsprintf(str, TEXT("The Modulus Of %d and %d is : %d"), num1, num2, (num1 % num2));
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;
		}
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	

	}//Switch

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}//WndProc

