#pragma once
#include "TestClassB.h"
class TestA;

class TestC
{
public:
	TestA *pTestA;

	int num;

	void setTestA(TestA *InTestA);
	void addDynamic();

	void funcCallBack(TestB b);

};
