class ISum :public IUnknown
{
public:
	//ISum specific method declarations pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};
class ISubtract :public IUnknown
{
public:
	//ISubtract specific method declarations pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
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

//CLSID of SumSubtract Component {BB43F13D-A5C5-4574-9C36-40B8125BD2EF} //stringised
const CLSID CLSID_SumSubtract = { 0xbb43f13d, 0xa5c5, 0x4574, 0x9c, 0x36, 0x40, 0xb8, 0x12, 0x5b, 0xd2, 0xef }; //numeric

//IID of ISum Interface {CB6069B3-7222-464F-BAA8-3CA35A1ED70E} //stringised
const IID IID_ISum = { 0xcb6069b3, 0x7222, 0x464f, 0xba, 0xa8, 0x3c, 0xa3, 0x5a, 0x1e, 0xd7, 0xe }; //numeric

//IID of ISubtract Interface {4AD51440-E378-46E5-9BA9-49FC989E841E} //stringised
const IID IID_ISubtract = { 0x4ad51440, 0xe378, 0x46e5, 0x9b, 0xa9, 0x49, 0xfc, 0x98, 0x9e, 0x84, 0x1e }; //numeric

//IID of IMultiplication Interface {A25D33C7-0C10-4EC3-80C3-EA8A8E7BCFA5} //stringised
const IID IID_IMultiplication = { 0xa25d33c7, 0xc10, 0x4ec3, 0x80, 0xc3, 0xea, 0x8a, 0x8e, 0x7b, 0xcf, 0xa5 }; //numeric

//IID of IDivision Interface {8D68D749-7627-469C-8786-AAD688217BDA} //stringised
const IID IID_IDivision = { 0x8d68d749, 0x7627, 0x469c, 0x87, 0x86, 0xaa, 0xd6, 0x88, 0x21, 0x7b, 0xda }; //numeric