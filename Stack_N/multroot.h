#pragma once
#include "datacom.h"
#include "dataroot.h"

#define MemLimit  15  // ������ ������
#define StackNum   3  // ���������� ������

class TMultiRoot : public TDataCom  {
protected:
	TElem Mem[MemLimit]; // ������ ��� ������
	int DefaultStack;    // ����� �������� �����
public:
	TMultiRoot() { DefaultStack = 0; }
	virtual int  IsEmpty(int ns) const = 0; // �������� ������� ��
	virtual int  IsFull(int ns) const = 0; // �������� ������������ ��
	virtual void Put(int ns, const TData &Val) = 0; // �������� � ����
	virtual TData Get(int ns) = 0;       // ����� �� ����� � ���������
	// ������ ��� ������ � ������� ������
	void SetDefaultStack(int ns){ DefaultStack = ns; } // ������� ����
	int  IsEmpty(void) const      { return IsEmpty(DefaultStack); } // ���� ?
	int  IsFull(void) const      { return IsFull(DefaultStack); } // ����� ?
	void Put(const TData &Val)  { Put(DefaultStack, Val); }     // � ����
	virtual TData Get(void)       { return Get(DefaultStack); }     // �� �����
};
