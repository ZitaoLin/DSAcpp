template <typename ElemType>
struct ThreadBinNode
{
    ElemType data;
    ThreadBinNode<ElemType> *leftChild, *rightChild;
    int leftTag, rightTag;
    // 0 - 孩子指针  1 - 前驱/后继结点

    ThreadBinNode();
    ThreadBinNode(const ElemType &d, ThreadBinNode<ElemType> *lc = nullptr, ThreadBinNode<ElemType> *rc = nullptr, int lt = 0, int rt = 0);
};

template <typename ElemType>
inline ThreadBinNode<ElemType>::ThreadBinNode()
{
    leftChild = rightChild = nullptr;
    leftTag = rightTag = 0;
}

template <typename ElemType>
inline ThreadBinNode<ElemType>::ThreadBinNode(const ElemType &d, ThreadBinNode<ElemType> *lc, ThreadBinNode<ElemType> *rc, int lt, int rt)
    : data(d), leftChild(lc), rightChild(rc), leftTag(lt), rightTag(rt) {}