#if !defined(ADJLISTNETWORKVEX_HPP_)
#define ADJLISTNETWORKVEX_HPP_

#include "AdjListNetWorkArc.hpp"

// 有向网 邻接表 顶点结点类

template <typename ElemType, typename WeightType>
struct AdjListNetWorkVex
{
    ElemType data;                           // 数据元素值
    AdjListNetWorkArc<WeightType> *firstarc; // 指向弧链表第一个弧结点的指针

    AdjListNetWorkVex();
    AdjListNetWorkVex(ElemType val, AdjListNetWorkArc<WeightType> *adj = nullptr);
};

#endif // ADJLISTNETWORKVEX_HPP_

template <typename ElemType, typename WeightType>
inline AdjListNetWorkVex<ElemType, WeightType>::AdjListNetWorkVex()
{
    firstarc = nullptr;
}

template <typename ElemType, typename WeightType>
inline AdjListNetWorkVex<ElemType, WeightType>::AdjListNetWorkVex(ElemType val, AdjListNetWorkArc<WeightType> *adj)
{
    data = val;
    firstarc = adj;
}
