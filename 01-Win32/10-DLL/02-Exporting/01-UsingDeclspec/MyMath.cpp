#include <Windows.h>
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpResult)
{
	//code
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
		default:
			break;
	}

	return TRUE;
}

//declaration specific
extern "C" __declspec(dllexport) int MakeCube(int num)
{
	//code
	int cube = num*num*num;
	return cube;
}

//In this program we are making our own DLL

/* Steps to run:

1. cl.exe /c /EHsc MyMath.cpp
2. link.exe MyMath.obj /DLL user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS

After executing the above 2 commands the current directory will contain the following files -
 -> MyMath.cpp, MyMath.dll, MyMath.exp, MyMath.h, MyMath.lib, MyMath.obj
 
copy the .dll, .h, .lib files into the folder where you wish to use the dll

*/
