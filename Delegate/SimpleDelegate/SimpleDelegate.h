#pragma once

#include <vector>

template< class ..._Param >
class BaseFuncPtr
{
public:
	virtual void invoke(_Param...) = 0;
	virtual bool equal(BaseFuncPtr*) = 0;

public:
	BaseFuncPtr(bool InIsFuncOfMemPtr)
		:m_isFuncOfMemPtr(InIsFuncOfMemPtr)
	{
	}
	virtual ~BaseFuncPtr() {}

public:
	bool m_isFuncOfMemPtr;
};


template< class _ClassName, class ..._Param>
class FuncOfMemPtr : public BaseFuncPtr<_Param...>
{
public:
	typedef void (_ClassName::*PtrFuncOfMem)(_Param...);

public:
	FuncOfMemPtr(_ClassName *InObj, PtrFuncOfMem InPtrFuncOfMem)
		:BaseFuncPtr(true)
	{
		m_obj = InObj;
		m_ptrFuncOfMem = InPtrFuncOfMem;
	}

	virtual bool equal(BaseFuncPtr* InBasePtr) override
	{
		if (InBasePtr->m_isFuncOfMemPtr == m_isFuncOfMemPtr)
		{
			FuncOfMemPtr<_ClassName, _Param...> *ptr = (FuncOfMemPtr<_ClassName, _Param...> *) InBasePtr;
			return m_obj == ptr->m_obj && m_ptrFuncOfMem == ptr->m_ptrFuncOfMem;
		}
		else
		{
			return false;
		}
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
		:BaseFuncPtr(false)
	{
		m_ptrFuncOfNoneMem = InPtrFunc;
	}

	virtual bool equal(BaseFuncPtr* InBasePtr) override
	{
		if (m_isFuncOfMemPtr == InBasePtr->m_isFuncOfMemPtr)
		{
			FuncOfNoneMemPtr<_Param...> *ptr = (FuncOfNoneMemPtr<_Param...> *) InBasePtr;
			return m_ptrFuncOfNoneMem == ptr->m_ptrFuncOfNoneMem;
		}
		else
		{
			return false;
		}
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
class SimpleMultiDelegate
{
public:
	SimpleMultiDelegate()
	{
		m_delegateList.empty();
	}

	~SimpleMultiDelegate()
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
	void SimpleAddDynamic(_ClassName *pObj, void (_ClassName::*pFuncOfMem)(_Param...))
	{
		BaseFuncPtr<_Param...>* ptr = new FuncOfMemPtr<_ClassName, _Param...>(pObj, pFuncOfMem);
		m_delegateList.push_back(ptr);
	}

	template< class _ClassName>
	void SimpleRemoveDynamic(_ClassName *pObj, void (_ClassName::*pFuncOfMem)(_Param...))
	{
		FuncOfMemPtr<_ClassName, _Param...> funcOfMemPtr(pObj, pFuncOfMem);
		BaseFuncPtr<_Param...>* ptr = &funcOfMemPtr;
		for (std::vector<BaseFuncPtr<_Param...>*>::iterator it = m_delegateList.begin(); it != m_delegateList.end(); ++it)
		{
			BaseFuncPtr<_Param...>*item = *it;
			if (item->equal(ptr))
			{
				m_delegateList.erase(it);
				return;
			}
		}
	}

	void SimpleAddDynamic(void(*pFuncOfNoneMem)(_Param...))
	{
		BaseFuncPtr<_Param...>* ptr = new FuncOfNoneMemPtr<_Param...>(pFuncOfNoneMem);
		m_delegateList.push_back(ptr);
	}

	void SimpleRemoveDynamic(void(*pFuncOfNoneMem)(_Param...))
	{
		FuncOfNoneMemPtr<_Param...> funcOfNoneMemPtr(pFuncOfNoneMem);
		BaseFuncPtr<_Param...>* ptr = &funcOfNoneMemPtr;
		for (std::vector<BaseFuncPtr<_Param...>*>::iterator it = m_delegateList.begin(); it != m_delegateList.end(); ++it)
		{
			BaseFuncPtr<_Param...>*item = *it;
			if (item->equal(ptr))
			{
				m_delegateList.erase(it);
				return;
			}
		}
	}

	void Broadcast(_Param... param1)
	{
		for (BaseFuncPtr<_Param...>*& pDelegateItem : m_delegateList)
		{
			pDelegateItem->invoke(param1...);
		}
	}

private:
	std::vector<BaseFuncPtr<_Param...>*> m_delegateList;
};





