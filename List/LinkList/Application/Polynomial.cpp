#include "Polynomial.h"
using std::cout;

Polynomial::Polynomial(PolyItem p[], int size)
{
	Node<PolyItem>* q = polyList.head;
	for (int i = 0; i < size; i++)
	{
		q->next = new Node<PolyItem>(p[i], nullptr);
		q = q->next;
	}
}

Polynomial::Polynomial(const Polynomial& copy)
{
	this->polyList = copy.polyList;
}

Polynomial::Polynomial(const LinkList<PolyItem>& copyLinkList)
{
	this->polyList = copyLinkList;
}

int Polynomial::Length() const
{
	return this->polyList.length;
}

bool Polynomial::IsZero() const
{
	return (this->polyList.length == 0);
}

void Polynomial::SetZero()
{
	this->polyList.Clear();
	//只保留头结点，下次整表重新创建，以便刷新多项式项数（链表长度）
}

void Polynomial::Order()
{
	for (int i = 1; i < this->Length(); i++)
	{
		for (int j = 0; j < this->Length() - i; j++)
		{
			PolyItem a, b;
			polyList.GetElem(j + 1, a);
			polyList.GetElem(j + 2, b);
			if (a.expn < b.expn)
			{
				polyList.SetElem(j + 1, b);
				polyList.SetElem(j + 2, a);
			}
		}
	}
}

void Polynomial::Display()
{
	
	Node<PolyItem>* p = this->polyList.head->next;
	for(int i=0;i<this->Length()-1;i++)
	{
		cout << p->data<<" + ";
		p = p->next;
		//cout << (p->data).coef << "x^" << (p->data).expn << " + ";
		//类似i++
	}
	cout << p->data;
}

void Polynomial::InsItem(const PolyItem& pitem)
{
	this->polyList.InsertElem(pitem);
}

Polynomial Polynomial::operator+(const Polynomial& p) const
{
	LinkList<PolyItem> la = this->polyList;
	LinkList<PolyItem> lb = p.polyList;
	LinkList<PolyItem> lc;
	int aPos = 1, bPos = 1;
	PolyItem aItem, bItem;
	Status aStatus, bStatus;

	aStatus = la.GetElem(aPos++, aItem);
	bStatus = lb.GetElem(bPos++, bItem);

	while (aStatus == true && bStatus == true)
	{
		if (aItem.expn > bItem.expn)
		{
			lc.InsertElem(aItem);;
			aStatus = la.GetElem(aPos++, aItem);
		}
		else if (aItem.expn < bItem.expn)
		{
			lc.InsertElem(bItem);;
			bStatus = lb.GetElem(bPos++, bItem);
		}
		else if (aItem.expn == bItem.expn)
		{
			PolyItem sumItem(aItem.coef + bItem.coef, aItem.expn);
			if (sumItem.coef != 0)
				lc.InsertElem(sumItem);
			aStatus = la.GetElem(aPos++, aItem);
			bStatus = lb.GetElem(bPos++, bItem);
		}
	}

	while (aStatus == true)
	{
		lc.InsertElem(aItem);
		aStatus = la.GetElem(aPos++, aItem);
	}

	while (bStatus == true)
	{
		lc.InsertElem(bItem);
		bStatus = lb.GetElem(bPos++, bItem);
	}

	return Polynomial(lc);
}


Polynomial Polynomial::operator*(const Polynomial& p) const
{
	//多项式相乘展开完成
	Polynomial t1;
	for (int i = 0; i < this->Length(); i++)
	{
		PolyItem ai;
		this->polyList.GetElem(i + 1, ai);
		for (int j = 0; j < p.Length(); j++)
		{
			PolyItem bi;
			p.polyList.GetElem(j + 1, bi);

			PolyItem si(ai.coef * bi.coef, ai.expn + bi.expn);
			t1.polyList.InsertElem(si);
		}
	}
	t1.Order();

	//多项式合并同类项
	Polynomial t2;
	for (int i = 0; i < t1.Length(); i++)
	{
		int nsame_count = 0;
		int same_count = 0;


		PolyItem ea;
		t1.polyList.GetElem(i + 1, ea);
		PolyItem esum(0.0,0);

		for (int j = i+1; j < t1.Length() ; j++)
		{
			PolyItem eb;
			t1.polyList.GetElem(j + 1, eb);
			
			if (ea.expn!=eb.expn)
				nsame_count++;

			if (ea.expn == eb.expn)
			{
				same_count++;
				if (same_count == 1)
					esum = ea + eb;
				else
					esum = esum + eb;
			}

		}
		if (same_count > 1)
			i += (same_count) ;

		if (nsame_count == t1.Length() - t1.polyList.LocateElem(ea))
			t2.polyList.InsertElem(ea);

		if (esum.coef != 0.0)
			t2.polyList.InsertElem(esum);
	}
	return t2;
}





