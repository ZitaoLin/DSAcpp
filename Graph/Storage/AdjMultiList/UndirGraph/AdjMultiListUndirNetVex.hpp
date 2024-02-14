#if !defined(ADJMULTILISTUNDIRNETVEX_HPP_)
#define ADJMULTILISTUNDIRNETVEX_HPP_

// 无向网 邻接多重表 顶点结点类


#include "AdjMultiListUndirNetArc.hpp"
template <typename ElemType, typename WeightType>
struct AdjMultiListUndirNetVex
{
    ElemType data;
    AdjMultiListUndirNetArc<WeightType> *firstarc;

    AdjMultiListUndirNetVex();
    AdjMultiListUndirNetVex(ElemType val, AdjMultiListUndirNetArc<WeightType> *first = nullptr);
};

#endif // ADJMULTILISTUNDIRNETVEX_HPP_

template <typename ElemType, typename WeightType>
inline AdjMultiListUndirNetVex<ElemType, WeightType>::AdjMultiListUndirNetVex()
{
    firstarc = nullptr;
}

template <typename ElemType, typename WeightType>
inline AdjMultiListUndirNetVex<ElemType, WeightType>::AdjMultiListUndirNetVex(ElemType val, AdjMultiListUndirNetArc<WeightType> *first)
{
    data = val;
    firstarc = first;
}
