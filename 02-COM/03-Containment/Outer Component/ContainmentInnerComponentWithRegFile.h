#pragma once

class IMultiplication :public IUnknown
{
public:
	//IMultiplication specific method declarations pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};
class IDivision :public IUnknown
{
public:
	//IDivision specific method declarations pure virtual
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

//CLSID of MultiplicationDivision Component {3515F24E-70B7-4912-8394-1AB928EF8792} //stringised
const CLSID CLSID_MultiplicationDivision = { 0x3515f24e, 0x70b7, 0x4912, 0x83, 0x94, 0x1a, 0xb9, 0x28, 0xef, 0x87, 0x92 }; //numeric

//IID of IMultiplication Interface {A25D33C7-0C10-4EC3-80C3-EA8A8E7BCFA5} //stringised
const IID IID_IMultiplication = { 0xa25d33c7, 0xc10, 0x4ec3, 0x80, 0xc3, 0xea, 0x8a, 0x8e, 0x7b, 0xcf, 0xa5 }; //numeric

//IID of IDivision Interface {8D68D749-7627-469C-8786-AAD688217BDA} //stringised
const IID IID_IDivision = { 0x8d68d749, 0x7627, 0x469c, 0x87, 0x86, 0xaa, 0xd6, 0x88, 0x21, 0x7b, 0xda }; //numeric
