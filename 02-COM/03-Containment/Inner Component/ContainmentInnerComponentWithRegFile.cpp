#include<windows.h>
#include"ContainmentInnerComponentWithRegFile.h"

//class declarations
class CMultiplicationDivision :public IMultiplication, IDivision
{
private:
	long m_cRef;
public:
	//constructor method declaration
	CMultiplicationDivision(void);
	//destructor method declaration
	~CMultiplicationDivision(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	//IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	//contructor method declaration
	CMultiplicationDivisionClassFactory(void);
	//destructor method declarations
	~CMultiplicationDivisionClassFactory(void);
	
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
long glNumberOfServerLocks = 0;			//number of locks on this dll

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

//Implementation of CMultiplicationDivision's constructor method
CMultiplicationDivision::CMultiplicationDivision(void)
{
	m_cRef = 1;											//hardcoded initialization to anticipate possible failure of QueryInterface
	InterlockedIncrement(&glNumberOfActiveComponents);	//increment global counter
}

//Implementation of CMultiplicationDivision's destructor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);	//decrement global counter
}

//Implementation of CMultiplicationDivision's IUnknown's method
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivision::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of IMultiplication's methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
	*pMultiplication = num1 * num2;
	return(S_OK);
}

//Implementation of IDivision's methods
HRESULT  CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}

//Implementation of CMultiplicationDivisionClassFactory's constructor method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1;	//hardcoded initialization to anticipate possible failure of QueryInterface()
}

//Implementation of CMultiplicationDivisionClassFactory's destructor method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	//no code
}

//Implementation of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if(riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of CMultiplicationDivisionClassFactory's IClassFactory's methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	//create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	//get the required interface
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();	//anticipate possible failure of QueryInterface
	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

//Implementation of exported functions from this DLL
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create ClassFactory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();	//anticipate possible failure of QueryInterface()
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
STEPS TO RUN:
1. cl.exe /c /EHsc ContainmentInnerComponentWithRegFile.cpp
2. link.exe ContainmentInnerComponentWithRegFile.obj user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /DLL /DEF:ContainmentInnerComponentWithRegFile.def /SUBSYSTEM:WINDOWS
3. Step 3 is to copy and paste the created dll in the registry path i.e. C:\Windows\SysWOW64 (bcz this is 32 bit DLL)
*/