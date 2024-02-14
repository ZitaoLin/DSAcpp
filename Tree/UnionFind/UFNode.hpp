#if !defined(UFNODE_HPP_)
#define UFNODE_HPP_

template <typename ElemType>
struct UFNode
{
    ElemType data; // 数据值
    int parent;    //! 双亲指针域 根结点的parent值为该树结点个数相反数
};

#endif // UFNODE_HPP_
