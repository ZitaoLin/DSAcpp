#pragma once
//链式非循环队列（FIFO的链表）
#include"Node.hpp"
#include<iostream>
using namespace std;
typedef bool Status;

template<typename ElemType>
class LinkQueue
{
protected:
	Node<ElemType>* front;
	Node<ElemType>* rear;
	//front相当于链表中指向头结点的头指针
	//就像 i = -1
public:
	LinkQueue();
	virtual ~LinkQueue();
	LinkQueue(const LinkQueue<ElemType>& lq);
	//LinkQueue<ElemType>& operator=(const LinkQueue<ElemType>& lq);

	int GetLength()const;
	bool IsEmpty()const;
	void Clear();
	void Display()const;

	Status EnQueue(const ElemType& elem);
	Status DeQueue(ElemType& elem);
	Status GetHead(ElemType& elem)const;
};

template<typename ElemType>
inline LinkQueue<ElemType>::LinkQueue()
{
	front = new Node<ElemType>();
	rear = front;
}

template<typename ElemType>
inline LinkQueue<ElemType>::~LinkQueue()
{
	Clear();
	delete front;
}

template<typename ElemType>
inline LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType>& lq)
{
	this->front = this->rear = new Node<ElemType>;
	Node<ElemType>* p = lq.front->next;
	for (int i = 0; i < lq.GetLength(); i++)
	{
		this->EnQueue(p->data);
		p = p->next;
	}
}

template<typename ElemType>
inline int LinkQueue<ElemType>::GetLength() const
{
	int count = 0;
	Node<ElemType>* p ;
	for (p = front->next; p != nullptr; p = p->next)
		//rear->next == nullptr
		count++;
	return count;

}

template<typename ElemType>
inline bool LinkQueue<ElemType>::IsEmpty() const
{
	return front==rear;
}

template<typename ElemType>
inline void LinkQueue<ElemType>::Clear()
{
	Node<ElemType>* p=front->next;
	while (p != nullptr)
	{
		front->next = p->next;
		//再delete内存空间前，记录下其原有数据
		delete p;
		p = front->next;
	}
	//过程类似front->next顺着链式关系向前推进
	//一路推进，一路delete链表原有的内存空间
	rear = front;
}

template<typename ElemType>
inline void LinkQueue<ElemType>::Display() const
{
	Node<ElemType>* p = front->next;
	for (p = front->next; p != rear; p = p->next)
		cout << p->data << ' ';
	cout << p->data << endl;

}

template<typename ElemType>
inline Status LinkQueue<ElemType>::EnQueue(const ElemType& elem)
{
	Node<ElemType>* q = new Node<ElemType>(elem, nullptr);
	rear->next = q;
	rear = rear->next;
	return true;
}

template<typename ElemType>
inline Status LinkQueue<ElemType>::DeQueue(ElemType& elem)
{
	if (IsEmpty())
	{
		cout << "queue underflow" << endl;
		return false;
	}
	else
	{
		elem = front->next->data;
		Node<ElemType>* temp = front->next;
		front->next = temp->next;
		if (rear == temp)
			rear = front;//只有一个元素的队列在删除头元素前要让rear==front
		delete temp;
		return true;
	}
}

template<typename ElemType>
inline Status LinkQueue<ElemType>::GetHead(ElemType& elem) const
{
	if (IsEmpty())
	{
		cout << "queue underflow,not head elem" << endl;
		return false;
	}
	else
	{
		elem = front->next->data;
		return true;
	}
}