#pragma once
#include "../Delegate/SimpleDelegate/SimpleDelegate.h"

class TestB;

class TestA
{

public:
	FuncOfMemManager<TestB> eventTest;

	void broadcast(TestB param);
};

