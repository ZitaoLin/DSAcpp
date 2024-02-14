#if !defined(ADJMULTILISTDIRNETVEX_HPP_)
#define ADJMULTILISTDIRNETVEX_HPP_

// 有向网 邻接多重表(十字链表) 顶点结点类

#include "AdjMultiListDirNetArc.hpp"

template <typename ElemType, typename WeightType>
struct AdjMultiListDirNetVex
{
    ElemType data;
    AdjMultiListDirNetArc<WeightType> *firstinarc, *firstoutarc;

    AdjMultiListDirNetVex();
    AdjMultiListDirNetVex(ElemType val, AdjMultiListDirNetArc<WeightType> *in = nullptr, AdjMultiListDirNetArc<WeightType> *out = nullptr);
};

#endif // ADJMULTILISTDIRNETVEX_HPP_

template <typename ElemType, typename WeightType>
inline AdjMultiListDirNetVex<ElemType, WeightType>::AdjMultiListDirNetVex()
{

    firstinarc = firstoutarc = nullptr;
}

template <typename ElemType, typename WeightType>
inline AdjMultiListDirNetVex<ElemType, WeightType>::AdjMultiListDirNetVex(ElemType val, AdjMultiListDirNetArc<WeightType> *in, AdjMultiListDirNetArc<WeightType> *out)
{
    data = val;
    firstinarc = in;
    firstoutarc = out;
}
