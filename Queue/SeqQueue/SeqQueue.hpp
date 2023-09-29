//顺序存储的循环队列
#pragma once
#include<iostream>
using namespace std;

typedef bool Status;
template<typename ElemType>
class SeqQueue
{
protected:
	int front, rear;
	int maxSize;
	ElemType* elems;
public:
	SeqQueue(int size);
	SeqQueue(const SeqQueue& sq);
	virtual ~SeqQueue();

	int GetLength()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void Clear();
	void Display()const;
	
	Status DeQueue(ElemType& elem);
	Status EnQueue(const ElemType& elem);
	Status GetHead(ElemType& elem)const;

};

template<typename ElemType>
inline SeqQueue<ElemType>::SeqQueue(int size)
{
	maxSize = size;
	if (elems != nullptr)
		delete[] elems;
	elems = new ElemType[maxSize];
	front = rear = 0;
}

template<typename ElemType>
inline SeqQueue<ElemType>::SeqQueue(const SeqQueue& sq)
{
	this->front = sq.front;
	this->rear = sq.rear;
	this->maxSize = sq.maxSize;
	if (this->elems != nullptr)
	{
		delete[] elems;
		elems = nullptr;
	}
	this->elems = new ElemType[this->maxSize];
	for (int i = front; i != rear; i = (i + 1) % maxSize)
		this->elems[i] = sq.elems[i];
}

template<typename ElemType>
inline SeqQueue<ElemType>::~SeqQueue()
{
	delete[] elems;
}

template<typename ElemType>
inline int SeqQueue<ElemType>::GetLength() const
{
	return (rear - front + maxSize) % maxSize;
}

template<typename ElemType>
inline bool SeqQueue<ElemType>::IsEmpty() const
{
	return (rear == front);
}

template<typename ElemType>
inline bool SeqQueue<ElemType>::IsFull() const
{
	return ((rear+1)%maxSize==front);
}

template<typename ElemType>
inline void SeqQueue<ElemType>::Clear()
{
	front = rear = 0;
}

template<typename ElemType>
inline void SeqQueue<ElemType>::Display() const
{
	if (rear < front)
	{
		for (int i = 0; i < rear ; i++)
			cout << elems[i] << ' ';
		for (int i = rear ; i < front; i++)
			cout << '*' << ' ';
		for (int i = front; i < maxSize - 1; i++)
			cout << elems[i] << ' ';
		cout << elems[maxSize - 1];

	}

	else if (rear > front)
	{
		for (int i = 0; i < front; i++)
			cout << '*' << ' ';
		for (int i = front; i < rear; i++)
			cout << elems[i] << ' ';
		for(int i=rear;i<maxSize;i++)
			cout << '*';
	}

	else if (rear == front)
		cout << "queue's empty";
}

template<typename ElemType>
inline Status SeqQueue<ElemType>::DeQueue(ElemType& elem)
{
	if (!IsEmpty())
	{
		elem = elems[front];
		front = (front + 1) % maxSize;
		return true;
	}
	else
	{
		cout << "queue underflow" << endl;
		return false;
	}
}

template<typename ElemType>
inline Status SeqQueue<ElemType>::EnQueue(const ElemType& elem)
{
	if (IsFull())
	{
		cout << "queue overflow" << endl;
		return false;
	}
	else
	{
		elems[rear] = elem;
		rear = (rear + 1) % maxSize;
		return true;
	}
}

template<typename ElemType>
inline Status SeqQueue<ElemType>::GetHead(ElemType& elem) const
{
	if (!IsEmpty())
	{
		elem = elems[front];
		return true;
	}
	else
	{
		cout << "queue's empty,not head elem" << endl;
		return false;
	}
}