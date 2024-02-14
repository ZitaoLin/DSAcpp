#if !defined(KRUSKALEDGE_HPP_)
#define KRUSKALEDGE_HPP_

template <typename ElemType, typename WeightType>
class KruskalEdge
{
private:
    ElemType vertex1, vertex2;
    WeightType weight;

public:
    KruskalEdge() {}
    KruskalEdge(ElemType vex1, ElemType vex2, WeightType w);
    KruskalEdge<ElemType, WeightType> &operator=(const KruskalEdge<ElemType, WeightType> &Ed);
    bool operator<=(const KruskalEdge<ElemType, WeightType> &Ed);
    bool operator>(const KruskalEdge<ElemType, WeightType> &Ed);
};

#endif // KRUSKALEDGE_HPP_

template <typename ElemType, typename WeightType>
inline KruskalEdge<ElemType, WeightType>::KruskalEdge(ElemType vex1, ElemType vex2, WeightType w)
{
    vertex1 = vex1;
    vertex2 = vex2;
    weight = w;
}

template <typename ElemType, typename WeightType>
inline KruskalEdge<ElemType, WeightType> &KruskalEdge<ElemType, WeightType>::operator=(const KruskalEdge<ElemType, WeightType> &Ed)
{
    if (&Ed != this)
    {
        this->vertex1 = Ed.vertex1;
        this->vertex2 = Ed.vertex2;
        this->weight = Ed.weight;
    }
    return *this;
}

template <typename ElemType, typename WeightType>
inline bool KruskalEdge<ElemType, WeightType>::operator<=(const KruskalEdge<ElemType, WeightType> &Ed)
{
    return this->weight <= Ed.weight;
}

template <typename ElemType, typename WeightType>
inline bool KruskalEdge<ElemType, WeightType>::operator>(const KruskalEdge<ElemType, WeightType> &Ed)
{
    return this->weight > Ed.weight;
}
