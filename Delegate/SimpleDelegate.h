#pragma once



template<class _ClassName, class _Param1>
class FuncOfMem
{

public:
	FuncOfMem()
	{
		m_delegateList.empty();
	}

private:
	typedef void (_ClassName::*PtrMemFuncType)(_Param1 param1);

	struct DelegateObj
	{
		_ClassName *_obj;
		PtrMemFuncType _ptrMemFuncType;
	};

	

public:
	void dynamic_add(_ClassName *pObj, PtrMemFuncType pFunc)
	{
		DelegateObj delegateObj;
		delegateObj._obj = pObj;
		delegateObj._ptrMemFuncType = pFunc;
		m_delegateList.push_back(delegateObj);
	}

	void invoke(_Param1 param1)
	{
		for (int i = 0; i < m_delegateList.size(); ++i)
		{
			DelegateObj& delegateObj = m_delegateList[i];
			(delegateObj._obj->*(delegateObj._ptrMemFuncType))(param1);
		}
	}

private:
	vector<DelegateObj> m_delegateList;
};






