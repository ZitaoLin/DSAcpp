#include "GenList.hpp"
#include <iostream>

int main()
{
    GList list;
    list.addAtom(1);
    list.addAtom(2);

    GList sublist;
    sublist.addAtom(3);
    sublist.addAtom(4);
    sublist.addAtom(5);

    GList subsublist;
    subsublist.addAtom(6);
    subsublist.addAtom(7);
    subsublist.addAtom(8);
    subsublist.addAtom(9);

    sublist.addSublist(subsublist);
    list.addSublist(sublist);

    std::cout << "原子数量: " << list.countAtoms() << std::endl;

    return 0;
}
