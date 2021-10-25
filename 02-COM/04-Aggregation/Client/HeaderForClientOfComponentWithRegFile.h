class ISum :public IUnknown
{
public:
	//ISum specific method declarations pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;			//pure virtual
};
class ISubtract :public IUnknown
{
public:
	//ISubtract specific method declarations pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;	//pure virtual
};
class IMultiplication :public IUnknown
{
public:
	//IMultiplication specific method declarations pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;	//pure virtual
};
class IDivision :public IUnknown
{
public:
	//IDivision specific method declarations pure virtual
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;	//pure virtual
};

//CLSID of SumSubtract Component {FFF7288D-379C-46C9-BDFA-51E93BFB3607} //stringised
const CLSID CLSID_SumSubtract = { 0xfff7288d, 0x379c, 0x46c9, 0xbd, 0xfa, 0x51, 0xe9, 0x3b, 0xfb, 0x36, 0x7 }; //numeric

//IID of ISum Interface {3E9952D2-A338-4EB0-8A4E-547158C5AF8F} //stringised
const IID IID_ISum = { 0x3e9952d2, 0xa338, 0x4eb0, 0x8a, 0x4e, 0x54, 0x71, 0x58, 0xc5, 0xaf, 0x8f }; //numeric

//IID of ISubtract Interface {0D8358B8-20EF-45B7-9DAB-8864747E7AA5} //stringised
const IID IID_ISubtract = { 0xd8358b8, 0x20ef, 0x45b7, 0x9d, 0xab, 0x88, 0x64, 0x74, 0x7e, 0x7a, 0xa5 }; //numeric

//CLSID of MultiplicationDivision Component {593030EB-B28C-4110-9B99-A3043D46E644} //stringised
const CLSID CLSID_MultiplicationDivision = { 0x593030eb, 0xb28c, 0x4110, 0x9b, 0x99, 0xa3, 0x4, 0x3d, 0x46, 0xe6, 0x44 }; //numeric

//IID of IMultiplication Interface {00AA8919-4614-44D8-B432-265A5B0FB180} //stringised
const IID IID_IMultiplication = { 0xaa8919, 0x4614, 0x44d8, 0xb4, 0x32, 0x26, 0x5a, 0x5b, 0xf, 0xb1, 0x80 }; //numeric

//IID of IDivision Interface {F074B829-F6BF-427B-9997-4046DFA6DCC7} //stringised
const IID IID_IDivision = { 0xf074b829, 0xf6bf, 0x427b, 0x99, 0x97, 0x40, 0x46, 0xdf, 0xa6, 0xdc, 0xc7 }; //numeric