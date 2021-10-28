#include<Windows.h>
#include "AutomationServerWithRegFile_C.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

IDispatch* pIDispatch = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr)) 
	{
		MessageBox(NULL, TEXT("COM Library cannot be initialized. \nProgram will nnow exit"), TEXT("Program Error"), MB_OK);
		exit(0);
	}
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
		TEXT("CLIENT OF COM DLL SERVER"),
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
	CoUninitialize();
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//void SafeInterfaceRelease(void);
	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];
	DISPID dispid;
	OLECHAR* szfunction1 = L"SumOfTwoIntegers";
	OLECHAR* szfunction2 = L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS params;
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(&CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, &IID_IDispatch, (void**)&pIDispatch);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("IDispatch Interface cannot be obtained. \nProgram will now exit"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 155;
		iNum2 = 145;
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = iNum2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = iNum1;
		params.rgvarg = vArg;
		params.cArgs = 2;
		params.rgdispidNamedArgs = NULL;
		params.cNamedArgs = 0;
		VariantInit(&vRet);

		// sum
		hr = pIDispatch->lpVtbl->GetIDsOfNames(pIDispatch, &IID_NULL, &szfunction1, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("GetIDsOfNames for SUM failed. \nProgram will now exit"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->lpVtbl->Invoke(pIDispatch, dispid, &IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Invoke for SUM failed. \nProgram will now exit"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

		// subtract
		hr = pIDispatch->lpVtbl->GetIDsOfNames(pIDispatch, &IID_NULL, &szfunction2, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("GetIDsOfNames for SUBTRACT failed. \nProgram will now exit"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->lpVtbl->Invoke(pIDispatch, dispid, &IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Invoke for SUBTRACT failed. \nProgram will now exit"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

		if (pIDispatch)
		{
			pIDispatch->lpVtbl->Release(pIDispatch);
			pIDispatch = NULL;
		}

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
/*void SafeInterfaceRelease(void)
{
	if (pIDispatch)
	{
		pIDispatch->Release();
		pIDispatch = NULL;
	}	
}*/