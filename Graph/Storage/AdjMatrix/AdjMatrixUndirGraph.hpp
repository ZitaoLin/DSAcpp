#if !defined(ADJMATRIXUNDIRGRAPH_HPP_)
#define ADJMATRIXUNDIRGRAPH_HPP_

// 无向图 邻接矩阵

#define Status bool
#define DEFAULT_MAXSIZE 10
#define UNVISITED false
#define VISITED true

#include <iostream>

template <typename ElemType>
class AdjMatrixUndirGraph
{
protected:
    int vexNum, vexMaxNum, arcNum; // 顶点数、允许的最大顶点数、边数
    int **arcs;                    // 关系矩阵
    ElemType *vertexes;            // 顶点集
    Status *tags;          // 顶点标签集

public:
    AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_MAXSIZE);
    // 构造以数组es[]为顶点集、vertexNUm为顶点数、vertexMaxNum为最大顶点数、边数为0的无向图
    AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_MAXSIZE);
    // 构造以vertexMaxNum为最大顶点数的空无向图
    ~AdjMatrixUndirGraph();

    void Clear();
    bool IsEmpty();

    int GetOrder(const ElemType &elem) const;    // 返回顶点的序号
    Status GetElem(int v, ElemType &elem) const; // 获取顶点的元素值
    Status SetElem(int v, const ElemType &elem); // 设置顶点的元素值为elem

    int GetVexNum() const { return vexNum; } // 返回顶点数
    int GetArcNum() const { return arcNum; } // 返回边数

    int FirstAdjVex(int v) const;         // 返回顶点v的第一个邻接点的序号
    int NextAdjVex(int v1, int v2) const; // 返回顶点v1相对于v2的邻接点

    void InsertVex(const ElemType &elem); // 插入元素值为elem的顶点
    void InsertArc(int v1, int v2);       // 插入顶点为v1和v2的边
    void DeleteVex(const ElemType &elem); // 删除元素值为elem的顶点
    void DeleteArc(int v1, int v2);       // 删除顶点为v1和v2的边

    Status GetTag(int v) const;       // 返回顶点v的标签
    Status SetTag(int v, Status val); // 设置顶点v的标签为val

    void Display() const; // 显示无向图的邻接矩阵
};

#endif // ADJMATRIXUNDIRGRAPH_HPP_

template <typename ElemType>
inline AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum)
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
        arcs = new int *[vexMaxNum];
        for (int i = 0; i < vexMaxNum; i++)
            arcs[i] = new int[vexMaxNum];
        for (int i = 0; i < vexNum; i++)
        {
            vertexes[i] = es[i];
            tags[i] = UNVISITED;
            for (int j = 0; j < vexNum; j++)
                arcs[i][j] = 0; // 邻接矩阵初始化
        }
    }
}

template <typename ElemType>
inline AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(int vertexMaxNum)
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
        arcs = new int *[vexMaxNum];
        for (int i = 0; i < vexMaxNum; i++)
            arcs[i] = new int[vexMaxNum];
    }
}

template <typename ElemType>
inline AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
{
    Clear();
}

template <typename ElemType>
inline void AdjMatrixUndirGraph<ElemType>::Clear()
{
    delete[] vertexes;
    delete[] tags;
    for (int i = 0; i < vexMaxNum; i++)
        delete[] arcs[i];
    delete[] arcs;
}

template <typename ElemType>
inline bool AdjMatrixUndirGraph<ElemType>::IsEmpty()
{
    return vexNum == 0;
}

template <typename ElemType>
inline int AdjMatrixUndirGraph<ElemType>::GetOrder(const ElemType &elem) const
{
    int pos = 0;
    while (vertexes[pos] != elem)
    {
        pos++;
    }
    return pos;
}

template <typename ElemType>
inline Status AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType &elem) const
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

template <typename ElemType>
inline Status AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType &elem)
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

template <typename ElemType>
inline int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return -1;
    }
    for (int u = 1; u <= vexNum; u++)
    {
        if (arcs[v - 1][u - 1] != 0)
            return u;
    }
    return -1;
}

template <typename ElemType>
inline int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
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
            if (arcs[v1 - 1][u - 1] != 0)
                return u;
        }
        return -1;
    }
}

template <typename ElemType>
inline void AdjMatrixUndirGraph<ElemType>::InsertVex(const ElemType &elem)
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
        arcs[vexNum][i] = 0; // 邻接矩阵新增末尾行
        arcs[i][vexNum] = 0; // 邻接矩阵新增末尾列
    }
    vexNum++;
}

template <typename ElemType>
inline void AdjMatrixUndirGraph<ElemType>::InsertArc(int v1, int v2)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;

    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;

    else if (arcs[v1 - 1][v2 - 1] == 0)
    // 原无向图中无边(v1,v2)
    {
        arcNum++;
        arcs[v1 - 1][v2 - 1] = 1;
        arcs[v2 - 1][v1 - 1] = 1;
    }
}

template <typename ElemType>
inline void AdjMatrixUndirGraph<ElemType>::DeleteVex(const ElemType &elem)
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
        if (arcs[v][u] == 1)
        {
            arcNum--;
            arcs[v][u] = 0;
            arcs[u][v] = 0;
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

template <typename ElemType>
inline void AdjMatrixUndirGraph<ElemType>::DeleteArc(int v1, int v2)
{
    if (v1 < 0 || v1 > vexNum)
        std::cerr << "v1不在范围内" << std::endl;
    if (v2 < 0 || v2 > vexNum)
        std::cerr << "v2不在范围内" << std::endl;

    if (v1 == v2)
        std::cerr << "v1不能等于v2" << std::endl;

    else if (arcs[v1 - 1][v2 - 1] == 1)
    // 原无向图中有边(v1,v2)
    {
        arcNum--;
        arcs[v1 - 1][v2 - 1] = 0;
        arcs[v2 - 1][v1 - 1] = 0;
    }
}

template <typename ElemType>
inline Status AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
{
    if (v < 0 || v > vexNum)
    {
        std::cerr << "v不在范围内" << std::endl;
        return false;
    }
    else
        return tags[v - 1];
}

template <typename ElemType>
inline Status AdjMatrixUndirGraph<ElemType>::SetTag(int v, Status val)
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

template <typename ElemType>
inline void AdjMatrixUndirGraph<ElemType>::Display() const
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
