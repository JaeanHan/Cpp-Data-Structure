#include <iostream>
#include <memory>
#include <cstring>
#include <typeinfo>
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
    void show(); // Push 확인을 위해 직접 만든 함수

    template <class T2>
    friend ostream &operator<<(ostream &, const Set<T2> &);
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
void setBagCapacity(T *&origin, int currentCapacity, int newCapacity)
{
    if (newCapacity < 0)
    {
        throw "new capacity must be greater than 0";
    }

    int length = currentCapacity > newCapacity ? currentCapacity : newCapacity;
    // 사이즈 더 작게는 x
    // cout << "length: " << length << endl;

    T *temp = new T[length];

    memcpy(temp, origin, sizeof(T) * length);
    // origin부터 length만큼을 tmep로 복사

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

    // cout << "top: " << top << endl;
    // cout << endl;

    int popIndex = top / 2;

    T *popped = new T;
    *popped = array[popIndex];

    memcpy(array + popIndex, array + popIndex + 1, sizeof(T) * (top - popIndex));

    top--;

    return *popped;
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

    if (top == capacity - 1)
    {
        setBagCapacity(array, capacity, 2 * capacity);
        capacity *= 2;
    }

    array[++top] = item;
    // cout << top << endl;
    // cout << "array[top]: " << array[top] << endl;
}

template <class T>
void Set<T>::show()
{
    for (int i = 0; i < top + 1; i++)
    {
        cout << array[i] << " ";
    }
}

template <class T>
ostream &operator<<(ostream &ostream, const Set<T> &set)
{
    for (int i = 0; i < set.top + 1; i++)
    {
        ostream << " " << set.array[i];
    }
    return ostream;
}

int main()
{
    Set<int> b(4);
    int n;
    int cnt = 0;

    // Set<float> fo(10);에 대하여도 구현할 것

    //화면에서 임의 숫자를 입력받아 Push( ) 호출하도록 수정

    b.Push(3);
    b.Push(5);
    b.Push(1);
    b.Push(6);
    b.Push(7);

    // cout << b << endl;

    if (b.IsEmpty())
    {
        cout << "empty" << endl;
    }

    else
    {
        cout << "not empty" << endl;
        // cout << "b.show() : ";
        // b.show();
        // cout << endl;
    }

    while (!b.IsEmpty())
    {
        n = b.Pop();
        cout << "b.Pop() = " << n << endl;
        cnt++;
    }

    // system("pause");

    return 0;
}