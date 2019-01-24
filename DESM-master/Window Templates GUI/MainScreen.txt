//Required libraries
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR DESM[] = _T("Desktop Environment Setup Manager");

// The string that appears in the application's title bar.
static TCHAR windowsTitle[] = _T("MainScreen");

//Window Instance
HINSTANCE hInst;
//Creation of a handle for the window
HWND switchUserButton, createProfileButton, loadProfileButton, currentUserTextbox, currentProfileTextbox;

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
			_T("MainScreen"),
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
			_T("MainScreen"),
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
WNDPROC switchUserButtonProc, createProfileButtonProc, loadProfileButtonProc, currentUserTextboxProc, currentProfileTextboxProc;

//Callback for buttonproc
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
		return 0;
	case WM_LBUTTONUP:
		return 0;
	}
	return CallWindowProc(switchUserButtonProc, hwnd, msg, wp, lp);
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
	TCHAR currentUser[] = _T("Current User:");
	TCHAR currentProfile[] = _T("Current Profile:");

	switch (message)
	{
	case WM_CREATE:
	{
		//Create Button instance in the window
		//http://www.cplusplus.com/forum/windows/11305/
		//Switch User Button
		HWND switchUserButton = CreateWindow(TEXT("button"), TEXT("Switch User"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			40, 350, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do)
		switchUserButtonProc = (WNDPROC)SetWindowLong(switchUserButton, GWL_EXSTYLE, (LONG)ButtonProc);

		//Create Profile Button
		HWND createProfileButton = CreateWindow(TEXT("button"), TEXT("Create Profile"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			180, 350, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do) 
		createProfileButtonProc = (WNDPROC)SetWindowLong(createProfileButton, GWL_EXSTYLE, (LONG)ButtonProc);

		//Load Profile Button
		HWND loadProfileButton = CreateWindow(TEXT("button"), TEXT("Load Profile"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			320, 350, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do)
		loadProfileButtonProc = (WNDPROC)SetWindowLong(loadProfileButton, GWL_EXSTYLE, (LONG)ButtonProc);

		/*Checkbox for default user
		//https://stackoverflow.com/questions/24065214/how-to-make-checkbox-in-win32
		HWND checkbox = CreateWindow(TEXT("button"), TEXT("Default User"),
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
			250, 240, 120, 20,
			hWnd, NULL, NULL, NULL);
		//Button Proc (what it will do)
		checkboxProc = (WNDPROC)SetWindowLong(checkbox, GWL_EXSTYLE, (LONG)ButtonProc);*/

		//Textbox input
		HWND currentUserTextbox = CreateWindow(TEXT("EDIT"), TEXT(""),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			310, 30, 150, 20,
			hWnd, NULL, NULL, NULL);
		//GetDlgItemText(hwnd, 123, line, 100); handles getting the input

		HWND currentProfileTextbox = CreateWindow(TEXT("EDIT"), TEXT(""),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			170, 190, 200, 20,
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
			220, 30,
			currentUser, _tcsclen(currentUser));
		TextOut(hdc,
			70, 190,
			currentProfile, _tcsclen(currentProfile));

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
