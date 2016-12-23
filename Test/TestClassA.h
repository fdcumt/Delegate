#pragma once
#include "SimpleDelegate.h"

class TestB;

class TestA
{

public:
	FuncOfMemManager<TestB> eventTest;

	void broadcast(TestB param);
};

