#include <Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//class declarations
class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CSumSubtract(void);
	//destructor method declarations
	~CSumSubtract(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum specific method declarations
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	//ISubtract specific method declarations
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CSumSubtractClassFactory(void);

	//destructor method declarations
	~CSumSubtractClassFactory(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0;	//number of active components
long glNumberOfServerLocks = 0;			//number of locks on this DLL

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

//Implementation of CSumSubtract's Constructor Method
CSumSubtract::CSumSubtract(void)
{
	//hardcoded initialization to anticipate possible failure of QueryInterface()
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);	//increment global counter
}

//Implementation of CSumSubtract's Destructor Method
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);	//decrement global counter
}

//Implementation of CSumSubtract's IUnknown's Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}

//Implementation of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}

//Implementation of CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//hardcoded initialization to anticipate possible failure of QueryInterface();
	m_cRef = 1; 
}

//Implementation of CSumSubtractClassFactory's Destrcutor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//no code
}

//Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	//code
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	//create the instance of component i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);

	//get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);

	//anticipate the possible failure of QueryInterface()
	pCSumSubtract->Release();

	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfActiveComponents);
	else
		InterlockedDecrement(&glNumberOfActiveComponents);

	return(S_OK);
}

//Implementation of exported functions from this DLL
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable declarations
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	//code
	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}


/*
COMMANDS TO RUN SERVER:
1. cl.exe /c /EHsc ClassFactoryDllServerWithRegFile.cpp
2. link.exe ClassFactoryDllServerWithRegFile.obj user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /DLL /DEF:ClassFactoryDllServerWithRegFile.def /SUBSYSTEM:WINDOWS
3. Step 3 is to copy and paste the created dll in the registry path
*/
