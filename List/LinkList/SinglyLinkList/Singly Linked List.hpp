//单向非循环链表（含头节点）

#pragma once
#include"Node.hpp"
typedef bool Status;
#include<iostream>
using namespace std;

template<typename ElemType>
class LinkList
{
public:
	Node<ElemType>* head;
	int length;
public:
	LinkList();
	LinkList(ElemType v[], int size);
	LinkList(const LinkList& ll);
	LinkList& operator=(const LinkList& ll);
	virtual ~LinkList();

	int GetLength()const;
	//获取单链表的当前长度

	bool IsEmpty()const;
	//判断单链表是否为空

	void Clear();
	//清空单链表的内容（保留头结点）

	void Display()const;
	//遍历单链表
	
	Node<ElemType>* Locate(int i)const;

	int LocateElem(const ElemType& elem)const;
	//获取指定元素在单链表中的位置

	Status GetElem(int i, ElemType& elem)const;
	//获取单链表中第i个元素的值

	Status SetElem(int i, const ElemType& elem);
	//修改单链表中第i个元素的值

	Status DeleteElem(int i, ElemType& elem);
	//删除单链表中第i个元素

	Status InsertElem(int i, const ElemType& elem);
	//在单链表第i个位置插入元素

	Status InsertElem(const ElemType& elem);
	//在单链表表尾插入元素
};

template<typename ElemType>
LinkList<ElemType>::LinkList()
{
	head = new Node<ElemType>;
	//给头结点创建内存空间，head为指向头结点的指针
	length = 0;
}

template<typename ElemType>
LinkList<ElemType>::LinkList(ElemType v[], int size)
{
	Node<ElemType>* p;
	p = head = new Node<ElemType>;
	for (int i = 0 ; i < size; i++)
	{
		p->next = new Node<ElemType>(v[i], nullptr);
		//下一结点的创建 + 通过next连接两个结点
		//p的next指针 指向的是一个next指针为nullptr的结点
		//当 i == size - 1 时，尾结点的next指针为nullptr 
		p = p->next;
		//指向下一个结点
		//循环结束时，p指向尾结点
	}
	
	//单向循环链表的创建，尾结点的指针指向头结点
	//p->next=head;
	length = size;
}


template<typename ElemType>
LinkList<ElemType>::LinkList(const LinkList& list)
{
	this->length = list.length;
	this->head = new Node<ElemType>(*list.head);
	Node<ElemType>* p = this->head;
	Node<ElemType>* q = list.head->next;
	for (int i = 0; i < this->length; i++)
	{
		p->next = new Node<ElemType>(q->data, nullptr);
		p = p->next;
		q = q->next;
	}
}

template<typename ElemType>
LinkList<ElemType>& LinkList<ElemType>::operator=(const LinkList<ElemType>& list)
{
	if (this->head != nullptr)
	{
		delete this->head;
		this->head = nullptr;
	}
	this->length = list.length;
	this->head = new Node<ElemType>(*list.head);
	Node<ElemType>* p = this->head;
	Node<ElemType>* q = list.head->next;
	for (int i = 0; i < this->length; i++)
	{
		p->next = new Node<ElemType>(q->data, nullptr);
		p = p->next;
		q = q->next;
	}
	return *this;
}

template<typename ElemType>
LinkList<ElemType>::~LinkList()
{
	Clear();
	//释放除头节点以外的结点
	delete head;
	//把头节点也释放了
}

template<typename ElemType>
int LinkList<ElemType>::GetLength()const
{
	return length;
}

template<typename ElemType>
bool LinkList<ElemType>::IsEmpty()const
{
	return (length == 0);
}

template<typename ElemType>
void LinkList<ElemType>::Clear()
{
	Node<ElemType>* p = head->next;		//用指针p接收首节点的内存空间
	while (p != nullptr)
	{
		head->next = p->next;			//头结点的指针接收p指向的下一个结点
		delete p;						//释放原先p指针指向的结点的内存空间
		p = head->next;					//让p指向原先p指向的结点的下一个结点
		//尾结点的next == nullptr，所以在delete尾结点后，循环结束
	}
	//最后只剩下头节点
	length = 0;
}

template<typename ElemType>
void LinkList<ElemType>::Display()const
{
	Node<ElemType>* p = head->next;//首结点
	while (p->next != nullptr)
	{
		cout << p->data << ' ';
		p = p->next;
		//指向下一个结点
	}
	cout << p->data << endl;
}


template<typename ElemType>
inline Node<ElemType>* LinkList<ElemType>::Locate(int loc) const
{
	int count = 0;
	Node<ElemType>* p = head->next;
	while (p != nullptr)
	{
		if (count + 1 == loc)
		{
			return &p;
			break;
		}
		count++;
		p = p->next;
	}

	if(count==length-1)
		return nullptr;
}

template<typename ElemType>
int LinkList<ElemType>::LocateElem(const ElemType& elem)const
{
	Node<ElemType>* p = head->next;
	int count = 1;
	while (p != nullptr && p->data != elem)
	{
		count++;
		p = p->next;
	}
	return (p != nullptr) ? count : 0;
	//一直到尾结点遍历完都没找到就返回0
}


template<typename ElemType>
Status LinkList<ElemType>::GetElem(int i, ElemType& elem)const
{
	if (i<1 || i>length)
		return false;
	else
	{
		Node<ElemType>* p = head->next;
		for (int count = 1; count < i; count++)
			p = p->next;
		elem = p->data;
		return true;
	}
}


template<typename ElemType>
Status LinkList<ElemType>::SetElem(int i, const ElemType& elem)
{
	if (i<1 || i>length)
		return false;
	else
	{
		Node<ElemType>* p = head->next;
		for (int count = 1; count < i; count++)
			p = p->next;
		p->data = elem;
		return true;
	}
}


template <typename ElemType>
Status LinkList<ElemType>::DeleteElem(int i, ElemType &elem)
{
	if (i < 1 || i > length)
		return false;
	else
	{
		Node<ElemType> *p = head; // p初始化为指向头结点的指针
		Node<ElemType> *temp;
		for (int count = 1; count < i; count++)
			p = p->next;   // 一直到p指向要删除的结点的前一个结点为止
		temp = p->next;	   // temp 指向要删除的结点
		elem = temp->data; // temp->data，返回要删除的结点的data
		p->next = temp->next;
		// temp == p->next
		length--;
		delete temp;
		// 释放被删除结点的内存空间，必须得用另外的指针temp承接
	}
}


template<typename ElemType>
Status LinkList<ElemType>::InsertElem(int i, const ElemType& elem)
{
	//在第i个结点之 前 插入结点
	if (i<1 || i>length+1)
		return false;
	else
	{
		Node<ElemType>* p = head;
		Node<ElemType>* temp;//头结点的内存空间
		for (int count = 1; count < i; count++)
			p = p->next;//p指向要插入的结点的前一个结点
		temp = new Node<ElemType>(elem, p->next->next);
		//p->next的结点指针应该是p->next->next
		//p->next->next指向第i个结点
		p->next = temp;
		length++;
		return true;
	}
}


template<typename ElemType>
Status LinkList<ElemType>::InsertElem(const ElemType& elem)
{
	Node<ElemType>* p = head;
	Node<ElemType>* q = new Node<ElemType>(elem, nullptr);
	//q = new Node<ElemType>(elem, head);
	//循环列表表尾结点指针指向头结点
	while (p->next != nullptr)
		p = p->next;
	//不到表尾不停止，因为尾结点的next==nullptr
	p->next = q;//表尾的next接收q，多了一个结点
	length++;
	return true;
}
