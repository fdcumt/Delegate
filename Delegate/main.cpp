#include <iostream>

using namespace std;


template<typename _ClassName, typename _Param1>
class FuncOfMem
{
public:
	typedef void (_ClassName::*PMemFuncType)(_Param1 param1);

	PMemFuncType m_pFuncMem;
	_ClassName *m_obj;
	_Param1 param1;

	void register(typename _ClassName* pObj, PMemFuncType pFunc)
	{
		m_obj = pObj;
		m_pFuncMem = pFunc;
	}

	void invoke(_Param1 param1)
	{
		pObj->(*pFunc)(param1);
	}

};


class Test
{
public:
	void funcA(int a) { cout <<  " funcA::::" << a<<":::end"<< endl; }

};

int main()
{
	cout << " hello world !!!" << endl;

	Test test1;
	FuncOfMem<Test, int> funcOfMem;
	funcOfMem.register(&test1, &test1::funcA);

	funcOfMem.invoke(3);

#ifdef 1




#endif // 1





	system("pause");
	return 0;
}