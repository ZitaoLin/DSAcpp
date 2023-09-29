#if !defined(TRISPARSEMATRIX_H_)
#define TRISPARSEMATRIX_H_

#include "Triple.hpp"

template <typename ElemType>
class TriSparseMatrix
{
protected:
    Triple<ElemType>* triElems;
    int maxSize;
    int row,cols,num;
    
};

#endif // TRISPARSEMATRIX_H_
