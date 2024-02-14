#include "ThreadBinNode.hpp"
#include "DS/Tree/BinaryTree/BinaryTree.hpp"

template <typename ElemType>
class InThreadBinTree
{
protected:
    ThreadBinNode<ElemType> *root;
    void InThreadHelp(ThreadBinNode<ElemType> *p, ThreadBinNode<ElemType> *&pre);
    // 中序线索化以p为根结点的二叉树，pre为根结点的前驱结点指针

    void TransformHelp(ThreadBinNode<ElemType> *tnode, BinTreeNode<ElemType> *node);
    // 将以r为根结点的二叉树转换成新的未线索化的线索二叉树

    void DestroyHelp(ThreadBinNode<ElemType> *&r);
    // 销毁以r为根结点的二叉树

public:
    InThreadBinTree(const BinaryTree<ElemType> &bt);
    // 由普通二叉树构造中序线索二叉树
    virtual ~InThreadBinTree();
    ThreadBinNode<ElemType> *GetRoot() const { return root; }

    void InThread();                           // 中序线索化二叉树
    ThreadBinNode<ElemType> *GetFirst() const; // 获取二叉树中序序列第一个结点
    ThreadBinNode<ElemType> *GetLast() const;  // 获取二叉树中序序列最后一个结点
    ThreadBinNode<ElemType> *GetPre(ThreadBinNode<ElemType> *p) const;
    ThreadBinNode<ElemType> *GetNext(ThreadBinNode<ElemType> *p) const; // 获取二叉树中结点p在中序序列中的后继结点

    void InsertLeftChild(ThreadBinNode<ElemType> *p, const ElemType &elem);  // 插入左孩子
    void InsertRightChild(ThreadBinNode<ElemType> *p, const ElemType &elem); // 插入右孩子

    void DeleteLeftChild(ThreadBinNode<ElemType> *p);  // 删除左子树
    void DeleteRightChild(ThreadBinNode<ElemType> *p); // 删除右子树

    void InOrderVisit(void (*Visit)(const ElemType &elem)) const;
};

template <typename ElemType>
inline void InThreadBinTree<ElemType>::InThreadHelp(ThreadBinNode<ElemType> *p, ThreadBinNode<ElemType> *&pre)
{
    if (p != nullptr)
    {
        InThreadHelp(p->leftChild, pre);

        if (p->leftChild == nullptr) // p无左孩子，则孩子为前驱指针
        {
            p->leftChild = pre;
            p->leftTag = 1;
        }
        else
            p->leftTag = 0; // p有左孩子，则指针为孩子指针

        if (pre != nullptr && pre->rightChild == nullptr) // pre（p的中序前驱结点）无右孩子
        {
            pre->rightChild = p; // 让p的中序前驱结点的右指针指向p
            pre->rightTag = 1;
        }
        else if (pre != nullptr)
            pre->rightTag = 0;

        pre = p; // 在p变更前使pre指向现有的p

        InThreadHelp(p->rightChild, pre);
    }
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::TransformHelp(ThreadBinNode<ElemType> *tnode, BinTreeNode<ElemType> *node)
{
    if (node != nullptr)
    {
        if (node->leftChild)
            tnode->leftChild = new ThreadBinNode<ElemType>(node->leftChild->data);

        if (node->rightChild)
            tnode->rightChild = new ThreadBinNode<ElemType>(node->rightChild->data);

        TransformHelp(tnode->leftChild, node->leftChild);
        TransformHelp(tnode->rightChild, node->rightChild);
    }
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::DestroyHelp(ThreadBinNode<ElemType> *&r)
{
    ThreadBinNode<ElemType> *p = r;
    for (p = GetFirst(); p != nullptr; p = GetNext(p))
    {
        delete p;
        // p = nullptr;
    }
}

template <typename ElemType>
inline InThreadBinTree<ElemType>::InThreadBinTree(const BinaryTree<ElemType> &bt)
{
    if (!bt.IsEmpty())
    {
        ThreadBinNode<ElemType> *pre = nullptr;
        this->root = new ThreadBinNode<ElemType>(bt.GetRoot()->data);
        TransformHelp(this->root, bt.GetRoot());
        InThreadHelp(this->root, pre);
        pre->rightTag = 1;
    }
}

template <typename ElemType>
inline InThreadBinTree<ElemType>::~InThreadBinTree()
{
    DestroyHelp(root);
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::InThread()
{
    ThreadBinNode<ElemType> *pre = nullptr;

    InThreadHelp(root, pre);
    pre->rightTag = 1;
}

template <typename ElemType>
inline ThreadBinNode<ElemType> *InThreadBinTree<ElemType>::GetFirst() const
{
    if (root == nullptr)
        return nullptr;
    else
    {
        ThreadBinNode<ElemType> *p = root;
        while (p->leftTag == 0)
            p = p->leftChild;
        // 中序序列的第一个结点是二叉树最左结点，只需一直向左遍历即可
        return p;
    }
}

template <typename ElemType>
inline ThreadBinNode<ElemType> *InThreadBinTree<ElemType>::GetLast() const
{
    if (root == nullptr)
        return nullptr;
    else
    {
        ThreadBinNode<ElemType> *p = root;
        while (p->rightTag == 0)
            p = p->rightTag;
        // 中序序列的最后一个结点是二叉树最右结点，只需一直向右遍历即可
        return p;
    }
}

template <typename ElemType>
inline ThreadBinNode<ElemType> *InThreadBinTree<ElemType>::GetPre(ThreadBinNode<ElemType> *p) const
{
    // 核心：一个结点的前驱结点是这个结点的左子树的最右结点
    if (p->leftTag == 1)
        p = p->leftChild;

    else
    {
        p = p->leftChild;
        while (p->rightTag == 0)
            p = p->rightChild;
    }

    return p;
}

template <typename ElemType>
inline ThreadBinNode<ElemType> *InThreadBinTree<ElemType>::GetNext(ThreadBinNode<ElemType> *p) const
{
    // 核心：一个结点的后继结点是这个结点的右子树的最左结点（按中序 左根右的递归遍历顺序 可知）
    if (p->rightTag == 1)
        p = p->rightChild; // p的右指针为线索，则返回其右指针指向结点 为其 后继结点

    else
    // 若p的右指针不是孩子指针，则p的中序后继结点为其右子树的最左结点
    {
        p = p->rightChild;
        while (p->leftTag == 0)
            p = p->leftChild;
    }

    return p;
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::InsertLeftChild(ThreadBinNode<ElemType> *p, const ElemType &elem)
{
    if (p == nullptr)
        return;
    else
    {
        ThreadBinNode<ElemType> *x, *q;
        x = new ThreadBinNode<ElemType>(elem, p->leftChild, p, p->leftTag, 1);
        // 新结点的右指针为线索指针，指向其后继结点，即结点p
        // 左指针情况（孩子/线索）及指向结点与p相同
        if (p->leftTag = 0)
        // 如果p的右指针为孩子指针，则沿p的右孩子的左子树搜到底，即原先p的后继结点
        {
            q = p->leftChild;
            while (q->rightTag == 0)
                q = q->rightChild; // 循环结束，q为p的前驱指针
            q->rightChild = x;     // 使其后继为x
        }
        p->leftChild = x;
        p->leftTag = 0; // p此时有左边孩子x
        return;
    }
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::InsertRightChild(ThreadBinNode<ElemType> *p, const ElemType &elem)
{
    if (p == nullptr)
        return;
    else
    {
        ThreadBinNode<ElemType> *x, *q;
        x = new ThreadBinNode<ElemType>(elem, p, p->rightChild, 1, p->rightTag);
        // 新结点的左指针为线索指针，指向其前驱结点，即结点p
        // 右指针情况（孩子/线索）及指向结点与p相同
        if (p->rightTag = 0)
        // 如果p的右指针为孩子指针，则沿p的右孩子的左子树搜到底，即原先p的后继结点
        {
            q = p->rightChild;
            while (q->leftTag == 0)
                q = q->leftChild; // 循环结束，q为p的后继指针
            q->leftChild = x;     // 使其前驱为x
        }
        p->rightChild = x;
        p->rightTag = 0; // p此时有右孩子x
        return;
    }
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::DeleteLeftChild(ThreadBinNode<ElemType> *p)
{
    ThreadBinNode<ElemType> *x, *q;
    if (p != nullptr || p->leftTag == 1)
        return;
    else
    {
        q = p->leftChild;
        while (q->leftTag == 0)
            q = q->leftChild; // 推出循环时，q为p的父结点的中序后继结点
        q = q->leftChild;     // 此时，q为p的中序前驱结点
        DestroyHelp(p->leftChild);
        p->leftChild = q;
        p->leftTag = 1;
        return;
    }
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::DeleteRightChild(ThreadBinNode<ElemType> *p)
{
    ThreadBinNode<ElemType> *x, *q;
    if (p != nullptr || p->rightTag == 1)
        return;
    else
    {
        q = p->rightChild;
        while (q->rightTag == 0)
            q = q->rightChild; // 推出循环时，q为p右子树的最右结点
        q = q->rightChild;     // 此时，q为p的删除右子树后的中序后继结点
        DestroyHelp(p->rightChild);
        p->rightChild = q;
        p->rightTag = 1;
        return;
    }
}

template <typename ElemType>
inline void InThreadBinTree<ElemType>::InOrderVisit(void (*Visit)(const ElemType &elem)) const
{
    ThreadBinNode<ElemType> *p;
    for (p = GetFirst(); p != nullptr; p = GetNext(p))
    {
        Print(p->data);

        // if (p->leftTag == 1)
        //     cout << "其左指针为线索指针，指向";
        // else
        //     cout << "其左指针为孩子指针，指向";

        // if (p->leftChild != nullptr)
        //     cout << p->leftChild->data;
        // else
        //     cout << "nullptr";

        // if (p->rightTag == 1)
        //     cout << "其右指针为线索指针，指向";
        // else
        //     cout << "其右指针为孩子指针，指向";

        // if (p->rightChild != nullptr)
        //     cout << p->rightChild->data;
        // else
        //     cout << "nullptr";
    }
}
