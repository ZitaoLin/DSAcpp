//双向链表的结点

#pragma once
template<typename ElemType>
struct DblNode
{
protected:
	ElemType data;
	DblNode* prior;
	DblNode* next;
public:
	DblNode();
	DblNode(ElemType elem, DblNode* priorlink=nullptr, DblNode* nextlink=nullptr);
};

template<typename ElemType>
DblNode<ElemType>::DblNode()
{
	this->prior = nullptr;
	this->next = nullptr;
}

template<typename ElemType>
DblNode<ElemType>::DblNode(ElemType elem, DblNode* priorlink, DblNode* nextlink)
{
	data = elem;
	prior = priorlink;
	next = nextlink;
}