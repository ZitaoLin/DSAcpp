#if !defined(ADJMATRIXUNDIRNET_HPP_)
#define ADJMATRIXUNDIRNET_HPP_

// 无向网 邻接矩阵

#define Status bool
#define DEFAULT_MAXSIZE 10
#define UNVISITED false
#define VISITED true
#define DEFAULT_INFINITY __INT64_MAX__

#include <iostream>

template <typename ElemType, typename WeightType>
class AdjMatrixUndirNet
{
protected:
    int vexNum, vexMaxNum, arcNum; // 顶点数、允许的最大顶点数、边数
    WeightType **arcs;             // 关系矩阵
    ElemType *vertexes;            // 顶点集
    mutable Status *tags;          // 顶点标签集

public:
    AdjMatrixUndirNet(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_MAXSIZE);
    // 构造以数组es[]为顶点集、vertexNUm为顶点数、vertexMaxNum为最大顶点数、边数为0的无向图
    AdjMatrixUndirNet(int vertexMaxNum = DEFAULT_MAXSIZE);
    // 构造以vertexMaxNum为最大顶点数的空无向图
    ~AdjMatrixUndirNet();

    void Clear();
    bool IsEmpty();
    WeightType GetInfinity() const { return WeightType(DEFAULT_INFINITY); } // 返回无穷大权值

    int GetOrder(const ElemType &elem) const;    // 返回顶点的序号
    Status GetElem(int v, ElemType &elem) const; // 获取顶点的元素值
    Status SetElem(int v, const ElemType &elem); // 设置顶点的元素值为elem

    int GetVexNum() const { return vexNum; } // 返回顶点数
    int GetArcNum() const { return arcNum; } // 返回边数

    int FirstAdjVex(int v) const;         // 返回顶点v的第一个邻接点的序号
    int NextAdjVex(int v1, int v2) const; // 返回顶点v1相对于v2的邻接点

    void InsertVex(const ElemType &elem);         // 插入元素值为elem的顶点
    void InsertArc(int v1, int v2, WeightType w); // 插入顶点为v1和v2的边
    void DeleteVex(const ElemType &elem);         // 删除元素值为elem的顶点
    void DeleteArc(int v1, int v2);               // 删除顶点为v1和v2的边

    WeightType GetWeight(int v1, int v2);         // 返回从v1到v2的边的权值
    void SetWeight(int v1, int v2, WeightType w); // 设置从v1到v2的边的权值为w

    Status GetTag(int v) const;       // 返回顶点v的标签
    Status SetTag(int v, Status val); // 设置顶点v的标签为val

    void Display() const; // 显示无向图的邻接矩阵
};

#endif // ADJMATRIXUNDIRNET_HPP_

template <typename ElemType, typename WeightType>
inline AdjMatrixUndirNet<ElemType, WeightType>::AdjMatrixUndirNet(ElemType es[], int vertexNum, int vertexMaxNum)
{
    if (vertexMaxNum < 0)
        std::cerr << "最大顶点数不能是负数" << std::endl;

    if (vertexMaxNum < vertexNum)
        std::cerr << "顶点数不能大于最大顶点数" << std::endl;

    else
    {
        vexNum = vertexNum;
        vexMaxNum = vertexMaxNum;
        arcNum = 0;
        vertexes = new ElemType[vexMaxNum];
        tags = new Status[vexMaxNum];
        arcs = new WeightType *[vexMaxNum];
        for (int i = 0; i < vexMaxNum; i++)
            arcs[i] = new WeightType[vexMaxNum];
        for (int i = 0; i < vexNum; i++)
        {
            vertexes[i] = es[i];
            tags[i] = UNVISITED;
            for (int j = 0; j < vexNum; j++)
                arcs[i][j] = WeightType(DEFAULT_INFINITY); // 邻接矩阵初始化
        }
    }
}

template <typename ElemType, typename WeightType>
inline AdjMatrixUndirNet<ElemType, WeightType>::AdjMatrixUndirNet(int vertexMaxNum)
{
    if (vertexMaxNum < 0)
        std::cerr << "最大顶点数不能是负数" << std::endl;

    else
    {
        vexNum = 0;
        vexMaxNum = vertexMaxNum;
        arcNum = 0;
        vertexes = new ElemType[vexMaxNum];
        tags = new Status[vexMaxNum];
        arcs = new WeightType *[vexMaxNum];
        for (int i = 0; i < vexMaxNum; i++)
            arcs[i] = new WeightType[vexMaxNum];
    }
}

template <typename ElemType, typename WeightType>
inline AdjMatrixUndirNet<ElemType, WeightType>::~AdjMatrixUndirNet()
{
    Clear();
}

template <typename ElemType, typename WeightType>
inline void AdjMatrixUndirNet<ElemType, WeightType>::Clear()
{
    delete[] vertexes;
    delete[] tags;
    for (int i = 0; i < vexMaxNum; i++)
        delete[] arcs[i];
    delete[] arcs;
}

template <typename ElemType, typename WeightType>
inline bool AdjMatrixUndirNet<ElemType, WeightType>::IsEmpty()
{
    return vexNum == 0;
}

template <typename ElemType, typename WeightType>
inline int AdjMatrixUndirNet<ElemType, WeightType>::GetOrder(const ElemType &elem) const
{
    int pos = 0;
    while (vertexes[pos] != elem)
    {
        pos++;
    }
    return pos;
}

template <typename ElemType, typename WeightType>
inline Status AdjMatrixUndirNet<ElemType, WeightType>::GetElem(int v, ElemType &elem) const
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return false;
    }
    else
    {
        elem = vertexes[v - 1];
        return true;
    }
}

template <typename ElemType, typename WeightType>
inline Status AdjMatrixUndirNet<ElemType, WeightType>::SetElem(int v, const ElemType &elem)
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return false;
    }
    else
    {
        vertexes[v - 1] = elem;
        return true;
    }
}

template <typename ElemType, typename WeightType>
inline int AdjMatrixUndirNet<ElemType, WeightType>::FirstAdjVex(int v) const
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return -1;
    }
    for (int u = 1; u <= vexNum; u++)
    {
        if (arcs[v - 1][u - 1] != WeightType(DEFAULT_INFINITY))
            return u;
    }
    return -1;
}

template <typename ElemType, typename WeightType>
inline int AdjMatrixUndirNet<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
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
        for (int u = v2 + 1; u <= vexNum; u++)
        {
            if (arcs[v1 - 1][u - 1] != WeightType(DEFAULT_INFINITY))
                return u;
        }
        return -1;
    }
}

template <typename ElemType, typename WeightType>
inline void AdjMatrixUndirNet<ElemType, WeightType>::InsertVex(const ElemType &elem)
{
    if (vexNum == vexMaxNum)
    {
        std::cerr << "顶点数不能大于顶点最大数" << std::endl;
        return;
    }

    // 加在末尾
    vertexes[vexNum] = elem;
    tags[vexNum] = UNVISITED;
    for (int i = 0; i <= vexNum; i++)
    {
        arcs[vexNum][i] = WeightType(DEFAULT_INFINITY); // 邻接矩阵新增末尾行
        arcs[i][vexNum] = WeightType(DEFAULT_INFINITY); // 邻接矩阵新增末尾列
    }
    vexNum++;
}

template <typename ElemType, typename WeightType>
inline void AdjMatrixUndirNet<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;

    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;

    else if (arcs[v1 - 1][v2 - 1] == WeightType(DEFAULT_INFINITY))
    // 原无向图中无边(v1,v2)
    {
        arcNum++;
        arcs[v1 - 1][v2 - 1] = w;
        arcs[v2 - 1][v1 - 1] = w;
    }
}

template <typename ElemType, typename WeightType>
inline void AdjMatrixUndirNet<ElemType, WeightType>::DeleteVex(const ElemType &elem)
{
    int v = 0;
    for (v = 0; v < vexNum; v++)
        if (vertexes[v] == elem)
            break;

    if (v == vexNum)
    {
        std::cerr << "图中无该元素" << std::endl;
        return;
    }

    // 删除依附于元素值为elem的顶点的边
    for (int u = 0; u < vexNum; u++)
    {
        if (arcs[v][u] != WeightType(DEFAULT_INFINITY))
        {
            arcNum--;
            arcs[v][u] = WeightType(DEFAULT_INFINITY);
            arcs[u][v] = WeightType(DEFAULT_INFINITY);
        }
    }

    // 删除元素值为elem的顶点：
    vexNum--;
    // arcs[vexNum][0~vexNum] -> arcs[v][0~vexNum]
    // arcs[0~vexNum][vexNum] -> arcs[0~vexNum][v]
    // arcs[vexNum][0~vexNum] == arcs[0~vexNum][vexNum]
    if (v < vexNum)
    {
        vertexes[v] = vertexes[vexNum];
        tags[v] = tags[vexNum];
        for (int i = 0; i < vexNum + 1; i++)
            arcs[i][v] = arcs[v][i] = arcs[vexNum][i];
    }
}

template <typename ElemType, typename WeightType>
inline void AdjMatrixUndirNet<ElemType, WeightType>::DeleteArc(int v1, int v2)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;

    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;

    else if (arcs[v1 - 1][v2 - 1] != WeightType(DEFAULT_INFINITY))
    // 原无向图中有边(v1,v2)
    {
        arcNum--;
        arcs[v1 - 1][v2 - 1] = WeightType(DEFAULT_INFINITY);
        arcs[v2 - 1][v1 - 1] = WeightType(DEFAULT_INFINITY);
    }
}

template <typename ElemType, typename WeightType>
inline WeightType AdjMatrixUndirNet<ElemType, WeightType>::GetWeight(int v1, int v2)
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
        return WeightType(DEFAULT_INFINITY);

    else
        return arcs[v1 - 1][v2 - 1];
}

template <typename ElemType, typename WeightType>
inline void AdjMatrixUndirNet<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;
    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;
    else
    {
        if (arcs[v1 - 1][v2 - 1] == WeightType(DEFAULT_INFINITY))
        {
            std::cerr << "无向网中没有依附于v1和v2的边" << std::endl;
            return;
        }
        else
            arcs[v1 - 1][v2 - 1] = arcs[v2 - 1][v1 - 1] = w;
    }
}

template <typename ElemType, typename WeightType>
inline Status AdjMatrixUndirNet<ElemType, WeightType>::GetTag(int v) const
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
inline Status AdjMatrixUndirNet<ElemType, WeightType>::SetTag(int v, Status val)
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
inline void AdjMatrixUndirNet<ElemType, WeightType>::Display() const
{
    for (int i = 0; i < vexNum - 1; i++)
    {
        for (int j = 0; j < vexNum - 1; j++)
            std::cout << arcs[i][j] << ' ';
        std::cout << arcs[i][vexNum - 1] << std::endl;
    }
    for (int i = 0; i < vexNum - 1; i++)
        std::cout << arcs[vexNum - 1][i] << ' ';
    std::cout << arcs[vexNum - 1][vexNum - 1] << std::endl;
    std::cout << std::endl;
}
