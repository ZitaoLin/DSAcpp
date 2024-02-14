#if !defined(ADJMULTILISTDIRNETARC_HPP_)
#define ADJMULTILISTDIRNETARC_HPP_

// 有向网 邻接多重表（十字链表）弧结点类

#define Status bool
template <typename WeightType>
struct AdjMultiListDirNetArc
{
    Status tag;
    WeightType weight;    // 弧的权值
    int tailVex, headVex; // 弧尾(起点)、弧头(终点)序号
    AdjMultiListDirNetArc<WeightType> *tailnextarc, *headnextarc;
    AdjMultiListDirNetArc();
    AdjMultiListDirNetArc(Status t = false, int tvex, int hvex, WeightType w, AdjMultiListDirNetArc<WeightType> *tailnext = nullptr, AdjMultiListDirNetArc<WeightType> *headnext = nullptr);
};

#endif // ADJMULTILISTDIRNETARC_HPP_

template <typename WeightType>
inline AdjMultiListDirNetArc<WeightType>::AdjMultiListDirNetArc()
{
    tag = false;
    weight = 0;
    tailVex = headVex = -1;
    tailnextarc = headnextarc = nullptr;
}

template <typename WeightType>
inline AdjMultiListDirNetArc<WeightType>::AdjMultiListDirNetArc(Status t, int tvex, int hvex, WeightType w, AdjMultiListDirNetArc<WeightType> *tailnext, AdjMultiListDirNetArc<WeightType> *headnext)
{
    tag = t;
    tailVex = tvex;
    headVex = hvex;
    weight = w;
    tailnextarc = tailnext;
    headnextarc = headnext;
}
