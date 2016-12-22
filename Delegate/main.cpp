#include <iostream>
#include <vector>
using namespace std;


template<class _ClassName, class _Param1>
class FuncOfMem
{

public:
	FuncOfMem()
	{
		m_delegateList.empty();
	}

public:
	typedef void (_ClassName::*PtrMemFuncType)(_Param1 param1);

	struct DelegateObj
	{
		_ClassName *_obj;
		PtrMemFuncType _ptrMemFuncType;
	};

	vector<DelegateObj> m_delegateList;

	void dynamic_add(_ClassName *pObj, PtrMemFuncType pFunc)
	{
		DelegateObj delegateObj;
		delegateObj._obj = pObj;
		delegateObj._ptrMemFuncType = pFunc;
		m_delegateList.push_back(delegateObj);
	}

	void invoke(_Param1 param1)
	{
		for (int i=0; i<m_delegateList.size(); ++i)
		{
			DelegateObj& delegateObj = m_delegateList[i];
			(delegateObj._obj->*(delegateObj._ptrMemFuncType))(param1);
		}
	}

};

class baseClass
{
public:

};

class Test :public baseClass
{
public:
	int mmm;
	void funcA(int a) { cout << mmm<< " funcA::::" << a<<":::end"<< endl; }

};

int main()
{

	typedef void (baseClass::*ffffffff)(int);;

	Test test1;
	Test test2;
	FuncOfMem<baseClass, int> funcOfMem;
	funcOfMem.dynamic_add(&test1, static_cast<ffffffff> (&Test::funcA));
	funcOfMem.dynamic_add(&test2, static_cast<ffffffff> (&Test::funcA));
	test1.mmm = 10;
	test2.mmm = 11;


	funcOfMem.invoke(3);

	system("pause");
	return 0;
}