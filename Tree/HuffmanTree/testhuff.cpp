#include "HuffmanTree.hpp"
#include <iostream>
int main()
{
    char ch[4] = {'A', 'B', 'C', 'D'};
    int w[4] = {1, 3, 2, 4};
    HuffmanTree<char, int> ht(ch, w, 4);
    cout << ht.Encode('B')<<endl;
    return 0;
}