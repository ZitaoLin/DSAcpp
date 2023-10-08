#include "HuffmanTreeNode.hpp"
#include "DS/List/LinkList/SinglyLinkList/SinglyLinkedList.hpp"
#include <string>
using namespace std;

template <typename CharType, typename WeightType>
class HuffmanTree
{
private:
    HuffmanTreeNode<WeightType> *nodes; // 结点数组
    CharType *LeafChars;                // 叶结点字符数组
    // CharType为原码数据类型
    string *LeafCharCodes; // 叶结点字符编码数组
    int num;               // 叶结点个数

    // 辅助函数
    void Select(int n, int &r1, int &r2);
    // 在nodes[0～(n-1)]中选择双亲为n，且权值最小的两个结点r1、r2

    void CreateHuffmanTree(CharType ch[], WeightType w[], int n);
    // 由n个字符和权值创建哈夫曼树

public:
    HuffmanTree(CharType ch[], WeightType w[], int n);
    // 由n个字符和权值构造哈夫曼树

    ~HuffmanTree();

    string Encode(CharType ch); // 取字符ch的编码

    LinkList<CharType> Decode(string strCode); // 解码字符串strCode
};

template <typename CharType, typename WeightType>
inline void HuffmanTree<CharType, WeightType>::Select(int n, int &r1, int &r2)
{
    r1 = r2 = -1;
    for (int i = 0; i < n; i++)
    {
        if (nodes[i].parent == -1) // 只处理根结点
        {
            if (r1 == -1)
                r1 = i;
            else if (nodes[i].weight < nodes[r1].weight)
            {
                r2 = r1;
                r1 = i;
            }
            else if (r2 == -1 || nodes[i].weight < nodes[r2].weight)
                r2 = i;
        }
    }
}

template <typename CharType, typename WeightType>
inline void HuffmanTree<CharType, WeightType>::CreateHuffmanTree(CharType ch[], WeightType w[], int n)
{
    num = n;
    int m = 2 * n - 1;

    nodes = new HuffmanTreeNode<WeightType>[m];
    LeafChars = new CharType[n];
    LeafCharCodes = new string[n];

    int i, p, q;
    for (i = 0; i < n; i++) // 存储叶结点信息
    {
        nodes[i].weight = w[i];
        nodes[i].leftChild = -1;
        nodes[i].rightChild = -1;
        nodes[i].parent = -1;
        LeafChars[i] = ch[i];
    }

    for (i = n; i < m; i++) // 构造哈夫曼树
    // 处理叶结点以外的结点
    {
        int r1, r2;
        Select(i, r1, r2); // 查找两棵权值最小的树

        // 合并以r1,r2为根的树
        nodes[r1].parent = nodes[r2].parent = i; // r1、r2的parent是i
        nodes[i].leftChild = r1;                 // r1是i的左孩子
        nodes[i].rightChild = r2;                // r2是i的右孩子
        nodes[i].parent = -1;                    // i为新的树的根结点
        nodes[i].weight = nodes[r1].weight + nodes[r2].weight;
    }

    for (i = 0; i < n; i++) // 求n个叶结点字符的编码
    {
        LinkList<char> charCode;
        q = i;
        p = nodes[q].parent;
        while (p != -1)
        {
            if (nodes[p].leftChild == q)
                charCode.InsertElem(1, '0'); // 左分支编码为0
            else if (nodes[p].rightChild == q)
                charCode.InsertElem(1, '1'); // 右分支编码为1

            q = p;               // q为原先q的双亲
            p = nodes[q].parent; // p为原先p的双亲
        }

        char *tmp = new char[charCode.GetLength()];
        for (int i = 0; i < charCode.GetLength(); i++)
            charCode.GetElem(i + 1, tmp[i]);

        LeafCharCodes[i] = tmp; // 复制字符编码
        delete[] tmp;
    }
}

template <typename CharType, typename WeightType>
inline HuffmanTree<CharType, WeightType>::HuffmanTree(CharType ch[], WeightType w[], int n)
{
    CreateHuffmanTree(ch, w, n);
    num = n;
}

template <typename CharType, typename WeightType>
inline HuffmanTree<CharType, WeightType>::~HuffmanTree()
{
    delete[] nodes;
    delete[] LeafChars;
    delete[] LeafCharCodes;
}

template <typename CharType, typename WeightType>
inline string HuffmanTree<CharType, WeightType>::Encode(CharType ch)
{
    for (int i = 0; i < num; i++)
    {
        if (LeafChars[i] == ch)
            return LeafCharCodes[i];
    }
}

template <typename CharType, typename WeightType>
inline LinkList<CharType> HuffmanTree<CharType, WeightType>::Decode(string strCode)
{
    LinkList<CharType> charList;
    int p = 2 * num - 2;
    for (int i = 0; i < strCode.size(); i++)
    {
        if (strCode[i] == '0')
            p = nodes[p].leftChild;
        else if (strCode[i] == '1')
            p = nodes[p].rightChild;

        if (nodes[p].rightChild == -1 && nodes[p].leftChild == -1)
        {
            charList.InsertElem(charList.GetLength() + 1, LeafChars[p]);
            p = 2 * num - 2;
        }
    }
    return charList;
}
