#include <windows.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations

//entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	//Initialize WNDCLASSEX structure
	WNDCLASSEX wndclass;					//window class extended
	HWND hwnd;						//initially NULL, after successfully running CreateWindow() it will hold a valid unsigned int value
	MSG msg;
	TCHAR szAppName[] = TEXT("Teja's Window");		//Making the application unicode compliant

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);			//size in count of bytes
	wndclass.style = CS_HREDRAW | CS_VREDRAW;		//style of window
	wndclass.lpfnWndProc = WndProc;				//long pointer to function, Name of func is address of func
	wndclass.cbClsExtra = 0;				//count  of bytes for extra info of class
	wndclass.cbWndExtra = 0;				//count of bytes for extra info of window
	wndclass.hInstance = hInstance;				//window's instance handle
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); 	/*I don't have my own icon, so OS give my your 'ID of an Icon which is of type application'. LoadIcon(hInstance, LPCTSTR) returns handle for icon. This icon is big icon that we see in taskbar*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);		//Give me your default cursor, 'ID of cursor which is of type arrow'
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//colour madhe budavlela brush return kar, tujhya stock madhe aslela
	wndclass.lpszClassName = szAppName;			//unique name for class
	wndclass.lpszMenuName = NULL;				//No menu for my window
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	//small icon that we see in top left of window, again taken from OS

	//register class
	RegisterClassEx(&wndclass);				//Adds my class to OS's database of classes

	//create the window in memory
	hwnd = CreateWindow(szAppName,				//custom window class 
		TEXT("TNT : My First Window"),			//caption bar of window
		WS_OVERLAPPEDWINDOW,				//window style- overlapped (topmost window / in-focus window)
		CW_USEDEFAULT,					//x co-ordinate of window
		CW_USEDEFAULT,					//y co-ordinate of window
		CW_USEDEFAULT,					//width of window
		CW_USEDEFAULT,					//height of window
		NULL,						//parent window handle (default parent window is Desktop - HWND_DESKTOP)
		NULL,						//no menu, hence no menu handle
		hInstance,					//instance handle
		NULL);						//creation parameter,if you want to pass some value from WinMain to WndProc then use this parameter
	ShowWindow(hwnd, iCmdShow);				//show window created in memory
	UpdateWindow(hwnd);

	//message loop	 					//heart of the application- message loop(windows), event loop(linux), run loop(MacOS), game loop (RTR)
	while (GetMessage(&msg, NULL, 0, 0))			//internally GetMessage monitors a msg queue where OS keeps the msgs of that window 	
	{
		TranslateMessage(&msg);				//msg-> in-out parameter
		DispatchMessage(&msg);				//msg-> in parameter
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) //wparam-16 bit, lparam-32 bit. wparam & lparam of every msg are different 
{
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("WM_CREATE message is arrived"), TEXT("Message"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Left mouse button is clicked"), TEXT("Message"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("Right mouse button is clicked"), TEXT("Message"), MB_OK);
		break;
	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("A key is pressed"), TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

/*

STEPS:
1. Initialize WNDCLASSEX structure.
2. Register this initialized structure/class.
3. Create the window in memory.
4. Show the window on screen.
5. Paint the window.
*/