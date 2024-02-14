//静态链表（含头节点）

#pragma once
#include"SNode.hpp"
using namespace std;
using Status = int;

const int length = 10;
template<typename ElemType>
class SLinkList
{
public:
	SNode<ElemType>* head;
	SNode<ElemType>* avail[length];

public:
	SLinkList();
	SLinkList(ElemType v[]);
	virtual ~SLinkList();

	bool IsEmpty()const;

	void Clear();

	void Traverse()const;

	int LocateElem(const ElemType& elem);

	Status GetElem(int i, ElemType& elem)const;

	Status SetElem(int i, const ElemType& elem);

	Status DeleteElem(int i, ElemType& elem);

	Status InsertElem(int i,const ElemType& elem);

};

template<typename ElemType>
SLinkList<ElemType>::SLinkList()
{
	head = new SNode<ElemType>;
	for (int i = 0; i < length; i++)
		avail[i] = new SNode<ElemType>;
	head->next = avail[0];
}

template<typename ElemType>
SLinkList<ElemType>::SLinkList(ElemType v[])
{
	head = new SNode<ElemType>;
	
	for (int i = 0; i < length; i++)
		avail[i] = new SNode<ElemType>(v[i], nullptr);

	for (int i = 0; i < length-1; i++)
		avail[i]->next = avail[i + 1];

	head->next = avail[0];
}



template<typename ElemType>
SLinkList<ElemType>::~SLinkList()
{
	Clear();
	delete head;
}


template<typename ElemType>
bool SLinkList<ElemType>::IsEmpty()const
{
	return (length == 0);
}

template<typename ElemType>
void SLinkList<ElemType>::Clear()
{
	for (int i = 0; i < length; i++)
		delete avail[i];
}

template<typename ElemType>
void SLinkList<ElemType>::Traverse()const
{
	for (int i = 0; i < length; i++)
	{
		if (avail[i] == nullptr)
			cout << 0 << ' ';
		else
			cout << avail[i]->data << ' ';
	}
}


template<typename ElemType>
int SLinkList<ElemType>::LocateElem(const ElemType& elem)
{
	int index = 0;
	for (int i = 0; i < length; i++)
	{
		if (avail[i]->data == elem)
		{
			index = i + 1;
			break;
		}
	}
	return index;
}


template<typename ElemType>
Status SLinkList<ElemType>::GetElem(int i, ElemType& elem)const
{
	if (i<1 || i>length)
		return false;
	else
	{
		elem = avail[i - 1]->data;
		return avail;
	}

}


template<typename ElemType>
Status SLinkList<ElemType>::SetElem(int i, const ElemType& elem)
{
	if (i<1 || i>length)
		return false;
	else
	{
		avail[i - 1]->data = elem;
		return true;
	}
}


template<typename ElemType>
Status SLinkList<ElemType>::DeleteElem(int i, ElemType& elem)
{
	if (i<1 || i>length)
		return false;
	else
	{
		elem = avail[i - 1]->data;
		if (i == 1)
		{
			head->next = avail[i];

			delete avail[i - 1];
			avail[i - 1] = nullptr;
		}
		if (i > 1 && i < length)
		{
			avail[i - 2]->next = avail[i];

			delete avail[i - 1];
			avail[i - 1] = nullptr;
		}
		if (i == length)
		{
			avail[i - 2]->next = nullptr;

			delete avail[i - 1];
			avail[i - 1] = nullptr;
		}
		return true;
	}
}

template<typename ElemType>
Status SLinkList<ElemType>::InsertElem(int i,const ElemType& elem)
{
	if (i<2 || i>length)
		return false;

	int count = 0;
	for (int i = 0; i < length; i++)
	{
		if (avail[i] == nullptr)
			count++;
	}

	if (count > 0)
	{
		SNode<ElemType>* q = new SNode<ElemType>(elem, nullptr);
		if (i == 2)
		{
			q->next = avail[i - 1];
			head->next = q;
			avail[i - 2] = q;
		}
		if (i > 2 && i <= length)
		{
			q->next = avail[i - 1];
			avail[i - 3]->next = q;
			avail[i - 2] = q;
		}
		return true;
	}
	else
		return false;
}


