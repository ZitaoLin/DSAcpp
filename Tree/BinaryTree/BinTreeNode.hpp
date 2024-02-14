template <typename ElemType>

struct BinTreeNode
{
    ElemType data;
    BinTreeNode<ElemType> *leftChild;
    BinTreeNode<ElemType> *rightChild;

    BinTreeNode();
    BinTreeNode(const ElemType &d, BinTreeNode<ElemType> *lchild = nullptr, BinTreeNode<ElemType> *rchild = nullptr);
};

template <typename ElemType>
inline BinTreeNode<ElemType>::BinTreeNode()
{
    leftChild = rightChild = nullptr;
}

template <typename ElemType>
inline BinTreeNode<ElemType>::BinTreeNode(const ElemType &d, BinTreeNode<ElemType> *lchild, BinTreeNode<ElemType> *rchild)
{
    data = d;
    leftChild = lchild;
    rightChild = rchild;
}
