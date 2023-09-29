#pragma once
typedef bool Status;
using namespace std;
template<typename ElemType>
class DESeqStack
{
protected:
	int size;
	int top1;
	int top2;
	ElemType* elems;
public:
	DESeqStack(int capacity);
	virtual ~DESeqStack();

	int GetLength()const;	//求栈的长度
	bool IsEmpty()const;	//判断栈是否为空
	void Clear();			//清空栈
	void Display()const;	//显示栈元素

	Status Push(const ElemType& elem,int num);//入栈
	Status Pop(ElemType& elem,int num); //出栈
	Status Top(ElemType& elem,int num)const;  //取栈顶元素
};


template<typename ElemType>
inline DESeqStack<ElemType>::DESeqStack(int capacity)
{
	this->size = capacity;
	this->top1 = -1;
	this->top2 = this->size;
	elems = new ElemType[size];
}

template<typename ElemType>
inline DESeqStack<ElemType>::~DESeqStack()
{
	delete[] elems;
}

template<typename ElemType>
inline int DESeqStack<ElemType>::GetLength() const
{
	return (top1+1)+(size-top2);
}

template<typename ElemType>
inline bool DESeqStack<ElemType>::IsEmpty() const
{
	return (top1 == -1 && top2 == size);
}

template<typename ElemType>
inline void DESeqStack<ElemType>::Clear()
{
	top1 = -1;
	top2 = size;
}

template<typename ElemType>
inline void DESeqStack<ElemType>::Display() const
{
	for (int i = 0; i <= top1; i++)
		cout << elems[i] << ' ';
	for (int i = top1 + 1; i < top2; i++)
		cout << '*' << ' ';
	for (int i = top2; i < size - 1; i++)
		cout << elems[i] << ' ';
	cout << elems[size - 1];

	cout << endl;
}

template<typename ElemType>
inline Status DESeqStack<ElemType>::Push(const ElemType& elem, int num)
{
	if (top1 == top2 - 1)
	{
		cout << "stack overflow" << endl;
		return false;
	}

	else if (num == 1)
	{
		elems[++top1] = elem;
		return true;
	}

	else if (num == 2)
	{
		elems[--top2] = elem;
		return true;
	}
}

template<typename ElemType>
inline Status DESeqStack<ElemType>::Pop(ElemType& elem, int num)
{
	if (IsEmpty())
	{
		cout << "stack's empty,nothing can be poped" << endl;
		return false;
	}

	else if (num == 1)
	{
		elem = elems[top1--];
		return true;
	}
	
	else if (num == 2)
	{
		elem = elems[top2++];
		return true;
	}
}

template<typename ElemType>
inline Status DESeqStack<ElemType>::Top(ElemType& elem, int num) const
{
	if (IsEmpty())
	{
		cout << "stack's emty,top elem do not exist" << endl;
		return false;
	}

	else if (num == 1)
	{
		elem = elems[top1];
		return true;
	}

	else if (num == 2)
	{
		elem = elems[top2];
		return true;
	}
}