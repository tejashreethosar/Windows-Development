#include <windows.h>
#include <mmsystem.h>
#define ID_TIMER1 101

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//colour madhe budavlela brush return kar, tujhya stock madhe aslela
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
	//variable declarations
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	TCHAR str1[]=TEXT("A");
	TCHAR str2[]=TEXT("B");
	TCHAR str3[]=TEXT("C");
	TCHAR str4[]=TEXT("D");
	TCHAR str5[]=TEXT("E");
	TCHAR str6[]=TEXT("F");
	TCHAR str7[]=TEXT("G");
	TCHAR str8[]=TEXT("H");
	TCHAR str9[]=TEXT("I");
	TCHAR str10[]=TEXT("J");
	TCHAR str11[]=TEXT("K");
	TCHAR str12[]=TEXT("L");
	TCHAR str13[]=TEXT("M");
	TCHAR str14[]=TEXT("N");
	TCHAR str15[]=TEXT("O");
	TCHAR str16[]=TEXT("P");
	TCHAR str17[]=TEXT("Q");
	TCHAR str18[]=TEXT("R");
	TCHAR str19[]=TEXT("S");
	TCHAR str20[]=TEXT("T");
	TCHAR str21[]=TEXT("U");
	TCHAR str22[]=TEXT("V");
	TCHAR str23[]=TEXT("W");
	TCHAR str24[]=TEXT("X");
	TCHAR str25[]=TEXT("Y");
	TCHAR str26[]=TEXT("Z");
	TCHAR str27[]=TEXT("JUCH HE!");
	TCHAR str28[]=TEXT("\x00C4"); //Ä
	TCHAR str29[]=TEXT("\x00D6"); //Ö
	TCHAR str30[]=TEXT("UND");
	TCHAR str31[]=TEXT("DAS");
	TCHAR str32[]=TEXT("\x00DC"); //Ü
	TCHAR str33[]=TEXT("ZUM");
	TCHAR str34[]=TEXT("LERNEN");
	TCHAR str35[]=TEXT("IST");
	TCHAR str36[]=TEXT("ES");
	TCHAR str37[]=TEXT("NIE");
	TCHAR str38[]=TEXT("ZU");
	TCHAR str39[]=TEXT("FR\x00DCH!"); //FRÜH
	static int iPaintFlag = 0;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		PlaySound((LPCSTR) "demo.wav", NULL, SND_FILENAME | SND_ASYNC);
		SetTimer(hwnd, ID_TIMER1, 1000, NULL);
		break;
	case WM_TIMER:
		KillTimer(hwnd, ID_TIMER1);
		iPaintFlag++;
		if(iPaintFlag>39)
			iPaintFlag=0;
		InvalidateRect(hwnd, NULL, TRUE);
		//SetTimer(hwnd, ID_TIMER1, 1000, NULL);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);					//get the client rea of the window
		hdc = BeginPaint(hwnd, &ps);				//BeginPaint()-prepares the specified window for painting and fills a PAINTSTRUCT structure with information about the painting, returns handle to the display device
		SetBkColor(hdc, RGB(0, 0, 0));				//Set bg color of the text same as the bg color of the window
		SetTextColor(hdc, RGB(0, 255, 0));			//Set the color of text to be displayed
		if(iPaintFlag==1){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str1, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);	//DT- Draw Text (in a single line & centrally)
		}
		else if(iPaintFlag==2){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str2, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==3){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str3, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==4){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str4, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==5){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str5, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==6){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str6, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==7){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str7, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==8){
			SetTimer(hwnd, ID_TIMER1, 1100, NULL);
			DrawText(hdc, str8, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==9){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str9, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==10){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str10, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==11){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str11, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==12){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str12, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==13){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str13, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==14){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str14, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==15){
			SetTimer(hwnd, ID_TIMER1, 400, NULL);
			DrawText(hdc, str15, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==16){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str16, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==17){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str17, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==18){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str18, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==19){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str19, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==20){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str20, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==21){
			SetTimer(hwnd, ID_TIMER1, 700, NULL);
			DrawText(hdc, str21, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==22){
			SetTimer(hwnd, ID_TIMER1, 700, NULL);
			DrawText(hdc, str22, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==23){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str23, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==24){
			SetTimer(hwnd, ID_TIMER1, 1200, NULL);
			DrawText(hdc, str24, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==25){
			SetTimer(hwnd, ID_TIMER1, 1100, NULL);
			DrawText(hdc, str25, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==26){
			SetTimer(hwnd, ID_TIMER1, 1000, NULL);
			DrawText(hdc, str26, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==27){
			SetTimer(hwnd, ID_TIMER1, 1000, NULL);
			DrawText(hdc, str27, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==28){
			SetTimer(hwnd, ID_TIMER1, 1100, NULL);
			DrawText(hdc, str28, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==29){
			SetTimer(hwnd, ID_TIMER1, 1100, NULL);
			DrawText(hdc, str29, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==30){
			SetTimer(hwnd, ID_TIMER1, 600, NULL);
			DrawText(hdc, str30, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==31){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str31, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==32){
			SetTimer(hwnd, ID_TIMER1, 1100, NULL);
			DrawText(hdc, str32, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==33){
			SetTimer(hwnd, ID_TIMER1, 700, NULL);
			DrawText(hdc, str33, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==34){
			SetTimer(hwnd, ID_TIMER1, 700, NULL);
			DrawText(hdc, str34, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==35){
			SetTimer(hwnd, ID_TIMER1, 700, NULL);
			DrawText(hdc, str35, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==36){
			SetTimer(hwnd, ID_TIMER1, 700, NULL);
			DrawText(hdc, str36, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==37){
			SetTimer(hwnd, ID_TIMER1, 700, NULL);
			DrawText(hdc, str37, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==38){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str38, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else if(iPaintFlag==39){
			SetTimer(hwnd, ID_TIMER1, 500, NULL);
			DrawText(hdc, str39, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else{
			SetTimer(hwnd, ID_TIMER1, 800, NULL);
			DrawText(hdc, str1, -1, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		
		EndPaint(hwnd, &ps);						//marks the end of painting, releases the display device context that BeginPaint retrieved.
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

Steps to run the program:
1. cl.exe sound.cpp /c /EHsc
2. link.exe sound.obj user32.lib gdi32.lib kernel32.lib winmm.lib
3. sound.exe
*/