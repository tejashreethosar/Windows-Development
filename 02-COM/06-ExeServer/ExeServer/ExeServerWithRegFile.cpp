#include<Windows.h>
#include<tlhelp32.h>
#include"ExeServerWithRegFile.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM)

// class declarations
class CSumSubtract :public ISum, ISubtract
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSumSubtract(void);
	// destructor method declarations
	~CSumSubtract(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;
IClassFactory* gpIClassFactory = NULL;
HWND ghwnd = NULL;
DWORD dwRegister;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//function declarations
	HRESULT StartMyClassFactories(void);
	void StopMyClassFactories(void);
	DWORD GetParentProcessID(void);

	//variable declarations
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	HRESULT hr;
	int iDontShowWindow = 0;	//0 means show the window
	TCHAR AppName[] = TEXT("ExeServer");
	TCHAR szTokens[] = TEXT("-/");
	TCHAR* pszTokens;
	TCHAR lpszCmdLine[255];
	wchar_t* next_token = NULL;

	// com library initialization
	GetParentProcessID();

	hr = CoInitialize(NULL);

	if (FAILED(hr))
		return(0);

	MultiByteToWideChar(CP_ACP, 0, lpCmdLine, 255, lpszCmdLine, 255);

	pszTokens = wcstok_s(lpszCmdLine, szTokens, &next_token);

	while (pszTokens != NULL)
	{
		if (_wcsicmp(pszTokens, TEXT("Embedding")) == 0)	// i.e. COM is calling me
		{
			iDontShowWindow = 1;	// don't show window but message loop must 
			break;
		}
		else
		{
			MessageBox(NULL, TEXT("Bad command line arguments.\nExitting the application."), TEXT("Error"), MB_OK);
			exit(0);
		}
		pszTokens = wcstok_s(NULL, szTokens, &next_token);
	}

	// window code
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register window class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(AppName,
		TEXT("Exe Server With Reg File"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// initialize global window handle
	ghwnd = hwnd;

	if (iDontShowWindow != 1)	//true if server is not called by COM engine
	{
		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);

		// increment server lock
		++glNumberOfServerLocks;
	}
	if (iDontShowWindow == 1)	//only when COM calls this program
	{
		// start class factory
		hr = StartMyClassFactories();
		if (FAILED(hr))
		{
			DestroyWindow(hwnd);
			exit(0);
		}
	}

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (iDontShowWindow == 1)	// only when COM calls this program
	{
		// stop class factory
		StopMyClassFactories();
	}

	// COM library uninitialization
	CoUninitialize();

	return((int)msg.wParam);
}

// Window Procedure Pg - 100