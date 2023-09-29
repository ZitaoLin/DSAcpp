template <typename ElemType>
struct Triple
{
    int row, col;
    ElemType val;
    Triple() {}
    Triple(int r, int c, ElemType v) : row(r), col(c), val(v) {}
};