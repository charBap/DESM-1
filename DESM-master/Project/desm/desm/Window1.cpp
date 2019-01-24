//Required libraries
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR DESM[] = _T("Desktop Environment Setup Manager");

// The string that appears in the application's title bar.
static TCHAR windowsTitle[] = _T("Window1");

//Window Instance
HINSTANCE hInst;
//Creation of a handle for the window
HWND createAccountButton, resetPasswordButton, signInButton, checkbox, usernameTextbox, passwordTextbox;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Required windows-procedure function
//Code to handle messages that the application receives from Windows when events occur here
LRESULT CALLBACK WndProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

//Required int main for the project
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow

) {
	//Extra Window Properties
	//Ex exclusive icon cursor or color
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = DESM;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Window1"),
			NULL);

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;


	// The parameters to CreateWindow explained:
	// DESM: the name of the application
	// windowsTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		DESM,
		windowsTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//Faliure state
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Window1"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
//Button Proc test
WNDPROC createButtonProc, resetPasswordButtonProc, signInButtonProc, checkboxProc, usernameTextboxProc, passwordTextboxProc;

//Callback for buttonproc
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
		return 0;
	case WM_LBUTTONUP:
		return 0;
	}
	return CallWindowProc(createButtonProc, hwnd, msg, wp, lp);
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//TCHAR greeting[] = _T("Hello, Windows desktop!");
	TCHAR username[] = _T("Username:");
	TCHAR password[] = _T("Password:");

	switch (message)
	{
	case WM_CREATE:
	{
		//Create Button instance in the window
		//http://www.cplusplus.com/forum/windows/11305/
		//Create Account Button
		HWND createAccountButton = CreateWindow(TEXT("button"), TEXT("Create Account"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			90, 240, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do)
		createButtonProc = (WNDPROC)SetWindowLong(createAccountButton, GWL_EXSTYLE, (LONG)ButtonProc);

		//Reset Password Button
		HWND resetPasswordButton = CreateWindow(TEXT("button"), TEXT("Reset Password"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			90, 400, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do) 
		resetPasswordButtonProc = (WNDPROC)SetWindowLong(resetPasswordButton, GWL_EXSTYLE, (LONG)ButtonProc);

		//Sign-in Button
		HWND signInButtonButton = CreateWindow(TEXT("button"), TEXT("Sign In"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			250, 400, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do)
		signInButtonProc = (WNDPROC)SetWindowLong(signInButton, GWL_EXSTYLE, (LONG)ButtonProc);

		//Checkbox for default user
		//https://stackoverflow.com/questions/24065214/how-to-make-checkbox-in-win32
		HWND checkbox = CreateWindow(TEXT("button"), TEXT("Default User"),
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
			250, 240, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do)
		checkboxProc = (WNDPROC)SetWindowLong(checkbox, GWL_EXSTYLE, (LONG)ButtonProc);

		//Textbox input
		HWND usernameTextbox = CreateWindow(TEXT("EDIT"), TEXT(""),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			100, 200, 250, 20,
			hWnd, NULL, NULL, NULL);
		//GetDlgItemText(hwnd, 123, line, 100); handles getting the input

		HWND passwordTextbox = CreateWindow(TEXT("EDIT"), TEXT(""),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			100, 220, 250, 20,
			hWnd, NULL, NULL, NULL);
		//GetDlgItemText(hwnd, 123, line, 100); handles getting the input

		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		//TextOut(hdc,
			//5, 5,
			//greeting, _tcslen(greeting));
		// End application-specific layout section.

		//Handles Text only
		//https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/nf-wingdi-textouta
		TextOut(hdc,
			10, 200,
			username, _tcsclen(username));
		TextOut(hdc,
			10, 220,
			password, _tcsclen(password));

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
	{
	}
	break;
	case WM_DESTROY:

		//Destructor
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}
