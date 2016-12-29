
#include <iostream>
#include "SimpleDelegate/SimpleDelegate.h"
using namespace std;

class MyClass
{
public:
	int a;
	int b;
};

void GloabalFunc(MyClass inClass)
{
	std::cout<<"GloabalFunc::"<< inClass.a <<endl;
}

class Test 
{
public:
	int mmm;
	void funcA(MyClass a) { cout << mmm<< " funcA::::" << a.a<<"      "<<a.b<<":::end"<< endl; }

};

class TestA
{
public:
	FuncOfMemManager<MyClass> funcOfMemManager;
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
	funcOfMemManager.AddDynamic(&GloabalFunc);
	test1.mmm = 10;
	test2.mmm = 777;
	MyClass myClass;
	myClass.a = 1;
	myClass.b = 2;


	funcOfMemManager.Broadcast(myClass);

	system("pause");
	return 0;
}