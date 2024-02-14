//Ordered顺序表

#pragma once
using namespace std;
template<typename ElemType>
class OSeqList
{
protected:
	int length;
	int maxLength;
	ElemType* elems;

public:
	OSeqList();
	OSeqList(int capacity);
	OSeqList(ElemType* v, int size, int capacity);
	OSeqList(const OSeqList& osl);
	OSeqList<ElemType>& operator=(const OSeqList& osl);
	OSeqList<ElemType> operator+(const OSeqList& osl);
	virtual ~OSeqList();
	
	void Display();
	void OInSertElem(const ElemType& elem);
	void ODeleteElem(const ElemType& elem);
	void DeleteElemInRange(const ElemType& s, const ElemType& t);
};

template<typename ElemType>
inline OSeqList<ElemType>::OSeqList()
{
	maxLength = length = 0;
	elems = nullptr;
}

template<typename ElemType>
inline OSeqList<ElemType>::OSeqList(int capacity)
{
	length = 0;
	maxLength = capacity;
	elems = nullptr;
}

template<typename ElemType>
inline OSeqList<ElemType>::OSeqList(ElemType* v, int size, int capacity)
{
	length = size;
	maxLength = capacity;
	elems = new ElemType[maxLength];
	for (int i = 0; i < length; i++)
		elems[i] = v[i];

	ElemType tmp;
	for (int i = 1; i < length; i++)
	{
		for (int j = 0; j < length - i; j++)
		{
			if (elems[j] > elems[j + 1])
			{
				tmp = elems[j];
				elems[j] = elems[j + 1];
				elems[j + 1] = tmp;
			}
		}
	}
}

template<typename ElemType>
inline OSeqList<ElemType>::OSeqList(const OSeqList& osl)
{
	this->length = osl.length;
	this->maxLength = osl.maxLength;
	this->elems = new ElemType[this->maxLength];
	for (int i = 0; i < this->length; i++)
		elems[i] = osl.elems[i];
}

template<typename ElemType>
inline OSeqList<ElemType>& OSeqList<ElemType>::operator=(const OSeqList& osl)
{
	if (this->elems != nullptr)
	{
		delete[] this->elems;
		this->elems = nullptr;
	}
	this->length = osl.length;
	this->maxLength = osl.maxLength;
	this->elems = new ElemType[this->maxLength];
	for (int i = 0; i < this->length; i++)
		elems[i] = osl.elems[i];

	return *this;
}

template<typename ElemType>
inline OSeqList<ElemType> OSeqList<ElemType>::operator+(const OSeqList& osl)
{
	OSeqList<ElemType> ret;

	ret.maxLength = this->maxLength + osl.maxLength;
	ret.length = this->length + osl.length;
	ret.elems = new ElemType[ret.maxLength];

	ElemType* new_v = new ElemType[ret.length];

	for (int i = 0; i < this->length; i++)
		new_v[i] = this->elems[i];

	for (int i = this->length; i < ret.length; i++)
		new_v[i] = osl.elems[i-this->length];

	ret = OSeqList(new_v, ret.length, ret.maxLength);

	delete[] new_v;
	return ret;
}



template<typename ElemType>
inline OSeqList<ElemType>::~OSeqList()
{
	delete[] elems;
	length = 0;
	maxLength = 0;
}

template<typename ElemType>
inline void OSeqList<ElemType>::Display()
{
	for (int i = 0; i < length - 1; i++)
		cout << elems[i] << ' ';
	cout << elems[length - 1];
	cout << endl;
	cout << this->length << endl;
	cout << this->maxLength << endl;
}

template<typename ElemType>
inline void OSeqList<ElemType>::OInSertElem(const ElemType& elem)
{
	for (int i = 0; i < this->length; i++)
	{
		if (elem >= elems[i] && elem < elems[i+1])
		{
			for (int j = length - 1; j > i; j--)
				elems[j + 1] = elems[j];
		elems[i + 1] = elem;
		break;
		}
	}
	length++;
}

template<typename ElemType>
inline void OSeqList<ElemType>::ODeleteElem(const ElemType& elem)
{
	for (int i = length - 1; i > 0; i--)
	{
		if (elems[i] == elem)
		{
			for (int j = i; j < length; j++)
				elems[j] = elems[j + 1];

			length--;
		}
	}
}

template<typename ElemType>
inline void OSeqList<ElemType>::DeleteElemInRange(const ElemType& s, const ElemType& t)
{
	if (s > t || this->length == 0)
	{
		cout << "删除信息错误" << endl;
		return;
	}
	else
	{
		for (int i = length - 1; i > 0; i--)
		{
			if (elems[i] >= s && elems[i] <= t)
			{
				for (int j = i; j < length; j++)
					elems[j] = elems[j + 1];

				length--;
			}
		}
		cout << "成功删除指定范围的元素" << endl;
	}
	
}