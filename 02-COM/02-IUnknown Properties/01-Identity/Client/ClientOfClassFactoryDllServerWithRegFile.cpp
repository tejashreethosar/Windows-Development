#include <Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IUnknown* gpIUnknownFromISum = NULL;
IUnknown* gpIUnknownFromISubtract = NULL;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;

	//code
	//COM Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library can not be initialized.\nProgram will now exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//WNDCLASSEX Initialization
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

	//register window class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(AppName,
		TEXT("Client of COM Dll Server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//COM Un-initialization
	CoUninitialize();
	return((int)msg.wParam);
}

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declarations
	void SafeInterfaceRelease(void);
	//variable declarations
	HRESULT hr;
	int iNum1, iNum2, iSum, iSubtract;
	TCHAR str[255];
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		//initialize arguments hardcoded
		iNum1 = 55;
		iNum2 = 45;
		//call SumOfTwoIntegers() of ISum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		//display the result
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		//call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		//as ISum is not needed now onwards, so release it
		//pISum->Release();
		//pISum = NULL;		//make released interface NULL

		//again initialize arguments hardcoded 
		iNum1 = 155;
		iNum2 = 145;
		//call SubtractionOfTwoIntegers() of ISubtract to get the difference
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);
		//as ISubtract is not needed now onwards, release it
		//pISubtract->Release();
		//pISubtract = NULL; //make released interface NULL
		//display the result
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSubtract);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// Checking the Identity Property 
		pISum->QueryInterface(IID_IUnknown, (void**)&gpIUnknownFromISum);
		pISubtract->QueryInterface(IID_IUnknown, (void**)&gpIUnknownFromISubtract);
		if(gpIUnknownFromISum == gpIUnknownFromISubtract)
			MessageBox(hwnd, TEXT("Both the IUnknown are same"), TEXT("Result"), MB_OK);
		else
			MessageBox(hwnd, TEXT("Both the IUnknown are different"), TEXT("Result"), MB_OK);
		//now release all the interfaces
		pISum->Release();
		pISum = NULL;
		pISubtract->Release();
		pISubtract = NULL;
		gpIUnknownFromISum->Release();
		gpIUnknownFromISum = NULL;
		gpIUnknownFromISubtract->Release();
		gpIUnknownFromISubtract = NULL;

		//exit the application
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		//relinquish the interfaces
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//This method is a safety measure to release interfaces if not previously
void SafeInterfaceRelease(void)
{
	//code
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
}

/*
STEPS TO RUN THE CLIENT:
1. cl.exe /c /EHsc ClientOfClassFactoryDllServerWithRegFile.cpp
2. link.exe ClientOfClassFactoryDllServerWithRegFile.obj user32.lib gdi32.lib kernel32.lib ole32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
3. ClientOfClassFactoryDllServerWithRegFile.exe
*/