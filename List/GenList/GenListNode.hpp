#if !defined(GENLISTNODE_H_)
#define GENLISTNODE_H_

enum NodeType
{
    ATOM,
    LIST
};

struct GListNode
{
    NodeType type; // 节点类型：原子或子表
    union
    {
        int atom;           // 原子
        GListNode *sublist; // 指向子表的指针
    } data;
    GListNode *next; // 指向下一个节点

    GListNode(int atomValue) : type(ATOM), next(nullptr)
    {
        data.atom = atomValue;
    }

    GListNode(GListNode *sublistNode) : type(LIST), next(nullptr)
    {
        data.sublist = sublistNode;
    }
};

#endif // GENLISTNODE_H_
