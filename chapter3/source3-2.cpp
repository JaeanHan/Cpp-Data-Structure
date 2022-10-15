#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;

template <class T>
class Stack
{
public:
    Stack(int stackCapacity = 10);
    ~Stack();
    bool IsEmpty() const;
    T &Top() const;
    void Push(const T &item);
    void Pop();

    template <class U>
    friend istream &operator>>(istream &CIN, Stack<U> &target);

    template <class U>
    friend ostream &operator<<(ostream &COUT, Stack<U> &target);

private:
    T *stack;
    int top;
    int capacity;
};

template <class T>
Stack<T>::Stack(int stackCapacity)
{
    if (stackCapacity < 0)
    {
        throw "capacity must be greater than 0";
    }

    stack = new T[stackCapacity];
    top = -1;
    capacity = stackCapacity;
}

template <class T>
Stack<T>::~Stack()
{
    cout << "~Stack()" << endl;
    delete[] stack;
}

template <class T>
inline bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template <class T>
inline T &Stack<T>::Top() const
{
    if (IsEmpty())
        throw "Stack is empty";
    return stack[top];
}

template <class T>
void changeSize(T *&array, const int oldSize, const int newSize)
{
    T *newArray = new T[newSize];
    int copySize = oldSize > newSize ? newSize : oldSize;

    memcpy(newArray, array, sizeof(T) * copySize);

    delete[] array;
    array = newArray;
}

template <class T>
void Stack<T>::Push(const T &item)
{
    if (top + 1 == capacity)
    {
        changeSize(stack, capacity, 2 * capacity);
    }
    stack[++top] = item;
}

template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty())
        throw "Stack is empty. Cannot delete";
    stack[top--].~T();
}

template <class T>
istream &operator>>(istream &CIN, Stack<T> &target)
{
    cout << "enter the number of elements to put: ";
    int size;
    cin >> size;

    srand(time(0));

    for (int i = 0; i < size; i++)
    {
        target.Push(rand() % 100);
    }

    return CIN;
}

template <class T>
ostream &operator<<(ostream &COUT, Stack<T> &target)
{
    if (target.IsEmpty())
    {
        COUT << "stack is empty" << endl;
        return COUT;
    }

    COUT << "stack: ";
    for (int i = 0; i < target.top + 1; i++)
    {
        COUT << target.stack[i] << " ";
    }
    COUT << endl;
    return COUT;
}

int main()
{
    Stack<int> s(2);
    cin >> s;
    cout << s;
    // s.Push(3);
    // s.Push(6);
    // s.Push(1);
    // s.Push(2);
    // s.Push(4);
    // s.Push(5);
    // s.Push(8);
    // s.Push(7);
    // s.Push(9);
    // s.Push(3);
    // s.Push(10);
    // s.Push(12);
    // s.Push(11);
    // s.Push(13);
    // s.Push(15);
    // s.Push(14);
    // s.Push(17);
    // s.Push(16);

    cout << "is empty" << endl;
    if (s.IsEmpty())
    {
        cout << " yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
    cout << "print all elements: " << endl;
    while (!s.IsEmpty())
    {
        cout << s.Top() << " ";
        s.Pop();
    }
    cout << endl;
    cout << "bye" << endl;

    return 0;
}
