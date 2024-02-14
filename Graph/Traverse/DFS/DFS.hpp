#if !defined(DFS_HPP_)
#define DFS_HPP_

//! 深度优先遍历 Depth First Search
//! 每次只在当前结点的邻接点中找UNVISITED的第一个邻接点，找不到就返回上一层，从上一层的第二个邻接点同样找起 ......

#include "Graph/Storage/AdjMatrix/AdjMatrixUndirGraph.hpp"

// 从序号v开始以Visit方式深度优先遍历图g(适用于连通图)
template <typename ElemType>
void DFS(AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(const ElemType &elem))
{
    ElemType e;
    g.SetTag(v, VISITED);
    g.GetElem(v, e);
    Visit(e);
    for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
    {
        if (g.GetTag(w) == UNVISITED)
            DFS(g, w, Visit);
    }
}

// 对于非连通图
template <typename ElemType>
void DFS_Traverse(AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(const ElemType &elem))
{
    int v;
    for (v = 1; v <= g.GetVexNum(); v++) //! O(n)
        g.SetTag(v, UNVISITED);
    for (v = 1; v <= g.GetVexNum(); v++) //! O(n)
        if (g.GetTag(v) == UNVISITED)
            DFS(g, v, Visit); //! 邻接矩阵：O(n^2)  邻接表：O(n+e)
}

#endif // DFS_HPP_
