#if !defined(ADJLISTNETWORKARC_HPP_)
#define ADJLISTNETWORKARC_HPP_

// 有向网 邻接表 弧结点类

template <typename WeightType>
struct AdjListNetWorkArc
{
    int adjVex;                             // 弧头(有向边的终点)顶点序号
    WeightType weight;                      // 弧的权值
    AdjListNetWorkArc<WeightType> *nextarc; // 指向下一个弧结点的指针

    AdjListNetWorkArc();
    AdjListNetWorkArc(int v, WeightType w, AdjListNetWorkArc<WeightType> *next = nullptr);
};

#endif // ADJLISTNETWORKARC_HPP_

template <typename WeightType>
inline AdjListNetWorkArc<WeightType>::AdjListNetWorkArc()
{
    adjVex = -1;
}

template <typename WeightType>
inline AdjListNetWorkArc<WeightType>::AdjListNetWorkArc(int v, WeightType w, AdjListNetWorkArc<WeightType> *next)
{
    adjVex = v;
    weight = w;
    nextarc = next;
}
