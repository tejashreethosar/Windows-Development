#include <windows.h>								//used for Windows APIs, MACROS, datatypes, and predefined functions

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations

//entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)		//WINAPI - __stdcall calling convention i.e pascal(r->l), hInstance - the key to uniquely identify the program, hPrevInstance - for maintaining backward compatibility, lpszCmdLine - A pointer to a char string containing the command line arguments passed to the program, iCmdShow - how the window is to be displayed : (minimized, maximized, hidden...) by default -> (SW_NORMAL)
{
	//local variable declarations
	//Step1 - Initialize WNDCLASSEX structure
	WNDCLASSEX wndclass;							//window class extended
	HWND hwnd;										//window handle - initially NULL, after successfully running CreateWindow() it will hold a valid unsigned int value
	MSG msg;										//MSG is a structure having paraemeters - hwnd, message, wParam, lParam, time, pt (point) --> pt_x & pt_y
	TCHAR szAppName[] = TEXT("Teja's Window");		//TCHAR - microsoft definition for char, szAppname - window class name, TEXT() - macro that resolves to just the string in ASCII, resolves to L to indicate the string is using wide chars in Unicode

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);			//size of struct in count of bytes
	wndclass.style = CS_HREDRAW | CS_VREDRAW;		//style of window - how to repaint horizontally or vertically
	wndclass.lpfnWndProc = WndProc;					//long pointer to function, Name of func is address of func
	wndclass.cbClsExtra = 0;						//count  of bytes for extra info of class
	wndclass.cbWndExtra = 0;						//count of bytes for extra info of window
	wndclass.hInstance = hInstance;					//window's instance handle
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); 	//I don't have my own icon, so OS give my your 'ID of an Icon which is of type application'. LoadIcon(hInstance, LPCTSTR) returns handle for icon. This icon is big icon that we see in taskbar
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);		//Give me your default cursor, 'ID of cursor which is of type arrow'
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//return a color brush handle from your stock, GetStockObject returns hgdi obj hence we typecast it to hbrush.
	wndclass.lpszClassName = szAppName;				//unique name for window class
	wndclass.lpszMenuName = NULL;					//No menu for my window
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	//small icon that we see in top left of window, again taken from OS

	//Step2 - register class
	RegisterClassEx(&wndclass);						//Adds my class to OS's database of classes

	//Step3 - create the window in memory
	hwnd = CreateWindow(szAppName,					//szAppName - window class name
		TEXT("TNT : My First Window"),				//caption bar of window
		WS_OVERLAPPEDWINDOW,						//window style- overlapped (topmost window / in-focus window), combination of 6 styles - WS_CAPTION | WS_OVERLAPPED | WS_MINIMISEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME
		CW_USEDEFAULT,								//x co-ordinate of window
		CW_USEDEFAULT,								//y co-ordinate of window
		CW_USEDEFAULT,								//width of window
		CW_USEDEFAULT,								//height of window
		NULL,										//parent window handle (default parent window is Desktop - HWND_DESKTOP)
		NULL,										//no menu, hence no menu handle
		hInstance,									//instance handle
		NULL);										//creation parameter,if you want to pass some value from WinMain to WndProc then use this parameter
	
	//Step4 - show window created in memory
	ShowWindow(hwnd, iCmdShow);						//hwnd - handle of window to be displayed, iCmdShow - how to display the window (the way OS wants) hence 4th parameter of WinMan			
	UpdateWindow(hwnd);								//paint the window

	//message loop	 								//heart of the application- message loop(windows), event loop(linux), run loop(MacOS), game loop (RTR), looper/event loop (Android)
	//GetMessage(msg, hwnd, minrange, maxrange)  	//hwnd is given as NULL bcz we want to rcv the msgs of the current window as well as of the child windows, if given hwnd the application will rcv msgs of the current window only
	//WM_QUIT is the only msg that allows GetMessage to return false and quit the loop

	while (GetMessage(&msg, NULL, 0, 0))			//internally GetMessage monitors a msg queue where OS keeps the msgs of that window 	
	{
		TranslateMessage(&msg);						//msg-> in-out parameter, msg is translated and converted and passed to DispatchMessage()
		DispatchMessage(&msg);						//msg-> in parameter, calls WndProc and passes msg and other info as parameters
	}

	return((int)msg.wParam);						//return wParam of msg typecasted to int, i.e return 0
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) //wparam-16 bit, lparam-32 bit. wparam & lparam of every msg are different 
{
	//variable declarations
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	static int iPaintFlag = 0;
	//code
	switch (iMsg)
	{
	case WM_CHAR:
		switch(LOWORD(wParam))
		{
			case 'R':
			case 'r':
				iPaintFlag=1;
				InvalidateRect(hwnd, NULL, TRUE);	//InvalidateRect - indirectly generates WM_PAINT, marks the client area as invalid (that must be redrawn)
				break;
			case 'G':
			case 'g':
				iPaintFlag=2;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'B':
			case 'b':
				iPaintFlag=3;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'C':
			case 'c':
				iPaintFlag=4;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'M':
			case 'm':
				iPaintFlag=5;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'Y':
			case 'y':
				iPaintFlag=6;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'K':
			case 'k':
				iPaintFlag=7;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'W':
			case 'w':
				iPaintFlag=8;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			default:
				iPaintFlag=0;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
		}
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);					//get the client rea of the window
		hdc = BeginPaint(hwnd, &ps);				//BeginPaint()-prepares the specified window for painting and fills a PAINTSTRUCT structure with information about the painting, returns handle to the display device
		if(iPaintFlag==1)
			hbrush = CreateSolidBrush(RGB(255,0,0));	//create a specified color brush
		else if(iPaintFlag==2)
			hbrush = CreateSolidBrush(RGB(0,255,0));
		else if(iPaintFlag==3)
			hbrush = CreateSolidBrush(RGB(0,0,255));
		else if(iPaintFlag==4)
			hbrush = CreateSolidBrush(RGB(0,255,255));
		else if(iPaintFlag==5)
			hbrush = CreateSolidBrush(RGB(255,0,255));
		else if(iPaintFlag==6)
			hbrush = CreateSolidBrush(RGB(255,255,0));
		else if(iPaintFlag==7)
			hbrush = CreateSolidBrush(RGB(0,0,0));
		else if(iPaintFlag==8)
			hbrush = CreateSolidBrush(RGB(255,255,255));
		else
			hbrush = CreateSolidBrush(RGB(0,0,0));
		SelectObject(hdc, hbrush);					//select brush in hdc
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hbrush);						//delete the created brush
		EndPaint(hwnd, &ps);						//marks the end of painting, releases the display device context that BeginPaint retrieved.
		break;
	case WM_DESTROY:
		PostQuitMessage(0);							//WM_QUIT msg is posted to the window with wparam as 0, this msg is sucked by GetMessage() and the loop is terminated
		break;
	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam)); //Default Window Procedure - default message handling if we don't handle a particular message in our WndProc ex- minmize, maximize, close, sys menu
}

/*

STEPS:
1. Initialize WNDCLASSEX structure.
2. Register this initialized structure/class.
3. Create the window in memory.
4. Show the window on screen.
5. Paint the window.

*/