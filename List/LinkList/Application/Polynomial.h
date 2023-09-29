#pragma once
#include"Singly Linked List.hpp"
#include"PolyItem.h"

class Polynomial
{
public:
	LinkList<PolyItem> polyList;
public:
	Polynomial() = default;
	Polynomial(PolyItem p[],int size);
	Polynomial(const Polynomial& copy);
	Polynomial(const LinkList<PolyItem>& copyLinkList);
	~Polynomial() = default;

	int Length()const;
	bool IsZero()const;
	void SetZero();
	void Order();
	void Display();
	void InsItem(const PolyItem& pitem);

	Polynomial operator+(const Polynomial& p)const;
	//Polynomial operator-(const Polynomial& p)const;
	Polynomial operator*(const Polynomial& p)const;
	//Polynomial& operator=(const Polynomial& copy);
	//Polynomial& operator=(const LinkList<PolyItem>& copyLinkList);
};

