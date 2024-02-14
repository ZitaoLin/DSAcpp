#if !defined(MINHEAP_HPP_)
#define MINHEAP_HPP_

#define Status bool

template <typename ElemType>
class MinHeap
{
private:
    ElemType *heapArr;
    int currentSize;
    int maxSize;
    void FilterDown(int Start); // 自下而上的向下调整算法
    void Filterup(int End);

public:
    MinHeap(int max_size);
    MinHeap(ElemType es[], int max_size, int n);
    ~MinHeap() { delete[] heapArr; }

    Status Insert(const ElemType &e);
    Status DeleteTop(ElemType &e);
    Status GetTop(ElemType &e) const;
    void Traverse(void (*Visit)(const ElemType &e)) const;

    bool IsEmpty() const { return currentSize == 0; }
    bool IsFull() const { return currentSize == maxSize; }
    int SizeOfHeap() const { return currentSize; }
    void SetEmpty() { currentSize = 0; }
};

#endif // MINHEAP_HPP_

template <typename ElemType>
inline void MinHeap<ElemType>::FilterDown(int Start)
{
    
}

template <typename ElemType>
inline MinHeap<ElemType>::MinHeap(int maxSize)
{
    currentSize = 0;
    maxSize = max_size;
    heapArr = new ElemType[maxSize];
}

template <typename ElemType>
inline MinHeap<ElemType>::MinHeap(ElemType es[], int max_size, int n)
{
    maxSize = max_size;
    heapArr = new ElemType[maxSize];
    currentSize = n;
    for (int i = 0; i < n; i++)
        heapArr[i] = es[i];
}
