#if !defined(LINKSTACK_H_)
#define LINKSTACK_H_

#include"Node.hpp"
#include<iostream>
typedef bool Status;
using namespace std;

template<typename ElemType>
class LinkStack
{
protected:
	Node<ElemType>* top;

public:
	LinkStack();
	LinkStack(const LinkStack<ElemType>& ls);
	virtual ~LinkStack();

	int GetLength()const;
	bool IsEmpty()const;
	void Clear();
	void DisPlay();

	void Recurse(Node<ElemType>* p);

	Status Push(const ElemType& elem);
	Status Pop(ElemType& elem);
	Status Top(ElemType& elem)const;
};

template<typename ElemType>
inline LinkStack<ElemType>::LinkStack()
{
	top = nullptr;
}

template<typename ElemType>
inline LinkStack<ElemType>::LinkStack(const LinkStack<ElemType>& ls)
{
	this->top = nullptr;
	Recurse(ls.top);
}

template<typename ElemType>
inline LinkStack<ElemType>::~LinkStack()
{
	Clear();
}

template<typename ElemType>
inline int LinkStack<ElemType>::GetLength() const
{
	int count = 0;
	for (Node<ElemType>* p = top; p != nullptr; p = p->next)
		count++;
	return count;
}

template<typename ElemType>
inline bool LinkStack<ElemType>::IsEmpty() const
{
	return top == nullptr;
}

template<typename ElemType>
inline void LinkStack<ElemType>::Clear()
{
	while (top != nullptr)
	{
		Node<ElemType>* p = top;
		top = top->next;
		delete p;
	}
}

template<typename ElemType>
inline void LinkStack<ElemType>::DisPlay()
{
	Node<ElemType>* p;
	for ( p = top; p->next!= nullptr; p = p->next)
		cout << p->data << endl;
	cout << p->data;
}

template<typename ElemType>
inline void LinkStack<ElemType>::Recurse(Node<ElemType>* p)
{
	if (p == nullptr)
		return;
	this->Recurse(p->next);
	this->Push(p->data);
}

template<typename ElemType>
inline Status LinkStack<ElemType>::Push(const ElemType& elem)
{
	//Node<ElemType>* p = new Node<ElemType>(elem, top);
	top = new Node<ElemType>(elem, top);
	return true;
}

template<typename ElemType>
inline Status LinkStack<ElemType>::Pop(ElemType& elem)
{
	if (IsEmpty())
	{
		cout << "stack underflow" << endl;
		return false;
	}
	else
	{
		Node<ElemType>* p = top;
		elem = top->data;
		top = top->next;
		delete p;
		return true;
	}
}

template<typename ElemType>
inline Status LinkStack<ElemType>::Top(ElemType& elem) const
{
	if (IsEmpty())
	{
		cout << "stack underflow" << endl;
		return false;
	}
	else
	{
		elem = top->data;
		return true;
	}
}

#endif // LINKSTACK_H_