#pragma once

class ISum :public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;	//pure virtual
};

class ISubtract :public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;	//pure virtual
};

// CLSID of SumSubtract Component {62B32D64-2B89-4B9B-8077-A28F869655F1}
const CLSID CLSID_SumSubtract = { 0x62b32d64, 0x2b89, 0x4b9b, 0x80, 0x77, 0xa2, 0x8f, 0x86, 0x96, 0x55, 0xf1 };

// IID of ISum Interface {D1575866-AF5C-4CD7-A5F2-462B3FC08692}
const IID IID_ISum = { 0xd1575866, 0xaf5c, 0x4cd7, 0xa5, 0xf2, 0x46, 0x2b, 0x3f, 0xc0, 0x86, 0x92 };

// IID of ISubtract Interface {B5B22137-B580-4F92-8FCA-ECC48B9FFEAB}
const IID IID_ISubtract = { 0xb5b22137, 0xb580, 0x4f92, 0x8f, 0xca, 0xec, 0xc4, 0x8b, 0x9f, 0xfe, 0xab };
