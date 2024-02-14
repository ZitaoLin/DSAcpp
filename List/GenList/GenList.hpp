#if !defined(GENLIST_H_)
#define GENLIST_H_

#include "GenListNode.hpp"

class GList
{
private:
    GListNode *head;

public:
    GList() : head(nullptr) {}

    // 向广义表添加原子
    void addAtom(int atom)
    {
        GListNode *newNode = new GListNode(atom);
        newNode->next = head;
        head = newNode;
    }

    // 向广义表添加子表
    void addSublist(const GList& sublist)
    {
        GListNode *newNode = new GListNode(sublist.head);
        newNode->next = head;
        head = newNode;
    }

    // 统计原子数目
    int countAtoms()
    {
        return countAtomsRecursive(head);
    }

private:
    int countAtomsRecursive(GListNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->type == ATOM)
        {
            return 1 + countAtomsRecursive(node->next);
        }
        else
        { // LIST
            return countAtomsRecursive(node->data.sublist) + countAtomsRecursive(node->next);
        }
    }
};

#endif // GENLIST_H_
