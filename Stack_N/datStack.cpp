#include <stdio.h>
#include <iostream>
#include "datStack.h"

using namespace std;
/*---------------------------------------------*/
void TStack::Put(const TData &Val) { // �������� � ����
	if (pMem == 0) SetRetCode(DataNoMem);
	else if (IsFull()) {
		SetRetCode(DataFull);
		cout << "���� ��������" << endl;
	}

	else
	{
		Hi=GetNextIndex(Hi);
		pMem[Hi] = Val;
		DataCount++;
		
	}
	
} // Put
/*---------------------------------------------*/

TData TStack::Get(void) { // ����� �� ����� � ���������
	TData temp = -1;
	if (pMem == NULL) {
		SetRetCode(DataNoMem);
		cout << "��� ��������� ������" << endl;
	}
	else if (IsEmpty()) {
		SetRetCode(DataEmpty); cout << "���� ����" << endl;
	}
	else {
		temp = pMem[Hi--];
		DataCount--;
	}
	return temp;
} // Get
/*---------------------------------------------*/

int TStack::GetNextIndex(int index) { // �������� ��������� ��������  �������
	return ++index;
} // GetNextIndex
/*---------------------------------------------*/


void TStack::Print() { // ������ �������� �����
	for (int i = 0; i < DataCount; i++)
		cout << pMem[i] << endl;
}
/*---------------------------------------------*/

int  TStack::IsValid() { // ������������ ���������
	int res = 0;
	if (pMem == NULL)                      res = 1;
	if (MemSize < DataCount)               res += 2;
	return res;
}
/*---------------------------------------------*/

void TStack::CopyToVector(TElem v[]) { // ���������� � �������
	for (int i = 0; i < DataCount; i++)
		v[i] = pMem[i];
}