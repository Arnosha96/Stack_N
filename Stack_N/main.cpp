#include <iostream>
#include "datStack.h"
#include "multistack.h"
#include <conio.h>
#include<stdlib.h>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	/*TStack a(4);
	a.Put(3);
	a.Put(34);
	a.Put(8);
	a.Print();
	cout << a.Get() << endl;
	if (a.IsValid() == 0) cout << "structura OK" << endl;*/
	
	
	TMultiStack b;
    b.Put(0, 10);
	b.Put(0, 8);
	b.Put(0, 7);
	b.Put(0, 45);
	
		
	b.Put(1, 10);
	b.Put(1, 8);
	b.Put(1, 7);		
	b.Put(2, 10);
	b.Put(2, 8);
	b.Put(2, 7);
	b.Put(2, 45);
	b.Put(2, 78);
	b.Put(2, 78);
	b.Put(2, 100);
	b.Put(2, 45);
	b.Put(2, 45);
	b.Get(2);
	b.Get(2);
	b.Get(2);
	b.Put(1, 34);
	cout << "Количество перепаковок " << b.GetRelocationCount() << endl;
	b.Print();
	_getch();
	return 0;
}