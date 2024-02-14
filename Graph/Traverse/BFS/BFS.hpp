#if !defined(BFS_HPP_)
#define BFS_HPP_

//! 广度优先遍历 Breath First Search
//! 每次都按排列顺序找当前结点的所有邻接点，逐层深入

#include "Graph/Storage/AdjMatrix/AdjMatrixUndirGraph.hpp"
#include <queue>

// 从序号v开始以Visit方式广度优先遍历图g(适用于连通图)
template <typename ElemType>
void BFS(AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(const ElemType &elem))
{
    std::queue<int> q;
    int u, w;
    ElemType e;
    g.SetTag(v, VISITED);
    g.GetElem(v, e);
    Visit(e);
    q.push(v);
    while (!q.empty())
    {
        u=q.front();
        q.pop();
        for (w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w))
        //! 邻接矩阵：O(n)   邻接表：O(e)   顶点数n  边数e
        {
            if (g.GetTag(w) == UNVISITED)
            {
                g.SetTag(w, VISITED);
                g.GetElem(w, e);
                Visit(e);
                q.push(w);
            }
        }
    }
}

// 对于非连通图
template <typename ElemType>
void BFS_Traverse(AdjMatrixUndirGraph<ElemType> &g,void (*Visit)(const ElemType &elem))
{
    int v;
    for (v = 1; v <= g.GetVexNum(); v++) //! O(n)
        g.SetTag(v, UNVISITED);
    for (v = 1; v <= g.GetVexNum(); v++) //! O(n)
        if (g.GetTag(v) == UNVISITED)
            BFS(g, v, Visit); //! 邻接矩阵：O(n^2)  邻接表：O(n+e)
}

//! 连通图 -> 广度优先生成树(极小连通子图)  非连通图 -> 广度优先生成森林

//! 用邻接矩阵存储的图的广度优先生成树 唯一确定     邻接矩阵各个顶点的邻接点的遍历序列 唯一确定
//! 用邻接表存储的图的广度优先生成树 不唯一确定     邻接表各个顶点的邻接点的遍历序列 不唯一确定

//! 邻接矩阵存储的图 O(n^2)
//! 邻接表存储的图  O(n+e)


#endif // BFS_HPP_
