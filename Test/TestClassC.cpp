#include "TestClassC.h"
#include "TestClassA.h"
#include <iostream>


void TestC::setTestA(TestA *InTestA)
{
	pTestA = InTestA;
}

void TestC::addDynamic()
{
	pTestA->eventTest.AddDynamic(this, &TestC::funcCallBack);
}

void TestC::funcCallBack(TestB b)
{
	std::cout << " this func is TestC::funcCallBack -> " << b.b << std::endl;
	std::cout << " owner class member is::: -> " << num << std::endl;
}

