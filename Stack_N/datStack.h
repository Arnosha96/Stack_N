#pragma once
#include "dataroot.h"
#define StackID  101

class TStack : public TDataRoot {
protected:
	int Hi;                              // ������ ���������� �������� ���������
	virtual int GetNextIndex(int index); // �������� ��������� ������
public:
	TStack(int Size = DefMemSize) : TDataRoot(Size) { Hi = -1; }
	virtual void  Put(const TData &Val);  // �������� � ����
	virtual TData Get(void);              // ����� �� ����� � ���������

	// ��������� ������
	virtual int  IsValid();                  // ������������ ���������
	virtual void Print();                    // ������ ��������
	virtual void CopyToVector(TElem v[]);    // ���������� � �������
};