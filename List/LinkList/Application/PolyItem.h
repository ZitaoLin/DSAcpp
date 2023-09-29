#pragma once
#include<iostream>
using namespace std;

class PolyItem
{
public:
	double coef;
	int expn;
public:
	friend ostream& operator<<(ostream& os,const PolyItem& pi);
	PolyItem() = default;
	PolyItem(double cf, int ep);
	PolyItem(const PolyItem& pi);
	PolyItem& operator=(const PolyItem& pi);
	PolyItem operator+(const PolyItem& pi);
	PolyItem operator-(const PolyItem& pi);
	bool operator!=(const PolyItem& pi);
	~PolyItem() = default;
};



