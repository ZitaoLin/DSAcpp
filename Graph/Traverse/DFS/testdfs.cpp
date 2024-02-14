#include "DFS.hpp"
#include <iostream>

template <typename ElemType>
void print(const ElemType &ch)
{
    std::cout << ch << ' ';
}

int main()
{
    char vex[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    AdjMatrixUndirGraph<char> udgraph(vex, 9);
    udgraph.Display();

    udgraph.InsertArc(1, 2);
    udgraph.InsertArc(1, 5);
    udgraph.InsertArc(1, 4);

    udgraph.InsertArc(2, 3);
    udgraph.InsertArc(2, 5);

    udgraph.InsertArc(3, 5);

    udgraph.InsertArc(4, 7);

    udgraph.InsertArc(5, 7);
    udgraph.InsertArc(5, 6);

    udgraph.InsertArc(6, 9);
    udgraph.InsertArc(7, 8);

    udgraph.Display();

    DFS_Traverse<char>(udgraph, print<char>);
    return 0;
}

// A1 B2 C3 D4 E5 F6 G7 H8 I9