#include "InThreadBinTree.hpp"

int main()
{
    BinaryTree<char> btch('A');
    btch.InsertLeftChild(btch.GetRoot(), 'B');
    btch.InsertRightChild(btch.GetRoot(), 'C');

    btch.InsertLeftChild(btch.GetLeftChild(btch.GetRoot()), 'D');
    btch.InsertRightChild(btch.GetLeftChild(btch.GetRoot()), 'E');

    btch.InsertLeftChild(btch.GetRightChild(btch.GetRoot()), 'F');
    btch.InsertRightChild(btch.GetRightChild(btch.GetRoot()), 'G');

    btch.PreOrderPrint();
    cout << endl;

    InThreadBinTree<char> itbtch(btch);
    itbtch.InOrderVisit(Print);
    cout << endl;

    ThreadBinNode<char> *p = itbtch.GetFirst();

    for (int i = 0; i < 2; i++)
        p = itbtch.GetNext(p);
    cout << p->data << endl;

    itbtch.InsertLeftChild(p,'H');
    itbtch.InOrderVisit(Print);
    cout << endl;
    return 0;
}