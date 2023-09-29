#include "BinaryTree.hpp"

int main()
{
    BinaryTree<char> btch('A');
    btch.InsertLeftChild(btch.GetRoot(), 'B');
    btch.InsertRightChild(btch.GetRoot(), 'C');

    btch.InsertLeftChild(btch.GetLeftChild(btch.GetRoot()), 'D');
    btch.InsertRightChild(btch.GetLeftChild(btch.GetRoot()), 'E');

    btch.InsertLeftChild(btch.GetRightChild(btch.GetRoot()), 'F');
    btch.InsertRightChild(btch.GetRightChild(btch.GetRoot()), 'G');

    BinaryTree<char> btch0;
    btch0 = btch;
    btch0.PreOrderPrint();
    
    cout << endl;

    btch.PreOrderPrint();
    cout << endl;

    btch.InOrderPrint();
    cout << endl;

    btch.PostOrderPrint();
    cout << endl;

    btch.LevelOrderPrint();
    cout << endl;

    cout << "Height of Tree: " << btch.GetHeight() << endl;
    cout << "Nums of nodes in tree: " << btch.GetNodeNums() << endl;
    cout << endl;

    return 0;
}