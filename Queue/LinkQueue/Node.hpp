#pragma once

template<typename ElemType>
class Node
{
public:
	ElemType data;
	Node<ElemType>* next;
public:
	Node();
	Node(const ElemType& elem, Node<ElemType>* nextlink = nullptr);
};

template<typename ElemType>
inline Node<ElemType>::Node()
{
	this->next = nullptr;
}

template<typename ElemType>
inline Node<ElemType>::Node(const ElemType& elem, Node<ElemType>* nextlink)
{
	this->data = elem;
	this->next = nextlink;
}
