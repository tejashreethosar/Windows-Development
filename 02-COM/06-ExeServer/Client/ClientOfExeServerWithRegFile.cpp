#define UNICODE
#include<windows.h>
#include<process.h>
#include "ExeServerWithRegFile.h"

// global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Client");
	
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
		AppName,
		TEXT("CLIENT OF EXE SERVER"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//variable declarations
	ISum* pISum = NULL;
	ISubtract* pISubtract = NULL;
	HRESULT hr;
	int error, n1, n2, n3;
	TCHAR szWinSysDir[255];
	static TCHAR szPath[_MAX_PATH];
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		// first register ProxyStub.dll
		GetSystemDirectory(szWinSysDir, 255);
		wsprintf(szPath, TEXT("%s\\regsvr32.exe"), szWinSysDir);

		error = _wspawnlp(P_WAIT, szPath, szPath, TEXT("/s"), TEXT("ProxyStub.dll"), NULL);

		if (error == -1)
		{
			MessageBox(hwnd, TEXT("Proxy/Stub D11 Can Not Be Registered"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		
		// initialize COM library
		hr = CoInitialize(NULL);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("COM library can not be initialized"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}		
		// get ISum Interface
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_LOCAL_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("Component Can Not Be Created"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}

		n1 = 25;
		n2 = 5;
		pISum->SumOfTwoIntegers(n1, n2, &n3);
		wsprintf(str, TEXT("Sum of %d and %d = %d"), n1, n2, n3);
		MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		// get ISubtract Interface
		pISubtract->SubtractionOfTwoIntegers(n1, n2, &n3);
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), n1, n2, n3);
		MessageBox(hwnd, str, TEXT("SUBTRACTION"), MB_OK);
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		CoUninitialize();
		error = _wspawnlp(P_WAIT, szPath, szPath, TEXT("/u"), TEXT("/s"), TEXT("ProxyStub.dll"), NULL);
		if (error == -1)
		{
			MessageBox(hwnd, TEXT("Proxy/Stub D11 Can Not Be Un-Registered"), TEXT("Error"), MB_OK);
		}
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
