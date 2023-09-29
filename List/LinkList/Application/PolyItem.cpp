#include "PolyItem.h"

PolyItem::PolyItem(double cf, int ep)
{
	this->coef = cf;
	this->expn = ep;
}

PolyItem::PolyItem(const PolyItem& pi)
{
	this->coef = pi.coef;
	this->expn = pi.expn;
}

PolyItem& PolyItem::operator=(const PolyItem& pi)
{
	this->coef = pi.coef;
	this->expn = pi.expn;
	return *this;
}

PolyItem PolyItem::operator+(const PolyItem& pi)
{
	return PolyItem(this->coef+pi.coef,pi.expn);
}

PolyItem PolyItem::operator-(const PolyItem& pi)
{
	return PolyItem(this->coef - pi.coef, pi.expn);
}


bool PolyItem::operator!=(const PolyItem& pi)
{
	if (this->expn != pi.expn)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& os, const PolyItem& pi)
{
	os << pi.coef << "x^" << pi.expn;
	return os;
}
