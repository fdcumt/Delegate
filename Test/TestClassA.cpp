

#include <iostream>
#include "TestClassA.h"
#include "TestClassB.h"

using namespace std;

void TestA::broadcast(TestB param)
{
	eventTest.Broadcast(param);
}

