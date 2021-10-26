class IMyMath :public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
// CLSID of MyMath Component {5F7FA900-CAD2-4EEB-B422-31B5966A6FC6}
const CLSID CLSID_MyMath = { 0x5f7fa900, 0xcad2, 0x4eeb, 0xb4, 0x22, 0x31, 0xb5, 0x96, 0x6a, 0x6f, 0xc6 };
// IID of ISum Interface {D198D476-CE49-47D2-A5DB-0A40A1D75A96}
const IID IID_IMyMath = { 0xd198d476, 0xce49, 0x47d2, 0xa5, 0xdb, 0xa, 0x40, 0xa1, 0xd7, 0x5a, 0x96 };
