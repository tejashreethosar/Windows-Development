// Header Files
#include <windows.h>
#include <stdio.h>					// for swprintf_s()
#include "AutomationServerWithRegFile.h"

// class declarations
// coclass
class CMyMath :public IMyMath
{
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo;
public:
	// constructor method declarations
	CMyMath(void);
	// destructor method declarations
	~CMyMath(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IDispatch specific method declarations (inherited)
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);
	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
	// custom methods
	HRESULT InitInstance(void);
};

// class factory
class CMyMathClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CMyMathClassFactory(void);
	// destructor method declarations
	~CMyMathClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global DLL handle
HMODULE ghModule = NULL;

// global variable declarations
long glNumberOfActiveComponents = 0;	//number of active components
long glNumberOfServerLocks = 0;			//number of locks on this dll
// {6D554AFA-3D0E-466E-A480-A6EF5508B1B7}
const GUID LIBID_AutomationServer = { 0x6d554afa, 0x3d0e, 0x466e, 0xa4, 0x80, 0xa6, 0xef, 0x55, 0x8, 0xb1, 0xb7 };

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	// code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

// Implementation of CMyMath's Constructor Method
CMyMath::CMyMath(void)
{
	// code
	m_pITypeInfo = NULL;								//private variables must be initialised (always) otherwise compiler misbehaves!!
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

// Implementation of CMyMath's Destructor Method
CMyMath::~CMyMath(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// Implementation of CMyMath's IUnknown's Methods
HRESULT CMyMath::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMath::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMath::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation of IMyMath's Methods
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	// code
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	// code
	*pSubtract = num1 - num2;
	return(S_OK);
}

HRESULT CMyMath::InitInstance(void)
{
	// function declarations
	void ComErrorDescriptionString(HWND, HRESULT);
	// variable declarations
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;
	// code
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			1, 0,	// major/minor version numbers
			0x00,	// LANG_NEUTRAL
			&pITypeLib);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return(S_OK);
}

// Implementation of CMyMathClassFactory's Constructor Method
CMyMathClassFactory::CMyMathClassFactory(void)
{
	// code
	m_cRef = 1;
}

// Implementation of CMyMathClassFactory's Destructor Method
CMyMathClassFactory::~CMyMathClassFactory(void)
{
	// code
}

// Implementation of CMyMathClassFactory's IClassFactory's IUnknown's Method
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// code
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

ULONG CMyMathClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMathClassFactory::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation of CMyMathClassFactory's IClassFactory's Method
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CMyMath* pCMyMath = NULL;
	HRESULT hr;
	// code
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CMyMath class
	pCMyMath = new CMyMath;
	if (pCMyMath == NULL)
		return(E_OUTOFMEMORY);

	// call automation related init method
	pCMyMath->InitInstance();

	// get the requested interface
	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return(hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
	// code
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

// Implementation of IDispatch's methods
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	// code
	// as we have type library it is 1, else 0
	*pCountTypeInfo = 1;
	return(S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
{
	// code
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
		return(DISP_E_BADINDEX);
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	// code
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	MessageBox(NULL, TEXT("Invoke success"), TEXT("Server"), MB_OK);
	// variable declarations
	HRESULT hr;
	// code
	hr = DispInvoke(
		this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);
	return(hr);
}

// Implementation of exported functions from this Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// variable declarations
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;
	// code
	if (rclsid != CLSID_MyMath)
		return(CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// variable declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];
	// code
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&szErrorMessage, 0, NULL) != 0)
	{
		wsprintf(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		wsprintf(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);
	}
	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}
