
#include <iostream>
#include "SimpleDelegate/SimpleDelegate.h"
using namespace std;

class MyClass
{
public:
	int a;
	int b;
};

void GloabalFunc(MyClass inClass, int i)
{
	cout <<" GloabalFunc:::: MyClass::a::" << inClass.a << ",MyClass::b::" << inClass.b << ",i::" << i << ":::end" << endl;
}

class Test 
{
public:
	int mmm;
	void funcA(MyClass a, int i) 
	{ 
		cout <<"chengyuan:"<<mmm << "\nfuncA:::: MyClass::a::" << a.a << ",MyClass::b::" << a.b << ",i::"<<i<<":::end" << endl; 
	}
};

class TestA
{
public:
	SimpleMultiDelegate<MyClass> funcOfMemManager;
	int mmm;
	void abc(MyClass a, int i) 
	{ 
		cout << "chengyuan:" << mmm << "\nabc:::: MyClass::a::" << a.a << ",MyClass::b::" << a.b << ",i::" << i << ":::end" << endl;
	}

};



int main()
{
	Test test1;
	TestA test2;
	SimpleMultiDelegate<MyClass, int> test;
	test.SimpleAddDynamic(&test1, &Test::funcA);
	test.SimpleAddDynamic(&test2, &TestA::abc);
	test.SimpleAddDynamic(&GloabalFunc);
	test1.mmm = 10;
	test2.mmm = 777;
	MyClass myClass;
	myClass.a = 1;
	myClass.b = 2;

	test.Broadcast(myClass, 666);

	test.SimpleRemoveDynamic(&test2, &TestA::abc);

	test.Broadcast(myClass, 777);

	test.SimpleRemoveDynamic(&GloabalFunc);
	test.Broadcast(myClass, 888);


	test.SimpleRemoveDynamic(&test1, &Test::funcA);

	test.Broadcast(myClass, 999);

	system("pause");
	return 0;
}