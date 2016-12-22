#include <iostream>

using namespace std;


template<class _ClassName, class _Param1>
class FuncOfMem
{
public:
	typedef void (_ClassName::*PtrMemFuncType)(_Param1 param1);

	PtrMemFuncType m_ptrMemFuncType;
	_ClassName *m_obj;
	_Param1 param1;

	void mytest(_ClassName *pObj, PtrMemFuncType pFunc)
	{
		m_obj = pObj;
		m_ptrMemFuncType = pFunc;
	}

	void invoke(_Param1 param1)
	{
		(m_obj->*m_ptrMemFuncType)(param1);
	}

};


class Test
{
public:
	int mmm;
	void funcA(int a) { cout << mmm<< " funcA::::" << a<<":::end"<< endl; }

};

int main()
{

	Test test1;
	FuncOfMem<Test, int> funcOfMem;
	funcOfMem.mytest(&test1, &Test::funcA);
	test1.mmm = 10;


	funcOfMem.invoke(3);





	system("pause");
	return 0;
}