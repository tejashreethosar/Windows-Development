#pragma once

class ISum : public IUnknown
{
	public:
	//ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class ISubtract : public IUnknown
{
	public:
	//ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

//CLSID of SumSubtract Component {78901C94-C926-43F3-AE0F-E9C2BAF4E398} (stringized GUID)
const CLSID CLSID_SumSubtract = { 0x78901c94, 0xc926, 0x43f3, 0xae, 0xf, 0xe9, 0xc2, 0xba, 0xf4, 0xe3, 0x98 }; //(numeric GUID)

//IID of ISum Interface {93A091B0-2E1C-4ECF-B0DD-01C0240E87BD} (stringized GUID)
const IID IID_ISum = { 0x93a091b0, 0x2e1c, 0x4ecf, 0xb0, 0xdd, 0x1, 0xc0, 0x24, 0xe, 0x87, 0xbd }; //(numeric GUID)

//IID of Isubtract Interface // {41B97F20-7532-46B1-8734-C77D8CDC88B7} (stringized GUID)
const IID IID_ISubtract = { 0x41b97f20, 0x7532, 0x46b1, 0x87, 0x34, 0xc7, 0x7d, 0x8c, 0xdc, 0x88, 0xb7 }; //(numeric GUID)