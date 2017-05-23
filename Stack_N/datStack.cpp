#include <stdio.h>
#include <iostream>
#include "datStack.h"

using namespace std;
/*---------------------------------------------*/
void TStack::Put(const TData &Val) { // положить в стек
	if (pMem == 0) SetRetCode(DataNoMem);
	else if (IsFull()) {
		SetRetCode(DataFull);
		cout << "Стек заполнен" << endl;
	}

	else
	{
		Hi=GetNextIndex(Hi);
		pMem[Hi] = Val;
		DataCount++;
		
	}
	
} // Put
/*---------------------------------------------*/

TData TStack::Get(void) { // взять из стека с удалением
	TData temp = -1;
	if (pMem == NULL) {
		SetRetCode(DataNoMem);
		cout << "Нет свободной памяти" << endl;
	}
	else if (IsEmpty()) {
		SetRetCode(DataEmpty); cout << "Стек пуст" << endl;
	}
	else {
		temp = pMem[Hi--];
		DataCount--;
	}
	return temp;
} // Get
/*---------------------------------------------*/

int TStack::GetNextIndex(int index) { // получить следующее значение  индекса
	return ++index;
} // GetNextIndex
/*---------------------------------------------*/


void TStack::Print() { // печать значений стека
	for (int i = 0; i < DataCount; i++)
		cout << pMem[i] << endl;
}
/*---------------------------------------------*/

int  TStack::IsValid() { // тестирование структуры
	int res = 0;
	if (pMem == NULL)                      res = 1;
	if (MemSize < DataCount)               res += 2;
	return res;
}
/*---------------------------------------------*/

void TStack::CopyToVector(TElem v[]) { // копировать в очередь
	for (int i = 0; i < DataCount; i++)
		v[i] = pMem[i];
}