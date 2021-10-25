#pragma once

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

//CLSID of MultiplicationDivision Component {593030EB-B28C-4110-9B99-A3043D46E644} //stringised
const CLSID CLSID_MultiplicationDivision = { 0x593030eb, 0xb28c, 0x4110, 0x9b, 0x99, 0xa3, 0x4, 0x3d, 0x46, 0xe6, 0x44 }; //numeric

//IID of IMultiplication Interface {00AA8919-4614-44D8-B432-265A5B0FB180} //stringised
const IID IID_IMultiplication = { 0xaa8919, 0x4614, 0x44d8, 0xb4, 0x32, 0x26, 0x5a, 0x5b, 0xf, 0xb1, 0x80 }; //numeric

//IID of IDivision Interface {F074B829-F6BF-427B-9997-4046DFA6DCC7} //stringised
const IID IID_IDivision = { 0xf074b829, 0xf6bf, 0x427b, 0x99, 0x97, 0x40, 0x46, 0xdf, 0xa6, 0xdc, 0xc7 }; //numeric
