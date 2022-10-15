// #pragma once
#include <iostream>
#include <memory>
#include <cstring>
#define MaxSize 100

using namespace std;

template <class T>
class Bag
{
public:
    Bag(int BagCapacity = 10);
    ~Bag();
    bool isFull();
    int Size() const;
    bool isEmpty() const;
    virtual T &Pop();
    virtual void Push(const T &);

    template <class U>
    friend ostream &operator<<(ostream &ostream, Bag<U> &operand);

private:
    T *array;
    int capacity;
    int top;
};

template <class T>
Bag<T>::Bag(int Bagcapacity)
{
    if (Bagcapacity < 1)
        throw "Capacity must be > 0";

    capacity = Bagcapacity;
    top = -1;
    array = new T[capacity];
}

template <class T>
Bag<T>::~Bag()
{
    delete[] array;
}

template <class T>
bool Bag<T>::isFull()
{
    return capacity == top;
}

// template <class T>
// void Bag<T>::setTopByMinusOne()
// {
//     top--;
// }

template <class T>
int Bag<T>::Size() const
{
    // return sizeof(array)/sizeof(array[0]);
    // return capacity; 함수 용도를 이해 못한듯?
    return top + 1;
}

template <class T>
bool Bag<T>::isEmpty() const
{
    return top == -1;
}

template <class T>
void ChangeSizeID(T *&a, const int oldSize, const int newSize)
{
    if (newSize < 0)
        throw "New length must be >= 0";

    T *temp = new T[newSize];
    int number = oldSize;

    if (oldSize > newSize)
        number = newSize;

    memcpy(temp, a, sizeof(T) * number);
    delete[] a;
    a = temp;
}

template <class T>
T &Bag<T>::Pop()
{
    static T retValue;
    // T* retValue = new T;

    if (isEmpty())
        throw "Bag is empty, cannot be delete";

    int deletePos = top / 2;
    // *retValue = array[deletePos];
    retValue = array[deletePos];

    memcpy(array + deletePos, array + deletePos + 1, sizeof(T) * (top - deletePos));
    top--;

    // return *retValue;
    return retValue;
}

template <class T>
void Bag<T>::Push(const T &item)
{
    if (top + 1 == capacity)
    {
        ChangeSizeID(array, capacity, 2 * capacity);
    }
    array[++top] = item;
}

template <class T>
ostream &operator<<(ostream &os, Bag<T> &bag)
{
    os << "remaining: ";
    for (int i = 0; i < bag.Size(); i++)
    {
        os << bag.array[i] << " ";
    }
    os << endl;
    return os;
}

int main()
{
    Bag<int> b(4);

    b.Push(3);
    b.Push(5);
    b.Push(1);
    b.Push(6);
    b.Push(2);
    b.Push(8);
    b.Push(4);
    b.Push(7);
    b.Push(9);

    if (b.isEmpty())
    {
        cout << "empty" << endl;
    }
    else
    {
        cout << "not empty" << endl;
    }

    while (!b.isEmpty())
    {
        int pop = b.Pop();
        cout << pop << endl;
        cout << b;
    }

    return 0;
}