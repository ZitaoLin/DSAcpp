#if !defined(ADJLISTDIRNETWORK_HPP_)
#define ADJLISTDIRNETWORK_HPP_

// 有向网 邻接表

#include <iostream>
#include "AdjListNetWorkVex.hpp"
#define Status bool
#define UNVISITED false
#define VISITED true
#define DEFAULT_SIZE 10
#define DEFAULT_INFINITY __INT64_MAX__

template <typename ElemType, typename WeightType>
class AdjListDirNetWork
{
protected:
    int vexNum, vexMaxNum, arcNum;                     // 顶点数，最大顶点数、弧数
    AdjListNetWorkVex<ElemType, WeightType> *vexTable; // 顶点集
    mutable Status *tags;
    WeightType infinity;

public:
    AdjListDirNetWork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE, WeightType infinite = (WeightType)DEFAULT_INFINITY);
    // 构造以数组es[]为顶点数据，vertexNum为顶点数，vertexMaxNum为最大顶点数，infinite为无穷大权值，0为弧数的有向网
    AdjListDirNetWork(int vertexMaxNum = DEFAULT_SIZE, WeightType infinite = (WeightType)DEFAULT_INFINITY);
    // vertexMaxNum为最大顶点数，infinite为无穷大权值，0为弧数的空有向网
    ~AdjListDirNetWork();

    void Clear();
    bool IsEmpty();
    int GetOrder(ElemType &elem) const;                 // 返回元素值为elem的顶点的序号
    Status GetElem(int v, ElemType &elem) const;        // 返回序号为v的顶点的元素值
    Status SetElem(int v, const ElemType &elem);        // 设置序号为v的顶点的元素值为elem
    WeightType GetInfinity() const { return infinity; } // 返回无穷大权值
    int GetVexNum() const { return vexNum; }            // 返回有向网的顶点数
    int GetArcNum() const { return arcNum; }            // 返回有向网的弧数

    int FirstAdjVex(int v) const;         // 返回序号为v的顶点的第一个邻接点的序号
    int NextAdjVex(int v1, int v2) const; // 返回顶点v1相对于顶点v2的邻接点的序号

    void InsertVex(const ElemType &elem);         // 插入元素值为elem的顶点
    void InsertArc(int v1, int v2, WeightType w); // 插入从v1到v2，权值为w的弧

    void DeleteVex(const ElemType &elem); // 删除元素值为elem的顶点
    void DeleteArc(int v1, int v2);       // 删除从v1到v2的弧

    WeightType GetWeight(int v1, int v2);         // 返回从v1到v2的弧的权值
    void SetWeight(int v1, int v2, WeightType w); // 设置从v1到v2的弧的权值为w

    Status GetTag(int v) const;     // 返回顶点v的tag
    void SetTag(int v, Status tag); // 设置顶点v的tag为tag

    void Display() const; // 显示有向网的邻接表
};

#endif // ADJLISTDIRNETWORK_HPP_

template <typename ElemType, typename WeightType>
inline AdjListDirNetWork<ElemType, WeightType>::AdjListDirNetWork(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infinite)
{
    if (vertexMaxNum < 0)
        std::cerr << "最大顶点数不能为负数" << std::endl;

    if (vertexMaxNum < vertexNum)
        std::cerr << "顶点数不能大于最大顶点数" << std::endl;

    else
    {
        vexNum = vertexNum;
        vexMaxNum = vertexMaxNum;
        arcNum = 0;
        infinity = infinite;
        tags = new Status[vexMaxNum];
        vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
        for (int i = 0; i < vexNum; i++)
        {
            vexTable[i].data = es[i];
            vexTable[i].firstarc = nullptr;
            tags[i] = UNVISITED;
        }
    }
}

template <typename ElemType, typename WeightType>
inline AdjListDirNetWork<ElemType, WeightType>::AdjListDirNetWork(int vertexMaxNum, WeightType infinite)
{
    if (vertexMaxNum < 0)
        std::cerr << "最大顶点数不能为负数" << std::endl;

    else
    {
        vexNum = 0;
        vexMaxNum = vertexMaxNum;
        arcNum = 0;
        infinity = infinite;
        tags = new Status[vexMaxNum];
        vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
    }
}

template <typename ElemType, typename WeightType>
inline AdjListDirNetWork<ElemType, WeightType>::~AdjListDirNetWork()
{
    Clear();
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::Clear()
{
    delete[] vexTable;
    delete[] tags;
}

template <typename ElemType, typename WeightType>
inline bool AdjListDirNetWork<ElemType, WeightType>::IsEmpty()
{
    return vexNum == 0;
}

template <typename ElemType, typename WeightType>
inline int AdjListDirNetWork<ElemType, WeightType>::GetOrder(ElemType &elem) const
{
    int pos = 0;
    while (vexTable[pos].data != elem)
    {
        pos++;
    }
    return pos;
}

template <typename ElemType, typename WeightType>
inline Status AdjListDirNetWork<ElemType, WeightType>::GetElem(int v, ElemType &elem) const
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return false;
    }
    else
    {
        elem = vexTable[v - 1].data;
        return true;
    }
}

template <typename ElemType, typename WeightType>
inline Status AdjListDirNetWork<ElemType, WeightType>::SetElem(int v, const ElemType &elem)
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return false;
    }
    else
    {
        vexTable[v - 1].data = elem;
        return true;
    }
}

template <typename ElemType, typename WeightType>
inline int AdjListDirNetWork<ElemType, WeightType>::FirstAdjVex(int v) const
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return -1;
    }
    if (vexTable[v - 1].firstarc == nullptr)
    {
        std::cerr << "v不存在邻接点" << std::endl;
        return -1;
    }
    else
        return vexTable[v - 1].firstarc->adjVex;
}

template <typename ElemType, typename WeightType>
inline int AdjListDirNetWork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
{
    int cnt = 0;
    if (v1 < 0 || v1 > vexNum)
    {
        std::cerr << "v1不在范围内" << std::endl;
        cnt++;
    }

    if (v2 < 0 || v2 > vexNum)
    {
        std::cerr << "v2不在范围内" << std::endl;
        cnt++;
    }

    if (v1 == v2)
    {
        std::cerr << "v1不能等于v2" << std::endl;
        cnt++;
    }

    if (cnt > 0)
        return -1;

    else
    {
        AdjListNetWorkArc<WeightType> *p = vexTable[v1 - 1].firstarc;
        WeightType weight = p->weight;
        while (p->adjVex != v2 - 1)
        {
            p = p->nextarc;
            weight = p->weight;
        }
        p = p->nextarc;
        if (p == nullptr)
        {
            std::cerr << "不存在相对于v2的下一个邻接点" << std::endl;
            return -1;
        }
        else
            return p->adjVex;
    }
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::InsertVex(const ElemType &elem)
{
    if (vexNum == vexMaxNum)
    {
        std::cerr << "图的顶点数不能超过最大顶点数" << std::endl;
        return;
    }
    // 尾插
    vexTable[vexNum].data = elem;
    vexTable[vexNum].firstarc = nullptr;
    tag[vexNum] = UNVISITED;
    vexNum++;
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;
    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;
    if (w == infinity)
        std::cerr << "w不能为无穷" << std::endl;

    // 头插 O(1)
    AdjListNetWorkArc<WeightType> *p = vexTable[v1 - 1].firstarc;
    vexTable[v1 - 1].firstarc = new AdjListNetWorkArc(v2, w, p);
    arcNum++;
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::DeleteVex(const ElemType &elem)
{
    int v;
    AdjListNetWorkArc<WeightType> *p, *q;

    // 遍历寻找该顶点的序号
    for (v = 0; v < vexNum; v++)
        if (vexTable[v].data = elem)
            break;
    if (v == vexNum)
    {
        std::cerr << "图中无该元素" << std::endl;
        return;
    }

    // 删除?->v的弧
    for (int u = 1; u <= vexNum; u++)
        if (u != v + 1)
            DeleteArc(u, v + 1);

    // 删除v->?的弧
    p = vexTable[v].firstarc;
    while (p != nullptr)
    {
        vexTable[v].firstarc = p->nextarc;
        delete p;
        p = vexTable[v].firstarc;
        arcNum--;
    }

    // 用末尾顶点填充
    vexNum--;
    vexTable[v].data = vexTable[vexNum].data;
    vexTable[v].firstarc = vexTable[vexNum].firstarc;
    vexTable[vexNum].firstarc = nullptr;
    tags[v] = tags[vexNum];

    // 将除v以外顶点的弧链表中各个adjVex==vexNum结点的adjVex修改为v
    for (int u = 0; u < vexNum; u++)
        if (u != v)
        {
            p = vexTable[u].firstarc;
            while (p != nullptr)
            {
                if (p->adjVex == vexNum)
                    p->adjVex = v;
                p = p->nextarc
            }
        }
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::DeleteArc(int v1, int v2)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;
    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;

    AdjListNetWorkArc<WeightType> *p, *q;
    p = vexTable[v1 - 1].firstarc;
    while (p->adjVex != v2 - 1)
    {
        q = p;
        p = p->nextarc;
    }

    if (p == nullptr)
    {
        std::cerr << "有向网中没有从顶点v1到v2的弧" << std::endl;
        return;
    }
    else
    {
        if (vexTable[v1 - 1].firstarc == p)
            // p为第一个弧结点时，q无效(弧链表无头结点)
            vexTable[v1 - 1].firstarc = p->nextarc;
        else
            q->nextarc = p->nextarc;
        delete p;
        arcNum--;
    }
}

template <typename ElemType, typename WeightType>
inline WeightType AdjListDirNetWork<ElemType, WeightType>::GetWeight(int v1, int v2)
{
    int cnt = 0;
    if (v1 < 0 || v1 > vexNum)
    {
        std::cerr << "v1不在范围内" << std::endl;
        cnt++;
    }

    if (v2 < 0 || v2 > vexNum)
    {
        std::cerr << "v2不在范围内" << std::endl;
        cnt++;
    }

    if (v1 == v2)
    {
        std::cerr << "v1不能等于v2" << std::endl;
        cnt++;
    }

    if (cnt > 0)
        return infinity;

    else
    {
        AdjListNetWorkArc<WeightType> *p = vexTable[v1 - 1].firstarc;
        WeightType weight = p->weight;
        while (p->adjVex != v2 - 1)
        {
            p = p->nextarc;
            weight = p->weight;
        }
        if (p == nullptr)
            return infinity;
        else
            return p->weight;
    }
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;
    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;

    else
    {
        AdjListNetWorkArc<WeightType> *p = vexTable[v1 - 1].firstarc;
        WeightType weight = p->weight;
        while (p->adjVex != v2 - 1)
        {
            p = p->nextarc;
            weight = p->weight;
        }
        if (p == nullptr)
        {
            std::cerr << "有向网中没有从顶点v1到v2的弧" << std::endl;
            return;
        }
        else
            p->weight = w;
    }
}

template <typename ElemType, typename WeightType>
inline Status AdjListDirNetWork<ElemType, WeightType>::GetTag(int v) const
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return false;
    }
    else
        return tags[v - 1];
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::SetTag(int v, Status tag)
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return false;
    }
    else
    {
        tags[v - 1] = val;
        return true;
    }
}

template <typename ElemType, typename WeightType>
inline void AdjListDirNetWork<ElemType, WeightType>::Display() const
{
    for (int v = 0; v < vexNum; v++)
    {
        std::cout << "弧尾(起点)=" << vexTable[v].data;
        AdjListNetWorkArc<WeightType> *p = vexTable[v].firstarc;
        while (p != nullptr)
        {
            std::cout << " -> "
                      << "(弧头(终点)=" << p->adjVex << ", 权值=" << p->weight << ")";
            p = p->nextarc;
        }
        std::cout << std::endl;
    }
}
