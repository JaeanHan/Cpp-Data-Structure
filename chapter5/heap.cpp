#include <iostream>
#include "time.h"

using namespace std;

const int HeapSize = 1000;
enum Boolean
{
    FALSE,
    TRUE
};

template <class Type>
class Element
{
public:
    Type key;
    Element() {}
    Element(Type key) : key(key) {}
};

template <class Type>
class MinPQ
{
public:
    virtual void Insert(const Element<Type> &) = 0;
    virtual Element<Type> *DeleteMin(Element<Type> &) = 0;
};

template <class Type>
class MaxPQ
{
public:
    virtual void Insert(const Element<Type> &) = 0;
    virtual Element<Type> *DeleteMax(Element<Type> &) = 0;
};

template <class Type>
class MinHeap : public MinPQ<Type>
{
public:
    MinHeap(int size)
    {
        maxSize = size;
        n = 0;
        heap = new Element<Type>[maxSize + 1];
    }
    void display();
    void Insert(const Element<Type> &x);
    Element<Type> *DeleteMin(Element<Type> &);

private:
    Element<Type> *heap;
    int n;
    int maxSize;
    void heapEmpty() { cout << "Heap is Empty!" << endl; }
    void heapFull() { cout << "Heap is Full!" << endl; }
};

template <class Type>
class MaxHeap : public MaxPQ<Type> // Max Heap
{
public:
    MaxHeap(int sz = HeapSize)
    {
        MaxSize = sz;
        n = 0;
        heap = new Element<Type>[MaxSize + 1]; // don'ㅅ want to use heap[0]
    }
    void display();
    void Insert(const Element<Type> &x);
    Element<Type> *DeleteMax(Element<Type> &);

private:
    Element<Type> *heap;
    int n;       // current size of MaxHeap
    int MaxSize; // maximum allowable size of MaxHeap
    void HeapEmpty() { cout << "Heap is empty" << endl; }
    void HeapFull() { cout << "Heap is full" << endl; }
};

template <class Type>
void MinHeap<Type>::display()
{
    int i;
    cout << "MinHeap:: (i, heap[i].key): ";
    for (i = 1; i <= n; i++)
        cout << "(" << i << ", " << heap[i].key << ") ";
    cout << endl;
}

template <class Type>
void MinHeap<Type>::Insert(const Element<Type> &x)
{
    if (n == maxSize)
    {
        heapFull();
        return;
    }
    n++;
    heap[n] = x;
    Element<Type> temp;
    int i = n;

    while (i > 1)
    {
        if (heap[i / 2].key > x.key)
        {
            temp = heap[i / 2];
            heap[i / 2] = x;
            heap[i] = temp;
            i /= 2;
        }
        else
            break;
    }
}

template <class Type>
Element<Type> *MinHeap<Type>::DeleteMin(Element<Type> &x)
{
    if (n == 0)
    {
        heapEmpty();
        return nullptr;
    }

    int i = 1;
    int j;
    Element<Type> temp;
    x = heap[i];
    heap[i] = heap[n];
    n--;
    //     while (i * 2 <= n)
    //     {
    //         cout << "i: " << i << endl;
    //         temp = heap[i];
    //         cout << temp.key << endl;
    //         if (i * 2 + 1 > n) // 오른쪽 노드 없으면 (마지막 자식이다)
    //         {
    //             if (heap[i].key < heap[i * 2].key)
    //             {
    //                 heap[i] = heap[i * 2];
    //                 heap[i * 2] = temp;
    //             }
    //             cout << "hi" << endl;
    //             break;
    //         }
    //         else if (heap[i * 2].key > heap[i * 2 + 1].key)
    //         {
    //             heap[i] = heap[i * 2 + 1];
    //             heap[i * 2 + 1] = temp;
    //             cout << "ji" << endl;
    //         }
    //         else
    //         {
    //             heap[i] = heap[i * 2];
    //             heap[i * 2] = temp;
    //             cout << "ki" << endl;
    //         }
    //         i *= 2;
    //         cout << "after: " << i << endl;
    //     }

    for(i = 1, j = 2; j<=n;)
    {
        if(j<n)
            if(heap[j].key > heap[j+1].key)
                j++;
        if(heap[i].key <= heap[j].key)
            break;
        temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        i = j;
        j *= 2;
    }
        return &x;   // 루트 값 반환
}

template <class Type>
void MaxHeap<Type>::display()
{
    int i;
    cout << "MaxHeap:: (i, heap[i].key): ";
    for (i = 1; i <= n; i++)
        cout << "(" << i << ", " << heap[i].key << ") ";
    cout << endl;
}

template <class Type>
void MaxHeap<Type>::Insert(const Element<Type> &x)
{
    int i;
    if (n == MaxSize) // 꽉 찼으면
    {
        HeapFull();
        return; // 나가
    }

    n++;                 // 현재 추가할 index
    for (i = n; i >= 1;) // 뒤에서부터 시작
    {
        if (i == 1) // 1이면 top priority
            break;
        if (x.key <= heap[i / 2].key) // insert하는 key가 parent의 key보다 작거나 같다면
            break;                    // 해당 index가 알맞은 자리
        heap[i] = heap[i / 2];        // 크면 교체 parent의 key는 해당 i로
        i /= 2;                       // i는 parent 자리로
    }
    heap[i] = x; // i번째에 insert x
}

template <class Type>
Element<Type> *MaxHeap<Type>::DeleteMax(Element<Type> &x) // 항상 루트를 삭제
{
    int i, j;
    if (!n) // n이 초기화 안됐다면
    {
        HeapEmpty();
        return 0; // 삭제할게 없다
    }
    x = heap[1];               // 루트에서 시작
    Element<Type> k = heap[n]; // 마지막 node 복사
    n--;                       // 마지막 node 유효범위에서 제거

    for (i = 1, j = 2; j <= n;) // i는 루트부터, j는 자식 node에서 시작
    {
        if (j < n)                             // j 번째 node가 마지막 노드가 아니라면
            if (heap[j].key < heap[j + 1].key) // 왼쪽 자식보다 오른쪽 자식이 크다면
                j++;                           // j는 큰 자식쪽으로 이동
        if (k.key >= heap[j].key)              // 마지막 노드 값이 지금 가르키는 노드(parent)의 값보다 크거나 같다면
            break;                             // for문 탈출 (더이상 parent 비교x)
        heap[i] = heap[j];                     // 한칸씩 앞으로 땡겨 (child -> parent)
        i = j;                                 // i로 이동 (parent)
        j *= 2;                                // j는 해당 node의 child node의 index로 이동
    }
    heap[i] = k; // 마지막 노드는 i번째 index에 추가
    return &x;   // 루트 값 반환
}

template <class Type>
void randInit(MaxHeap<Type> *MaxHeap, int num)
{
    srand(time(NULL));

    for (int i = 0; i < num; i++)
    {
        MaxHeap->Insert(Element<int>(rand() % 100));
    }
}

template <class Type>
void randInit(MinHeap<Type> *MinHeap, int num)
{
    srand(time(NULL));

    for (int i = 0; i < num; i++)
    {
        MinHeap->Insert(Element<int>(rand() % 100));
    }
}

int main()
{
    int select = 0;
    int data = 0;

    MaxHeap<int> heap(20);
    Element<int> ele;

    MinHeap<int> heap2(20);
    Element<int> ele2;

    Element<int> *deleteEle = nullptr;

    do
    {
        cout << endl
             << "Max Tree. Select: 1 insert, 2 display, 3 delete, 7 exit" << endl
             << "Min Tree. Select: 4 insert, 5 display, 6 delete, 7 exit" << endl;
        cin >> select;
        switch (select)
        {
        case 1:
            cout << "input value: ";
            cin >> data;
            randInit(&heap, data);
            heap.display();
            break;
        case 2:
            heap.display();
            break;
        case 3:
            deleteEle = heap.DeleteMax(ele);
            if (deleteEle != nullptr)
                cout << "deleted element: " << deleteEle->key << endl;
            cout << "current max heap: " << endl;
            heap.display();
            break;
        case 4:
            cout << "input value: ";
            cin >> data;
            randInit(&heap2, data);
        case 5:
            heap2.display();
            break;
        case 6:
            deleteEle = heap2.DeleteMin(ele);
            if (deleteEle != nullptr)
                cout << "deleted element: " << deleteEle->key << endl;
            cout << "current min heap: " << endl;
            heap2.display();
        default:
            break;
        }
    } while (select < 7);

    return 0;
}