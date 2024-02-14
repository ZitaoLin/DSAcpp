#if !defined(UFSET_HPP_)
#define UFSET_HPP_

#include <cmath>
#include "UFNode.hpp"

template <typename ElemType>
class UFSet
{
protected:
    UFNode<ElemType> *set; // 结点数组
    int size;              // 结点数组长度

    int Find(ElemType elem) const;           // 查找元素elem所在等价类的根结点
    int CollapsingFind(ElemType elem) const; //! 使用折叠规则压缩查找路径的查找算法

public:
    UFSet(ElemType es[], int n);
    virtual ~UFSet();
    ElemType GetElem(int pos) const;            // 根据下标p取元素值
    int GetOrder(ElemType elem) const;          // 取指定元素在数组中的下标
    void WeightedUnion(ElemType a, ElemType b); //! 按元素数量合并元素a、b所在的等价类
    bool Differ(ElemType a, ElemType b);        //! 判断a、b是否在同一个等价类
};

#endif // UFSET_HPP_

template <typename ElemType>
inline int UFSet<ElemType>::Find(ElemType elem) const
{
    int p = 0;
    while (p < size && set[p].data != elem)
        p++;
    if (p == size)
        return -1; // 集合中不存在元素elem

    while (set[p].parent > -1)
        p = set[p].parent;
    return p;
}

template <typename ElemType>
inline int UFSet<ElemType>::CollapsingFind(ElemType elem) const
//! 优化：把查找路径下的所有结点(包括elem)挂到根结点上
{
    int i, k, p = 0;
    // 遍历至元素elem的数组下标p
    while (p < size && sets[p].data != elem)
        p++;
    if (p == size)
        return -1;

    // 查找元素elem所在等价类的根结点的数组下标i
    for (i = p; set[i].parent >= 0; i = set[i].parent)
        ;

    
    while (i != set[p].parent)
    {
        k = set[p].parent;
        set[p].parent = i;
        p = k;
    }
    return i;
}

template <typename ElemType>
inline UFSet<ElemType>::UFSet(ElemType es[], int n)
{
    size = n;
    set = new UFNode<ElemType>[size];
    for (int i = 0; i < size; i++)
    {
        set[i].data = es[i];
        set[i].parent = -1;
    }
}

template <typename ElemType>
inline UFSet<ElemType>::~UFSet()
{
    delete[] set;
}

template <typename ElemType>
inline ElemType UFSet<ElemType>::GetElem(int pos) const
{
    return set[pos - 1].data;
}

template <typename ElemType>
inline int UFSet<ElemType>::GetOrder(ElemType elem) const
{
    int p = 0;
    while (p < size && set[p].data != elem)
        p++;
    if (p == size)
        return -1;
    else
        return p;
}

template <typename ElemType>
inline void UFSet<ElemType>::WeightedUnion(ElemType a, ElemType b)
{
    int r1 = Find(a);
    int r2 = Find(b);
    if (r1 != r2 && r1 != -1 && r2 != -1)
    {
        //! 优化：把结点树少的树合并到结点数多的树上 合并后高度为大树的高度
        if (abs(set[r1].parent) <= abs(set[r2].parent))
        {
            set[r2].parent += set[r1].parent;
            set[r1].parent = r2;
        }
        else
        {
            set[r1].parent += set[r2].parent;
            set[r2].parent = r1;
        }
    }
}

template <typename ElemType>
inline bool UFSet<ElemType>::Differ(ElemType a, ElemType b)
{
    return Find(a) != Find(b) ? 1 : 0;
}
