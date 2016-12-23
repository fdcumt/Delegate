
#include <iostream>
#include "TestClassA.h"
#include "TestClassB.h"
#include "TestClassC.h"



int main()
{
	TestA testA;
	TestB testB;
	TestC testC;

	testC.setTestA(&testA);
	testC.addDynamic();
	testC.num = 100;

	testB.b = 99999;

	testA.broadcast(testB);


	system("pause");

	return 0;



}
