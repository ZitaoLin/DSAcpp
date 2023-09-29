//单向链表结点

#pragma once
template<typename ElemType>
struct Node
{
public:
	ElemType data;
	Node<ElemType>* next;
public:
	Node();
	Node(ElemType elem, Node<ElemType>* link = nullptr);

};

template<typename ElemType>
Node<ElemType>::Node()
{
	this->next = nullptr;
}

template<typename ElemType>
Node<ElemType>::Node(ElemType elem, Node<ElemType>* link )
{
	this->data = elem;
	this->next = link;
}