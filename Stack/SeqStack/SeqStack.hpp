#pragma once
typedef bool Status;
using namespace std;
template<typename ElemType>
class SeqStack
{
protected:
	int top;
	int maxSize;
	ElemType* elems;

public:
	SeqStack(int size);
	SeqStack(const SeqStack& st);
	SeqStack<ElemType>& operator=(const SeqStack<ElemType>& st);
	virtual ~SeqStack();

	int GetLength()const;	//求栈的长度
	bool IsEmpty()const;	//判断栈是否为空
	void Clear();			//清空栈
	void Display()const;	//显示栈元素

	Status Push(const ElemType& elem);//入栈
	Status Pop(ElemType& elem); //出栈
	Status Top(ElemType& elem)const;  //取栈顶元素

};


template<typename ElemType>
inline SeqStack<ElemType>::SeqStack(int size)
{
	maxSize = size;
	top = -1;
	if (elems != nullptr)
		delete[] elems;
	elems = new ElemType[maxSize];
}

template<typename ElemType>
inline SeqStack<ElemType>::SeqStack(const SeqStack& st)
{
	this->maxSize = st.maxSize;
	this->top = -1;
	this->elems = new ElemType[this->maxSize];
	for (int i = 0; i <= st.top; i++)
		this->Push(st.elems[i]);

}

template<typename ElemType>
inline SeqStack<ElemType>& SeqStack<ElemType>::operator=(const SeqStack<ElemType>& st)
{
	this->maxSize = st.maxSize;
	this->top = -1;
	if (elems != nullptr)
	{
		delete[] elems;
		elems = nullptr;
	}
	this->elems = new ElemType[this->maxSize];
	for (int i = 0; i <= st.top; i++)
		this->Push(st.elems[i]);
	return *this;
}

template<typename ElemType>
inline SeqStack<ElemType>::~SeqStack()
{
	delete[] elems;
}

template<typename ElemType>
inline int SeqStack<ElemType>::GetLength() const
{
	return top+1;
}

template<typename ElemType>
inline bool SeqStack<ElemType>::IsEmpty() const
{
	return (top==-1);
}

template<typename ElemType>
inline void SeqStack<ElemType>::Clear()
{
	top = -1;
}

template<typename ElemType>
inline void SeqStack<ElemType>::Display() const
{
	for (int i = maxSize - 1; i > top; i--)
		cout << '#' << endl;
	for (int i = top; i > 0; i--)
		cout << elems[i] << endl;
	cout << elems[0] << endl;
}

template<typename ElemType>
inline Status SeqStack<ElemType>::Push(const ElemType& elem)
{
	if (top == maxSize)
	{
		cout << "stack overflow" << endl;
		return false;
	}
	else
	{
		elems[++top] = elem;
		//插入之前top先增加
		return true;
	}
}

template<typename ElemType>
inline Status SeqStack<ElemType>::Pop(ElemType& elem)
{
	if (IsEmpty())
	{
		cout << "stack is empty,nothing can be poped" << endl;
		return false;
	}
	else
	{
		elem = elems[top--];
		//取出之后top再减小
		return true;
	}
}

template<typename ElemType>
inline Status SeqStack<ElemType>::Top(ElemType& elem) const
{
	if (IsEmpty())
		return false;
	else
	{
		elem = elems[top];
		return true;
	}
}