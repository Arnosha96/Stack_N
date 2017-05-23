#pragma once
#include "multRoot.h"
#include "dataroot.h"
#include "datStack.h"
#include <stdio.h>
#include "datacom.h"
#include <math.h>
#include <iostream>
#include <iomanip>      // std::setw

typedef int TData;
using namespace std;
class TMultiStack : public TMultiRoot {
protected:
	TStack *pStack[StackNum + 1];
	int FreeMemSize;

protected:
	TElem *pStackMem[StackNum + 1];
	int RelocationCount;
	int StackRelocation(int nst)
	{
		int is, ns, ks, k, res = 0;
		pStack[nst]->DataCount++;//захват памяти для переполненного стека
		//оценка свободной памяти
		//int temp = FreeMemSize;
		FreeMemSize = GetFreeMemSize();
		if (FreeMemSize > -1) {
			res = 1;//свободная память есть - перепаковка
			RelocationCount++;
			//определение нового расположения стеков
			SetStackLocation(pStackMem);
			// перемещение стеков
			for (ns = 0; ns < StackNum; ns++)
			if (pStackMem[ns] < pStack[ns]->pMem){// смещение влево
				for (k = 0; k < pStack[ns]->DataCount; k++)
					pStackMem[ns][k] = pStack[ns]->pMem[k];
				pStack[ns]->SetMem(pStackMem[ns], pStackMem[ns + 1] - pStackMem[ns]);
			}
			else if (pStackMem[ns]>pStack[ns]->pMem){// смещение вправо
				for (ks = ns; pStackMem[ks + 1]>pStack[ks + 1]->pMem; ks++);
				//стек (ks+1) - первый справа, сдвигаемый влево
				for (is = ks; is >= ns; is--){// сдвиг вправо стека is
					for (k = pStack[is]->DataCount - 1; k >= 0; k--)
						pStackMem[is][k] = pStack[is]->pMem[k];
					pStack[is]->SetMem(pStackMem[is], pStackMem[is + 1] - pStackMem[is]);
				}
			}
			else // стек не перемещается - изменение размера
				pStack[ns]->SetMem(pStackMem[ns], pStackMem[ns + 1] - pStackMem[ns]);
		}
		pStack[nst]->DataCount--;//возврат захваченной памяти
		FreeMemSize++;
		return res;
	}
	int GetFreeMemSize(void)
	{
		FreeMemSize = 0;
		for (int i(0); i < StackNum; i++)
		{
			FreeMemSize += pStack[i]->MemSize - pStack[i]->DataCount;
		}
		return FreeMemSize;
	}
	virtual void SetStackLocation(TElem *pStackMem[])
	{
		pStackMem[0] = &Mem[0];
		for (int i(1); i < StackNum; i++)
			pStackMem[i] = pStackMem[i - 1] + pStack[i - 1]->DataCount + (FreeMemSize+1) / StackNum;
		pStackMem[StackNum] = pStack[StackNum]->pMem;
	}



public:
	TMultiStack()
	{
		int StackSize = MemLimit / StackNum;
		int pos = 0;
		for (int i(0); i <= StackNum; i++)
		{
			
			pStack[i] = new TStack(0);
			
			if (i == StackNum - 1) pStack[i]->SetMem(&Mem[pos], MemLimit - pos);
			if (i == StackNum) pStack[i]->SetMem(&Mem[MemLimit], 0);
			else pStack[i]->SetMem(&Mem[pos], StackSize);
			pos += StackSize;
		}

		RelocationCount=0;
		FreeMemSize = MemLimit;
		RetCode = DataOK;
	
	}

	~TMultiStack()
	{
		for (int i(0); i <= StackNum; i++)
			delete pStack[i];
	}

	int IsEmpty(int ns) const
	{
		return pStack[ns]->IsEmpty();
	}

	int IsFull(int ns) const
	{
		return FreeMemSize == 0;
	}

	virtual void Put(int ns, const int &Val)
	{
		SetRetCode(DataOK);
		if (pStack[ns]->IsFull()){

			if (!StackRelocation(ns)) SetRetCode(DataNoMem);
		}
		if (RetCode == DataOK){
			pStack[ns]->Put(Val);
			int Code = pStack[ns]->GetRetCode();
			if (Code == DataOK) FreeMemSize--;
			SetRetCode(Code);
	 		cout << "Стек " << ns << setw(4) << Val << setw(5) << " свободно " << FreeMemSize << endl;
		}
		

	}

	virtual int Get(int ns)
	{
		int temp = pStack[ns]->Get();
		int Code = pStack[ns]->GetRetCode();
		if (Code == DataOK) FreeMemSize++;
		SetRetCode(Code);
		return temp;
	}

	int GetRelocationCount(){ return RelocationCount; }
	

	void Print()
	{
		int i1, i2;
		for (int i(0); i < StackNum; i++)
		{
			i1 = pStack[i]->pMem - &Mem[0];
			i2 = pStack[i + 1]->pMem - &Mem[0] - 1;
			printf("ns=%d, i1=%d, i2=%d, k=%d, m=%d ->", i, i1, i2, pStack[i]->DataCount, pStack[i]->MemSize);
			cout << endl;
			pStack[i]->Print();

			
		}
	}
	
	int IsValid()
	{
		int res = 0;
		int rc;
		for (int i(0); i < StackNum; i++)
		{
			rc = pStack[i]->IsValid();
			if (rc != 0)
			{
				printf("ns=%d, rs=%d\n", rc);
				res = 1;
			}
		}

		rc = 0;
		for (int i(0); i < StackNum; i++)
		{
			rc += (pStack[i + 1]->pMem - pStack[i]->pMem);
		}

		if (rc != MemLimit)
		{
			printf("rc=%d\n", rc);
			res += 2;
		}

		rc = 0;
		for (int i(0); i < StackNum; i++)
		{
			rc += pStack[i]->MemSize;
		}

		if (rc != MemLimit)
		{
			printf("rc=%d\n", rc);
			res += 2;
		}

		rc = 0;

		if ((pStack[0]->pMem < &Mem[0]) || (pStack[0]->pMem < pStack[1]->pMem + pStack[1]->MemSize)) rc=4;

		for (int i(1); i < StackNum; i++)
		{
			if ((pStack[i]->pMem < pStack[i - 1]->pMem + pStack[i - 1]->MemSize) || (pStack[i]->pMem > pStack[i + 1]->pMem + pStack[1]->MemSize)) rc=4;
		}

		if (rc != 0)
		{
			printf("rc=%d\n", rc);
			res += 4;
		}
		return res;
	}
};