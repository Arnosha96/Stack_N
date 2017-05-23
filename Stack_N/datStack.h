#pragma once
#include "dataroot.h"
#define StackID  101

class TStack : public TDataRoot {
protected:
	int Hi;                              // индекс последнего элемента структуры
	virtual int GetNextIndex(int index); // получить следующий индекс
public:
	TStack(int Size = DefMemSize) : TDataRoot(Size) { Hi = -1; }
	virtual void  Put(const TData &Val);  // положить в стек
	virtual TData Get(void);              // взять из стека с удалением

	// служебные методы
	virtual int  IsValid();                  // тестирование структуры
	virtual void Print();                    // печать значений
	virtual void CopyToVector(TElem v[]);    // копировать в очередь
};