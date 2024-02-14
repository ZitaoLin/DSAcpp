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

    cout << "前序遍历：";
    btch0.PreOrderPrint();
    cout << endl;

    cout << "中序遍历：";
    btch0.InOrderPrint();
    cout << endl;

    cout << "后序遍历：";
    btch0.PostOrderPrint();
    cout << endl;

    cout << "层序遍历：";
    btch0.LevelOrderPrint();
    cout << endl;

    btch0.DisplayShape();

    cout << "树的高度: " << btch.GetHeight() << endl;
    cout << "树的结点数量：: " << btch.GetNodeNums() << endl;
    cout << endl;

    return 0;
}