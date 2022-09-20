#include <iostream>
#include <memory>
#include <cstring>
// #include "time.h"

using namespace std;

#define MaxSize 100

template <class T>
class Set
{
private:
    T *array;
    int capacity;
    int top;

public:
    Set(int enteredCapacity = 10);
    ~Set();
    virtual void Push(T); // abstract?
    virtual T &Pop();
    bool IsEmpty();
    bool IsFull();
    int Size();
    // friend ostream &operator<<(ostream &, Set<T> &);
};

template <class T>
Set<T>::Set(int enteredCapacity) : capacity(enteredCapacity)
{
    if (enteredCapacity < 1)
        throw "Capacity must be > 0";

    array = new T[capacity];
    top = -1;
}

template <class T>
Set<T>::~Set()
{
    delete[] array;
}

template <class T>
bool Set<T>::IsEmpty()
{
    return top < 0;
}

template <class T>
bool Set<T>::IsFull()
{
    return top == MaxSize - 1;
}

template <class T>
void setBagCapacity(T *origin, int currentCapacity, int newCapacity)
{
    if (newCapacity < 0)
    {
        throw "new capacity must be greater than 0";
    }

    int length = currentCapacity > newCapacity ? newCapacity : currentCapacity;

    T *temp = new T[length];

    memcpy(temp, origin, sizeof(T) * length);

    delete[] origin;

    origin = temp;
}

template <class T>
T &Set<T>::Pop()
{
    if (IsEmpty())
    {
        throw "no element found";
    }

    int popIndex = top / 2;

    T *popped = new T;
    *popped = array[popIndex];

    memcpy(array[popIndex], array[popIndex + 1], sizeof(T) * (top - popIndex));

    top--;

    return popped;
}

template <class T>
void Set<T>::Push(const T item)
{
    for (int i = 0; i < top; i++)
    {
        if (array[i] == item)
        {
            return;
        }
    }

    if (top > capacity)
    {
        setBagCapacity(array, capacity, 2 * capacity);
        capacity *= 2;
    }

    array[++top] = item;
}

// template <class T>
// ostream &operator<<(ostream &ostream, Set<T> set)
// {
//     for (int i = 0; i < set.top; i++)
//     {
//         ostream << " " << set.array[i];
//     }
//     return ostream;
// }

int main()
{
    Set<int> b(4);
    int n;

    // Set<float> fo(10);에 대하여도 구현할 것

    //화면에서 임의 숫자를 입력받아 Push( ) 호출하도록 수정

    b.Push(3);
    b.Push(5);
    b.Push(1);
    b.Push(6);
    b.Push(7);

    if (b.IsEmpty())
    {
        cout << "empty" << endl;
    }

    else
    {
        cout << "not empty" << endl;
    }

    while (!b.IsEmpty())
    {
        n = b.Pop();
        cout << "b.Pop() = " << n << endl;
    }

    // system("pause");

    return 0;
}