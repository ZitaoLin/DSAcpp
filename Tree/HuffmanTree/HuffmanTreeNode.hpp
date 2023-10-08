// 哈夫曼树结点类
// 采用双亲-孩子表示法

template <typename WeightType>
struct HuffmanTreeNode
{
    WeightType weight;                 // 权重数据域
    int parent, leftChild, rightChild; // 双亲-孩子指针域

    HuffmanTreeNode();
    HuffmanTreeNode(WeightType w, int p = -1, int lc = -1, int rc = -1)
        : weight(w), parent(p), leftChild(lc), rightChild(rc) {}
};

template <typename WeightType>
inline HuffmanTreeNode<WeightType>::HuffmanTreeNode()
{
    parent = leftChild = rightChild = -1;
}
