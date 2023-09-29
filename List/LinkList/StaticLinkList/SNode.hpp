//静态链表节点

#pragma once
template<typename ElemType>
struct SNode
{
public:

	ElemType data;
	SNode<ElemType>* next;
	SNode();
	SNode(ElemType elem, SNode<ElemType>* nextlink = nullptr);
};

template<typename ElemType>
SNode<ElemType>::SNode()
{
	this->next = nullptr;
}

template<typename ElemType>
SNode<ElemType>::SNode(ElemType elem, SNode<ElemType>* nextlink)
{
	this->data = elem;
	this->next = nextlink;
}

