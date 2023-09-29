#pragma once
using namespace std;
typedef bool Status;
constexpr auto OK = 1;

template<typename ElemType>
class SeqList
{
protected:
	int length;				//顺序表的当前长度
	int maxLength;			//顺序表的最大长度
	ElemType* elems;		//元素存储空间的首地址

public:
	SeqList(int capacity);	
	//构造空顺序表，最大长度为capacity

	SeqList(ElemType* v, int size, int capacity);	
	//根据数组v的内容构造顺序表，seqlist当前长度为size，seqlist最大长度为capacity

	SeqList(const SeqList& sl);
	//拷贝构造函数

	SeqList<ElemType>& operator=(const SeqList& sl);
	//赋值符号重载

	virtual ~SeqList();
	//析构函数

	int GetLength()const;
	//获取顺序表的当前长度

	bool IsEmpty()const;
	//判断顺序表是否为空

	void Clear();
	//清空顺序表的内容

	void Display()const;
	//遍历顺序表

	int LocateElem(const ElemType& elem);
	//获取指定元素在顺序表中的位置

	Status GetElem(int i, ElemType& elem)const;
	//获取顺序表中第i个元素的值

	Status SetElem(int i,const ElemType& elem);
	//修改顺序表中第i个元素的值

	Status DeleteElem(int i, ElemType& elem);
	//删除顺序表中第i个元素

	ElemType& DeleteMinElem();
	//删除顺序表中值最小的元素，并由最后一个元素填充

	void DeleteAllElem(const ElemType& elem);
	//删除顺序表中值为elem的所有元素

	void DeleteSameElem();
	//删除重复的元素，保留第一个重复的元素

	void Reverse();
	//原地逆置 空间复杂度O(1),内存空间大小始终保持不变

	Status InsertElem(int i, const ElemType& elem);
	//在顺序表第i个位置插入元素

	Status InsertElem(const ElemType& elem);
	//在顺序表表尾插入元素
};

template<typename ElemType>//O(1)
SeqList<ElemType>::SeqList(int capacity)
{
	elems = new ElemType[capacity];
	//assert(elems);
	//申请存储空间失败，程序终止
	maxLength = capacity;
	length = 0;

}

template<typename ElemType>//O(n)
SeqList<ElemType>::SeqList(ElemType* v, int size, int capacity)
{
	elems = new ElemType[capacity];
	maxLength = capacity;
	length = size;
	for (int i = 0; i < length; i++)
		elems[i] = v[i];
}


template<typename ElemType>//O(n)
SeqList<ElemType>::SeqList(const SeqList& sl)
{
	this->length = sl.length;
	this->maxLength = sl.maxLength;
	this->elems = new ElemType[this->maxLength];
	for (int i = 0; i < this->length; i++)
		this->elems[i] = sl.elems[i];
}


template<typename ElemType>//O(n)
SeqList<ElemType>& SeqList<ElemType>::operator=(const SeqList<ElemType>& sl)
{
	if (this->elems != nullptr)
	{
		delete[] this->elems;
		this->elems = nullptr;
	}
	this->length = sl.length;
	this->maxLength = sl.maxLength;
	this->elems = new ElemType[this->maxLength];
	for (int i = 0; i < this->length; i++)
		this->elems[i] = sl.elems[i];
}


template<typename ElemType>//O(1)
SeqList<ElemType>::~SeqList()
{
	delete[] this->elems;
}


template<typename ElemType>//O(1)
int SeqList<ElemType>::GetLength()const
{
	return this->length;
}


template<typename ElemType>//O(1)
bool SeqList<ElemType>::IsEmpty()const
{
	return (this->length == 0);
}


template<typename ElemType>//O(1)
void SeqList<ElemType>::Clear()
{
	this->length = 0;
}


template<typename ElemType>//O(n)
void SeqList<ElemType>::Display()const
{
	for (int i = 0; i < this->length; i++)
		cout << elems[i] << ' ';
	cout << endl;
}


template<typename ElemType>//O(n)
int SeqList<ElemType>::LocateElem(const ElemType& elem)
{
	int i = 0;
	while (i < this->length && elems[i] != elem)
		i++;
	return i < this->length ? i + 1 : 0;
	//元素查找，找到返回位置，找不到返回0
}


template<typename ElemType>//O(1)
Status SeqList<ElemType>::GetElem(int i, ElemType& elem)const
{
	if (i<1 || i>this->length)
		return false;
	else
	{
		elem = elems[i - 1];
		return true;
	}
}


template<typename ElemType>//O(1)
Status SeqList<ElemType>::SetElem(int i, const ElemType& elem)
{
	if (i<1 || i>this->length)
		return false;
	else
	{
		elems[i - 1] = elem;
		return true;
	}
}


template<typename ElemType>//O(n)
Status SeqList<ElemType>::DeleteElem(int i, ElemType& elem)
{
	if (i<1 || i>this->length)
		return false;

	else
	{
		elem = elems[i-1];
		for (int j = i; j < this -> length; j++)
			elems[j - 1] = elems[j];
		this->length--;
		return true;
	}
}

template<typename ElemType>
inline ElemType& SeqList<ElemType>::DeleteMinElem()
{
	ElemType min=elems[0];
	for (int i = 0; i < length; i++)
	{
		if (elems[i] <= min)
			min = elems[i];
	}
	SetElem(LocateElem(min), elems[length - 1]);
	return min;
}

template<typename ElemType>
inline void SeqList<ElemType>::DeleteAllElem(const ElemType& elem)
{
	ElemType tmp;
	for (int i = 0; i < length; i++)
	{
		if (elems[i] == elem)
			DeleteElem(i + 1, tmp);
	}
}

template<typename ElemType>
inline void SeqList<ElemType>::DeleteSameElem()
{
	int same = 0;
	for (int i = 0; i < length; i++)
	{
		ElemType first_same = elems[i];
		for (int j = i + 1; j < length; j++)
		{
			ElemType another_same = elems[j];
			if (first_same == another_same)
				DeleteElem(j + 1, another_same);
		}
	}
}

template<typename ElemType>
inline void SeqList<ElemType>::Reverse()
{
	ElemType* tmp = new ElemType[(length / 2)];

	for (int i = 0; i < (length / 2); i++)
	{
		tmp[i] = this->elems[length-1-i];
		elems[length - 1 - i] = elems[i];
		elems[i] = tmp[i];
	}
	delete[] tmp;
}


template<typename ElemType>//O(n)
Status SeqList<ElemType>::InsertElem(int i, const ElemType& elem)
{
	if (this->length < this->maxLength)
	{
		for (int j = this->length; j >= i; j--)
			elems[j] = elems[j - 1];
		elems[i - 1] = elem;
		this->length++;
		return true;
	}
	else if (i<1 || i>this->length)
		return false;
	else if (this->length == this->maxLength)
		return false;
}


template<typename ElemType>//O(1)
Status SeqList<ElemType>::InsertElem(const ElemType& elem)
{
	if (this->length == this->maxLength)
		return false;
	else
	{
		elems[this->length] = elem;
		this->length++;
		return true;
	}
}