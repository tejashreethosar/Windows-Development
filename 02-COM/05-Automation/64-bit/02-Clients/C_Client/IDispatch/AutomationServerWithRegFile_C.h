#pragma once

#undef INTERFACE
#define INTERFACE IMyMath
DECLARE_INTERFACE_(IMyMath, IDispatch)
{
	//IUnknown specific
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;
	//IDispatch specific
	STDMETHOD(GetTypeInfoCount)(UINT*) PURE;
	STDMETHOD(GetTypeInfo)(UINT, LCID, ITypeInfo**) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, UINT, LCID, DISPID*) PURE;
	STDMETHOD(Invoke)(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*) PURE;
	//IMyMath specific
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

// CLSID of MyMath Component {5F7FA900-CAD2-4EEB-B422-31B5966A6FC6}
const CLSID CLSID_MyMath = { 0x5f7fa900, 0xcad2, 0x4eeb, 0xb4, 0x22, 0x31, 0xb5, 0x96, 0x6a, 0x6f, 0xc6 };
// IID of ISum Interface {D198D476-CE49-47D2-A5DB-0A40A1D75A96}
const IID IID_IMyMath = { 0xd198d476, 0xce49, 0x47d2, 0xa5, 0xdb, 0xa, 0x40, 0xa1, 0xd7, 0x5a, 0x96 };
