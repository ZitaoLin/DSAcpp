#if !defined(MINISPANTREEPRIM_HPP_)
#define MINISPANTREEPRIM_HPP_

#include "Graph/Storage/AdjMatrix/AdjMatrixUndirNet.hpp"
#include <iostream>

template <typename ElemType, typename WeightType>
struct CloseArcType
{
    WeightType lowweight;
    int nearvertex;
};

template <typename ElemType, typename WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNet<ElemType, WeightType> &g, int u0)
{
    WeightType min;
    ElemType v1, v2;
    int vexnum = g.GetVexNum();
    CloseArcType<ElemType, WeightType> *closearc;
    if (u0 < 0 || u0 > vexnum)
    {
        std::cerr << "顶点u0不存在" << std::endl;
        return;
    }

    int u, v, k;

    // 初始化辅助数组closearc    初始化MST顶点集U={u0}
    closearc = new CloseArcType<ElemType, WeightType>[vexnum];
    for (v = 1; v <= vexnum; v++)
    {
        closearc[v].lowweight = g.GetWeight(u0, v);
        closearc[v].nearvertex = u0;
    }
    closearc[u0 - 1].lowweight = 0;
    closearc[u0 - 1].nearvertex = 0;

    // 选择除顶点u0以外的顶点
    for (k = 2; k <= vexnum; k++)
    {
        // for循环遍历选择依附于 顶点集V-U中一点 与 MST顶点集U中一点 且权值最小的边(closearc[v].nearvertex,v)
        min = g.GetInfinity();
        v = u0;
        for (u = 1; u <= vexnum; u++)
        {
            if (closearc[u - 1].lowweight != 0 && closearc[u - 1].lowweight < min)
            {
                v = u;
                min = closearc[u - 1].lowweight;
            }
        }

        if (v != u0)
        {
            g.GetElem(closearc[v].nearvertex, v1);
            g.GetElem(v, v2);
            std::cout << "边：(" << v1 << "," << v2 << ") 权：" << min << std::endl;
            close[v].lowweight = 0; // 将顶点v并入MST顶点集U
            for (u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
            {
                if (closearc[u].lowweight != 0 && (g.GetWeight(v, u) < closearc[u].lowweight))
                // 当依附于 MST顶点集U的新顶点v 与 其各个邻接点u 的边的权值 小于 原先依附于
                {
                    closearc[u].lowweight = g.GetWeight(v, u);
                    closearc[u].nearvertex = v;
                }
            }
        }
    }
    delete[] closearc;
}

#endif // MINISPANTREEPRIM_HPP_
