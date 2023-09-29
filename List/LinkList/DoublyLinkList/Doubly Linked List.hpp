//双向循环链表（含头节点）

#pragma once
#include"DblNode.hpp"
#include<variant>
using Status = int;

template<typename ElemType>
class DblLinkList
{
protected:
	DblNode<ElemType>* head;
	int length;
public:
	DblLinkList();
	DblLinkList(ElemType v[], int size);
	DblLinkList(const DblLinkList& ll);
	DblLinkList& operator=(const DblLinkList& ll);
	virtual ~DblLinkList();

	int GetLength()const;
	//获取双向链表的当前长度

	bool IsEmpty()const;
	//判断双向链表是否为空

	void Clear();
	//清空双向链表的内容（保留头结点）

	void Traverse(void (*Visit)(const ElemType&))const;
	//遍历双向链表

	int LocateElem(const ElemType& elem);
	//获取指定元素在双向链表中的位置

	Status GetElem(int i, ElemType& elem)const;
	//获取双向链表中第i个元素的值

	Status SetElem(int i, const ElemType& elem);
	//修改双向链表中第i个元素的值

	Status DeleteElem(int i, ElemType& elem);
	//删除双向链表中第i个元素

	Status InsertElem(int i, const ElemType& elem);
	//在双向链表第i个位置插入元素

	Status InsertElem(const ElemType& elem);
	//在双向链表表尾插入元素
};

template<typename ElemType>
DblLinkList<ElemType>::DblLinkList()
{
	head = new DblNode<ElemType>;
	head->prior = head->next = head;
	//初始时，头结点的前驱与后继指针都指向自身
	length = 0;
}

template<typename ElemType>
DblLinkList<ElemType>::DblLinkList(ElemType v[], int size)
{
	DblNode<ElemType>* p;
	p = head = new DblNode<ElemType>;
	for (int i = 0; i < size; i++)
	{
		p->next = new DblNode<ElemType>(v[i], p, nullptr);
		//nullptr作用在于先使得尾结点的next指针置空
		p = p->next;
		//循环结束时p指向尾结点
	}
	length = size;
	head->prior = p;	//头结点的prior指向尾结点
	p->next = head;		//尾结点的next指向头结点，形成闭环
}


template<typename ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList& list)
{
	
}

template<typename ElemType>
DblLinkList<ElemType>& DblLinkList<ElemType>::operator=(const DblLinkList<ElemType>& list)
{
	
}

template<typename ElemType>
DblLinkList<ElemType>::~DblLinkList()
{
	Clear();
	delete head;//头结点一并删除
}

template<typename ElemType>
int DblLinkList<ElemType>::GetLength()const
{
	return length;
}

template<typename ElemType>
bool DblLinkList<ElemType>::IsEmpty()const
{
	return (length == 0);
}

template<typename ElemType>
void DblLinkList<ElemType>::Clear()
{
	ElemType tmpElem;
	while (length > 0)
		DeleteElem(1, tmpElem);
	//只要length>0,就删除当前链表的首结点
	//此操作不会删除头结点

}

template<typename ElemType>
void DblLinkList<ElemType>::Traverse(void (*Visit)(const ElemType&))const
{
	DblLinkList<ElemType>* p;
	for (p = head->next; p != head; p = p->next)
	//从head->next首结点开始，一直到尾结点结束
		visit(p->data);
}


template<typename ElemType>
int DblLinkList<ElemType>::LocateElem(const ElemType& elem)
{
	DblNode<ElemType>* p = head->next;
	//p指向首结点
	int count = 1;
	while (p != head && p->data != elem)
	{
		count++;
		p = p->next;
	}
	//由于尾结点也会遍历到，所以如果没找到，p==head
	if (p != head)
		return count;
	//找到就返回count
	else
		return 0;
}


template<typename ElemType>
Status DblLinkList<ElemType>::GetElem(int i, ElemType& elem)const
{
	DblNode<ElemType>* p = head->next;
	if (i<1 || i> length)
		return false;
	else
	{
		for (int count = 1; count < i; count++)
			p = p->next;
		elem = p->data;
		return true;
	}
}


template<typename ElemType>
Status DblLinkList<ElemType>::SetElem(int i, const ElemType& elem)
{
	DblNode<ElemType>* p = head->next;
	if (i<1 || i> length)
		return false;
	else
	{
		for (int count = 1; count < i; count++)
			p = p->next;
		p->data=elem;
		return true;
	}
}


template<typename ElemType>
Status DblLinkList<ElemType>::DeleteElem(int i, ElemType& elem)
{
	DblNode<ElemType>* p = head->next;
	if (i<1 || i>length)
		return false;
	else
	{
		for (int count = 1; count < i; count++)
			p = p->next;
		//循环结束时，p指向要删除的结点
		p->prior->next = p->next;//p的前驱结点的next指针指向p的后继结点
		p->next->prior = p->prior;//p的后继结点的prior指针指向p的前驱结点
		elem = p->data;
		length--;
		delete p;//释放要删除的结点
		return true;
	}
}


template<typename ElemType>//在第i个结点之 前 插入新结点
Status DblLinkList<ElemType>::InsertElem(int i, const ElemType& elem)
{
	DblNode<ElemType>* p, * q = head->next;
	if (i<1 || i>length + 1)
		return false;
	else
	{
		for (int count = 1; count < i; count++)
			p = p->next;
		//循环结束后 p指向第i个结点
		q = new DblNode<ElemType>(elem, p->prior, p);
		//将新结点q的前驱结点设置为原p结点的前驱结点
		//q的后继结点为p
		p->prior->next = q;
		p->prior = q;
		length++;
		return true;
	}
}


template<typename ElemType>//在表尾插入新结点
Status DblLinkList<ElemType>::InsertElem(const ElemType& elem)
{
	DblNode<ElemType>* p;
	p = new Node<ElemType>(elem, head->prior, head);
	//head->prior为原先链表的尾结点，head为原先链表的头结点
	head->prior->next = p;//将原先的尾结点的后继结点设置为p;
	head->prior = p;//重新设置尾结点，即头结点的前驱结点
	length++;
	return true;
}