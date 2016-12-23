#include <iostream>
#include <vector>
using namespace std;

template< class _Param >
class BaseFuncOfMem
{
public:
	virtual void invoke(_Param ) = 0;
};


template< class _ClassName, class _Param>
class FuncOfMem : public BaseFuncOfMem<_Param>
{
public:
	typedef void (_ClassName::*PtrFuncOfMem)(_Param);

public:
	FuncOfMem(_ClassName *InObj, PtrFuncOfMem InPtrFuncOfMem)
	{
		m_obj = InObj;
		m_ptrFuncOfMem = InPtrFuncOfMem;
	}

	virtual void invoke(_Param InParam) override
	{
		if (m_obj && m_ptrFuncOfMem)
		{
			(m_obj->*m_ptrFuncOfMem)(InParam);
		}
	}

private:
	_ClassName *m_obj;
	PtrFuncOfMem m_ptrFuncOfMem;
};

template<class _Param1>
class FuncOfMemManager
{
public:
	FuncOfMemManager()
	{
		m_delegateList.empty();
	}

	~FuncOfMemManager()
	{
		for (int i = 0; i < m_delegateList.size(); ++i)
		{
			BaseFuncOfMem<_Param1>* ptr = m_delegateList[i];
			if (ptr)
			{
				delete ptr;
			}
		}
	}

public:
	template< class _ClassName>
	void AddDynamic(_ClassName *pObj, void (_ClassName::*pFuncOfMem)(_Param1 ))
	{
		BaseFuncOfMem<_Param1>* ptr = new FuncOfMem<_ClassName, _Param1>(pObj, pFuncOfMem);
		m_delegateList.push_back(ptr);
	}

	void Broadcast(_Param1 param1)
	{
		for (int i=0; i<m_delegateList.size(); ++i)
		{
			BaseFuncOfMem<_Param1>* ptr = m_delegateList[i];
			ptr->invoke(param1);
		}
	}

private:
	vector<BaseFuncOfMem<_Param1>*> m_delegateList;
};

class MyClass
{
public:
	int a;
	int b;
};

class Test 
{
public:
	int mmm;
	void funcA(MyClass a) { cout << mmm<< " funcA::::" << a.a<<"      "<<a.b<<":::end"<< endl; }

};

class TestA
{
public:
	int mmm;
	void abc(MyClass a) { cout << mmm << " abc::::"  <<a.a << "      " << a.b<< ":::end" << endl; }

};



int main()
{
	Test test1;
	TestA test2;
	FuncOfMemManager<MyClass> funcOfMemManager;
	funcOfMemManager.AddDynamic(&test1, &Test::funcA);
	funcOfMemManager.AddDynamic(&test2, &TestA::abc);
	test1.mmm = 10;
	test2.mmm = 777;
	MyClass myClass;
	myClass.a = 1;
	myClass.b = 2;


	funcOfMemManager.Broadcast(myClass);

	system("pause");
	return 0;
}