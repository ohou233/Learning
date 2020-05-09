#include<iostream>
#include<string>
#include "MyStack.h"
using namespace std;

int main()
{
	MyStack<int>* p = new MyStack<int>(5);
	p->push(1);
	p->push(2);
	p->push(3);
	p->push(4);
	p->push(5);
	//int e = 0;
	//p->pop(e);
	//cout << e << endl;
	//p->ClearStack();
	if (p->StackEmpty())
	{
		cout << "Õ»ÒÑ¿Õ" << endl;
	}
	if(p->StackFull())
	{
		cout << "Õ»ÒÑÂú" << endl;
	}

	p->StackTraverse(false);
	return 0;
}