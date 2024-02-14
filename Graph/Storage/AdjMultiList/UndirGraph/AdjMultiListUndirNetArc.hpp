#if !defined(ADJMULTILISTUNDIRNETARC_HPP_)
#define ADJMULTILISTUNDIRNETARC_HPP_

// 无向网 邻接多重表 边结点类

#define Status bool
template <typename WeightType>
struct AdjMultiListUndirNetArc
{
    Status tag;
    WeightType weight;    // 边的权值
    int adjVex1, adjVex2; // 边端顶点序号
    AdjMultiListUndirNetArc<WeightType> *nextarc1, *nextarc2;
    AdjMultiListUndirNetArc();
    AdjMultiListUndirNetArc(Status t = false, int vex1, int vex2, WeightType w, AdjMultiListUndirNetArc<WeightType> *next1 = nullptr, AdjMultiListUndirNetArc<WeightType> *next2 = nullptr);
};

#endif // ADJMULTILISTUNDIRNETARC_HPP_

template <typename WeightType>
inline AdjMultiListUndirNetArc<WeightType>::AdjMultiListUndirNetArc()
{

    tag = false;
    weight = 0;
    adjVex1 = adjVex2 = -1;
    nextarc1 = nextarc2 = nullptr;
}

template <typename WeightType>
inline AdjMultiListUndirNetArc<WeightType>::AdjMultiListUndirNetArc(Status t, int vex1, int vex2, WeightType w, AdjMultiListUndirNetArc<WeightType> *next1, AdjMultiListUndirNetArc<WeightType> *next2)
{
    tag = t;
    adjVex1 = vex1;
    adjVex2 = vex2;
    weight = w;
    nextarc1 = next1;
    nextarc2 = next2;
}
