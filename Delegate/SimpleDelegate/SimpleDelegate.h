#pragma once


/*
	使用的时候请注明来源 
	author: fuzongqiong
	github: https://github.com/fdcumt/Delegate
*/




#include <vector>

template< class ..._Param >
class BaseFuncPtr
{
public:
	virtual void invoke(_Param...) = 0;
	virtual ~BaseFuncPtr() {}
};
  

template< class _ClassName, class ..._Param>
class FuncOfMemPtr : public BaseFuncPtr<_Param...>
{
public:
	typedef void (_ClassName::*PtrFuncOfMem)(_Param...);

public:
	FuncOfMemPtr(_ClassName *InObj, PtrFuncOfMem InPtrFuncOfMem)
	{
		m_obj = InObj;
		m_ptrFuncOfMem = InPtrFuncOfMem;
	}

	virtual void invoke(_Param... InParam) override
	{
		if (m_obj && m_ptrFuncOfMem)
		{
			(m_obj->*m_ptrFuncOfMem)(InParam...);
		}
	}

private:
	_ClassName *m_obj;
	PtrFuncOfMem m_ptrFuncOfMem;
};

template<class ..._Param>
class FuncOfNoneMemPtr : public BaseFuncPtr<_Param...>
{
public:
	typedef void(*PtrOfNoneFunc)(_Param...);

public:
	FuncOfNoneMemPtr(PtrOfNoneFunc InPtrFunc)
	{
		m_ptrFuncOfNoneMem = InPtrFunc;
	}

	virtual void invoke(_Param... InParam) override
	{
		if (m_ptrFuncOfNoneMem)
		{
			(*m_ptrFuncOfNoneMem)(InParam...);
		}
	}

private:
	PtrOfNoneFunc m_ptrFuncOfNoneMem;
};

template<class ..._Param>
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
			BaseFuncPtr<_Param...>* ptr = m_delegateList[i];
			if (ptr)
			{
				delete ptr;
			}
		}
	}

public:
	template< class _ClassName>
	void AddDynamic(_ClassName *pObj, void (_ClassName::*pFuncOfMem)(_Param...))
	{
		BaseFuncPtr<_Param...>* ptr = new FuncOfMemPtr<_ClassName, _Param...>(pObj, pFuncOfMem);
		m_delegateList.push_back(ptr);
	}

	void AddDynamic(void (*pFuncOfNoneMem)(_Param...))
	{
		BaseFuncPtr<_Param...>* ptr = new FuncOfNoneMemPtr<_Param...>(pFuncOfNoneMem);
		m_delegateList.push_back(ptr);
	}

	void Broadcast(_Param... param1)
	{
		for (int i = 0; i < m_delegateList.size(); ++i)
		{
			BaseFuncPtr<_Param...>* ptr = m_delegateList[i];
			ptr->invoke(param1...);
		}
	}

private:
	std::vector<BaseFuncPtr<_Param...>*> m_delegateList;
};
