#include "BinTreeNode.hpp"
#include <queue>
#include <iostream>
#include <cmath>
using namespace std;

template <typename ElemType>
void Print(const ElemType &elem) { cout << elem << ' '; }
// 遍历打印

template <typename ElemType>
class BinaryTree
{
private:
    BinTreeNode<ElemType> *root; // 根结点

    void Destroy(BinTreeNode<ElemType> *&r);
    // 删除以r为根结点的二叉树
    void Copy(BinTreeNode<ElemType> *&nt, BinTreeNode<ElemType> *t);
    void PreOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const;  // 前序遍历
    void InOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const;   // 中序遍历
    void PostOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const; // 后序遍历

    void LevelOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const; // 层序遍历

    int Height(const BinTreeNode<ElemType> *r) const;   // 求二叉树的高度（多少层）
    int NodeNums(const BinTreeNode<ElemType> *r) const; // 求结点个数
    BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *p) const;
    // 在以r为根结点的二叉树中求p的双亲


public:
    BinaryTree();
    BinaryTree(const ElemType &r_elem);
    // 构造以data==r_elem的结点为根结点的二叉树
    BinaryTree(const BinTreeNode<ElemType> *r);
    // 构造以r为根结点的二叉树
    BinaryTree<ElemType> &operator=(const BinaryTree<ElemType> &bt);
    ~BinaryTree();

    BinTreeNode<ElemType> *GetRoot() const { return root; } // 返回根结点
    bool IsEmpty() const { return root == nullptr; }

    void PreOrderPrint() { PreOrder(root, Print); }
    void InOrderPrint() { InOrder(root, Print); }
    void PostOrderPrint() { PostOrder(root, Print); }

    void LevelOrderPrint() { LevelOrder(root, Print); }

    void DisplayShape();

    int GetHeight() const { return Height(root); };
    int GetNodeNums() const { return NodeNums(root); };

    bool GetElem(const BinTreeNode<ElemType> *p, ElemType &e) const;
    bool SetElem(BinTreeNode<ElemType> *p, const ElemType &e);

    BinTreeNode<ElemType> *GetLeftChild(const BinTreeNode<ElemType> *p) const
    {
        return p->leftChild;
    }

    BinTreeNode<ElemType> *GetRightChild(const BinTreeNode<ElemType> *p) const
    {
        return p->rightChild;
    }

    BinTreeNode<ElemType> *GetParent(const BinTreeNode<ElemType> *p) const
    {
        return Parent(root, p);
    }

    BinTreeNode<ElemType> *GetLeftSibling(const BinTreeNode<ElemType> *p) const;
    BinTreeNode<ElemType> *GetRightSibling(const BinTreeNode<ElemType> *p) const;

    void InsertLeftChild(BinTreeNode<ElemType> *p, const ElemType &e);
    void InsertRightChild(BinTreeNode<ElemType> *p, const ElemType &e);

    void DeleteLeftTree(BinTreeNode<ElemType> *p);
    void DeleteRightTree(BinTreeNode<ElemType> *p);
};

template <typename ElemType>
inline void BinaryTree<ElemType>::Destroy(BinTreeNode<ElemType> *&r)
{

    if (r != nullptr)
    {
        Destroy(r->leftChild);
        Destroy(r->rightChild);
        delete r;
        r = nullptr;
    }
}

template <typename ElemType>
inline void BinaryTree<ElemType>::Copy(BinTreeNode<ElemType> *&nt, BinTreeNode<ElemType> *t)
{
    // BinTreeNode<ElemType> *nt = new BinTreeNode<ElemType>(*t);
    if (t != nullptr && nt != nullptr)
    {
        if (t->leftChild)
            nt->leftChild = new BinTreeNode<ElemType>(*(t->leftChild));

        if (t->rightChild)
            nt->rightChild = new BinTreeNode<ElemType>(*(t->rightChild));
        Copy(nt->leftChild, t->leftChild);
        Copy(nt->rightChild, t->rightChild);
    }
    // if (nt == nullptr || t == nullptr)
    //     return;
}

template <typename ElemType>
inline void BinaryTree<ElemType>::PreOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const
{
    if (r != nullptr)
    {
        Visit(r->data);
        PreOrder(r->leftChild, Visit);
        PreOrder(r->rightChild, Visit);
    }
}

template <typename ElemType>
inline void BinaryTree<ElemType>::InOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const
{
    if (r != nullptr)
    {
        InOrder(r->leftChild, Visit);
        Visit(r->data);
        InOrder(r->rightChild, Visit);
    }
}

template <typename ElemType>
inline void BinaryTree<ElemType>::PostOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const
{
    if (r != nullptr)
    {
        PostOrder(r->leftChild, Visit);
        PostOrder(r->rightChild, Visit);
        Visit(r->data);
    }
}

template <typename ElemType>
inline void BinaryTree<ElemType>::LevelOrder(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &elem)) const
{
    std::queue<BinTreeNode<ElemType> *> q;
    BinTreeNode<ElemType> *p;
    if (r != nullptr)
        q.push(r);
    while (!q.empty())
    {
        p = q.front();
        Visit(p->data);
        q.pop();

        if (p->leftChild != nullptr)
            q.push(p->leftChild);
        if (p->rightChild != nullptr)
            q.push(p->rightChild);
    }
}

template <typename ElemType>
inline int BinaryTree<ElemType>::Height(const BinTreeNode<ElemType> *r) const
{
    if (r == nullptr)
        return 0;
    else
        return 1 + max(Height(r->leftChild), Height(r->rightChild));
}

template <typename ElemType>
inline int BinaryTree<ElemType>::NodeNums(const BinTreeNode<ElemType> *r) const
{
    if (r == nullptr)
        return 0;
    else
        return 1 + NodeNums(r->leftChild) + NodeNums(r->rightChild);
}

template <typename ElemType>
inline BinTreeNode<ElemType> *BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *p) const
{
    if (r == nullptr) // 空树或者递归到底
        return nullptr;

    else if (r->leftChild == p || r->rightChild == p)
        return r;

    else
    {
        BinTreeNode<ElemType> *tmp;

        tmp = Parent(r->leftChild, p);
        if (tmp != nullptr) // 双亲在左子树上
            return tmp;

        tmp = Parent(r->rightChild, p);
        if (tmp != nullptr) // 双亲在右子树上
            return tmp;

        else
            return nullptr; // 结点p就压根不在树上
    }
}

template <typename ElemType>
inline BinaryTree<ElemType>::BinaryTree()
{
    root = nullptr;
}

template <typename ElemType>
inline BinaryTree<ElemType>::BinaryTree(const ElemType &r_elem)
{
    root = new BinTreeNode<ElemType>(r_elem);
}

template <typename ElemType>
inline BinaryTree<ElemType>::BinaryTree(const BinTreeNode<ElemType> *r)
{
    root = r;
}

template <typename ElemType>
inline BinaryTree<ElemType> &BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &bt)
{
    if ((*this).root == bt.root)
        return *this;
    else
    {
        this->root = new BinTreeNode<ElemType>(*(bt.root));
        Copy(this->root, bt.root);
        return *this;
    }
}

template <typename ElemType>
inline BinaryTree<ElemType>::~BinaryTree()
{
    Destroy(root);
}

template <typename ElemType>
inline void BinaryTree<ElemType>::DisplayShape()
{
    if (root == nullptr) {
        cout << "二叉树为空。" << endl;
        return;
    }

    queue<BinTreeNode<ElemType> *> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // 当前层级的元素数量

        for (int i = 0; i < levelSize; ++i) {
            BinTreeNode<ElemType> *current = q.front();
            q.pop();

            // 打印当前节点的数据
            cout << current->data << " ";

            if (current->leftChild != nullptr)
                q.push(current->leftChild);

            if (current->rightChild != nullptr)
                q.push(current->rightChild);
        }

        // 每个层级后换行
        cout << endl;
    }
}

template <typename ElemType>
inline bool BinaryTree<ElemType>::GetElem(const BinTreeNode<ElemType> *p, ElemType &e) const
{
    if (IsEmpty())
    {
        cout << "There's nothing to get!" << endl;
        return false;
    }
    else
    {
        e = p->data;
        cout << "Data has been successfully got!" << endl;
        return true;
    }
}

template <typename ElemType>
inline bool BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType> *p, const ElemType &e)
{
    if (IsEmpty())
    {
        cout << "There's nothing can be set!" << endl;
        return false;
    }
    else
    {
        p->data = e;
        cout << "Data has been successfully set!" << endl;
        return true;
    }
}

template <typename ElemType>
inline BinTreeNode<ElemType> *BinaryTree<ElemType>::GetLeftSibling(const BinTreeNode<ElemType> *p) const
{
    BinTreeNode<ElemType> *p_parent = Parent(root, p);
    if (p_parent == nullptr)
        return nullptr;
    else if (p_parent->rightChild == p)
        return p_parent->leftChild;
    else
        return nullptr;
}

template <typename ElemType>
inline BinTreeNode<ElemType> *BinaryTree<ElemType>::GetRightSibling(const BinTreeNode<ElemType> *p) const
{
    BinTreeNode<ElemType> *p_parent = Parent(root, p);
    if (p_parent == nullptr)
        return nullptr;
    else if (p_parent->leftChild == p)
        return p_parent->rightChild;
    else
        return nullptr;
}

template <typename ElemType>
inline void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *p, const ElemType &e)
{
    if (p == nullptr)
    {
        cout << "P can not breed -_-" << endl;
        return;
    }
    else
    {
        BinTreeNode<ElemType> *lchild = new BinTreeNode<ElemType>(e);
        if (p->leftChild != nullptr) // p的左孩子非空
            lchild->leftChild = p->leftChild;
        p->leftChild = lchild;
    }
}

template <typename ElemType>
inline void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *p, const ElemType &e)
{
    if (p == nullptr)
    {
        cout << "P can not breed -_-" << endl;
        return;
    }
    else
    {
        BinTreeNode<ElemType> *rchild = new BinTreeNode<ElemType>(e);
        if (p->rightChild != nullptr) // p的右孩子非空
            rchild->rightChild = p->rightChild;
        p->rightChild = rchild;
    }
}

template <typename ElemType>
inline void BinaryTree<ElemType>::DeleteLeftTree(BinTreeNode<ElemType> *p)
{
    if (p == nullptr)
        return;

    Destroy(p->leftChild->leftChild);
    Destroy(p->leftChild->rightChild);
}

template <typename ElemType>
inline void BinaryTree<ElemType>::DeleteRightTree(BinTreeNode<ElemType> *p)
{
    if (p == nullptr)
        return;

    Destroy(p->rightChild->leftChild);
    Destroy(p->rightChild->rightChild);
}
