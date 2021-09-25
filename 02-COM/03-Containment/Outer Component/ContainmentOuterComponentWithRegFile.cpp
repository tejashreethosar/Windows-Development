#include<windows.h>
#include"ContainmentInnerComponentWithRegFile.h"
#include"ContainmentOuterComponentWithRegFile.h"

//class declarations
class CSumSubtract :public ISum, ISubtract, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication* m_pIMultiplication;
	IDivision* m_pIDivision;
public:
	//constructor method declaration
	CSumSubtract(void);
	//destrcutor method declaration
	~CSumSubtract(void);
	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	//ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
	//IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	//IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
	//custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);
};
class CSumSubtractClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declaration
	CSumSubtractClassFactory(void);
	//destructor method declaration
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
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0;			//number of locks on this dll

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	//code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

//Implementation of CSumSubtract's constructor method
CSumSubtract::CSumSubtract(void)
{
	//code
	//initialization of private data members
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);	//increment global counter
}

//Implementation of CSumSubtract's destructor method
CSumSubtract::~CSumSubtract(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);	//decrement global counter
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}

//Implementation of CSumSubtract's IUnknown's methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
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

//Implementation of ISum's methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}

//Implementation of ISubtract's methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}

//Implementation of IMultiplication's methods
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
	*pMultiplication = num1 * num2;
	return(S_OK);
}

//Implementation of IDivision's methods
HRESULT  CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	//variable declarations
	HRESULT hr;
	//code
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication interface can not be obtained from inner component."), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}
	return(S_OK);
}

//Implementation of CSumSubtractClassFactory's contructor method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1;
}
//Implementation of CSumSubtractClassFactory's destructor method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//no code
}

//Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's method
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
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

//Implementation of CSumSubtractClassFactory's IClassFactory's methods
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
	//initilize the inner component
	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to initialize inner component"), TEXT("Error"), MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}

	//get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();	//anticipate possible failure of QueryInterface
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create ClassFactory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();	//anticipate possible failure of QueryInterface()
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
1. cl.exe /c /EHsc ContainmentOuterComponentWithRegFile.cpp
2. link.exe ContainmentOuterComponentWithRegFile.obj user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /DLL /DEF:ContainmentOuterComponentWithRegFile.def /SUBSYSTEM:WINDOWS
3. Step 3 is to copy and paste the created dll in the registry path i.e. C:\Windows\SysWOW64 (bcz this is 32 bit DLL)
*/